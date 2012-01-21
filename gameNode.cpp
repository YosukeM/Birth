#include "gameNode.h"

#include <GL/glfw.h>

using namespace game;

float3d Node::getPosition() const {
	return _position;
}

void Node::setPosition(const float3d& p) {
	_position = p;
}

Quaternion Node::getRotation() const {
	return _rotation;
}

void Node::setRotation(const Quaternion& rotation) {
	_rotation = rotation;
}

void Node::draw(EDrawState eds) {
	glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		core::tuple<Angle2d, float3d> angleaxis = _rotation.getAngleAxis();
		glRotatef(core::get<0>(angleaxis).degree(), core::get<1>(angleaxis).x, core::get<1>(angleaxis).y, core::get<1>(angleaxis).z);

		switch (eds) {
		case EDS_SOLID:
			_drawSolid();
			break;
		case EDS_EFFECT:
			_drawEffect();
			break;
		}

	glPopMatrix();
}