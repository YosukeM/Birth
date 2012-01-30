#include "gamePlayer.h"

#include "rscIManager.h"
#include "rscMesh.h"
#include "oglShader.h"

#include "Angle2d.h"
#include "inputManager.h"
#include "inputMouse.h"

#include "rscShader.h"

using namespace game;

Player::Player(core::shared_ptr<rsc::IManager> rm)
	:_tail(0.13f, 3.6f, 12, 20)
{
	_mesh = rm->getMesh("spermatozoa.obj");

	_material.setAmbientColor(Color(0x111111FF));
	_material.setDiffuseColor(Color(0xFFFFFFFF));

	_program = rm->getProgram("spermatozoa");
}

float3d Player::getPosition() const {
	return _position;
}

void Player::update(float t) {
	_theta += 1.0f * Angle2d::PI * 2.0f * t;
	float3d dir = float3d(0.0f, 0.04f * _theta.sin(), 1.0f);
	dir.normalize();

	Quaternion prev_rotation = _rotation;

	if (_pointer.getLengthSQ() > 0.001f) {
		float2d n = _pointer.getNormalized();
		float3d axis(n.y, - n.x, 0.0f);
		f32 level = _pointer.getLength() * 15.0f;
		if (level < 0.0f) level = 0.0f;
		if (level > 1.0f) level = 1.0f;
		Quaternion target(Angle2d::PI * 0.1f * level, axis);
		_rotation = Quaternion::slerp(_rotation, target, 10.0f * t);
	} else {
		_rotation = Quaternion::slerp(_rotation, Quaternion(), 10.0f * t);
	}
	_rotation.normalize();

	float3d velocity = - 20.0f * _rotation.getRotated(float3d(0.0f, 0.0f, -1.0f));
	_position += velocity * t;

	_tail.update(t, Quaternion(0.8f * _theta.sin(), float3d(0, 1, 0)) * _rotation);
}

void Player::draw(Node::EDrawState eds) {
	glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		if (eds == EDS_SOLID) {
			const core::tuple<float3d, float3d> ray = input::Manager::instance()->getMouse()->getRay();

			float3d p;
			if (abs(core::get<0>(ray).z - core::get<1>(ray).z) > 0.0001f) {
				float t = - core::get<1>(ray).z / (core::get<0>(ray).z - core::get<1>(ray).z);
				p = core::get<0>(ray) * t + core::get<1>(ray) * (1.0f - t);
			} else {
				p.x = core::get<0>(ray).x;
				p.y = core::get<0>(ray).y;
			}
			_pointer = float2d(p.x, p.y);

			glPointSize(10.0f);
			glBegin(GL_POINTS);
			glVertex2f(p.x, p.y);
			glEnd();
		}

		core::tuple<Angle2d, float3d> angleaxis = _rotation.getAngleAxis();
		glRotatef(core::get<0>(angleaxis).degree(), core::get<1>(angleaxis).x, core::get<1>(angleaxis).y, core::get<1>(angleaxis).z);

		if (eds == EDS_SOLID) {
			_drawSolid();
		} else {
			_drawEffect();
		}
	glPopMatrix();
}

void Player::_drawSolid() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_NORMALIZE);
	
	_material.bind();
	_program->use();
	_mesh->draw();
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 2.1f);
		core::tuple<Angle2d, float3d> angleaxis = _rotation.getAngleAxis();
		glRotatef(- core::get<0>(angleaxis).degree(), core::get<1>(angleaxis).x, core::get<1>(angleaxis).y, core::get<1>(angleaxis).z);
		_tail.draw();
	glPopMatrix();
	_program->unuse();
	_material.unbind();

	glDisable(GL_CULL_FACE);
	glDisable(GL_NORMALIZE);
}

