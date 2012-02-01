#include "gameSpermatozoa.h"

#include "rscIManager.h"
#include "rscMesh.h"
#include "oglShader.h"

#include "Angle2d.h"
#include "inputManager.h"
#include "inputMouse.h"

#include "rscShader.h"

using namespace game;


Spermatozoa::Spermatozoa(core::shared_ptr<rsc::IManager> rm)
	:_tail(0.13f, 3.6f, 12, 20)
{
	_mesh = rm->getMesh("spermatozoa.obj");

	_material.setAmbientColor(Color(0x000000FF));
	_material.setDiffuseColor(Color(0xFFFFFFFF));

	_program = rm->getProgram("spermatozoa");
}

void Spermatozoa::draw(Node::EDrawState eds) {
	glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		
		_onDraw();	// プレイヤーがマウスポインタの位置を計算する用

		core::tuple<Angle2d, float3d> angleaxis = _rotation.getAngleAxis();
		glRotatef(core::get<0>(angleaxis).degree(), core::get<1>(angleaxis).x, core::get<1>(angleaxis).y, core::get<1>(angleaxis).z);

		if (eds == EDS_SOLID) {
			_drawSolid();
		} else {
			_drawEffect();
		}
	glPopMatrix();
}

void Spermatozoa::_drawSolid() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_NORMALIZE);
	
	_material.bind();
	_program->use();

	// 本体を描く
	_mesh->draw();

	// 尻尾を描く
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