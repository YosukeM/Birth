#include "inputMouse.h"

#include "Matrix4d.h"
#include <GL/glfw.h>

using namespace input;

Mouse::Mouse() {

}

void Mouse::update(f32) {
	glfwGetMousePos(&_position.x, &_position.y);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	_position.x -= viewport[0];
	_position.y -= viewport[1];
}

int2d Mouse::getPosition() const {
	return _position;
}

core::tuple<float3d, float3d> Mouse::getRay() const {
	float3d from, to;
	float3d cursor_pos;

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	cursor_pos = float3d(
		(_position.x / f32(viewport[2]) * 2.0f - 1.0f),
		(1.0f - _position.y / f32(viewport[3]) * 2.0f),
		0.0f
	);

	Matrix4d proj_inv = Matrix4d::getProjection().getInverse();
	Matrix4d modelview_inv = Matrix4d::getModelView().getInverse();
	
	float3d proj_cursor_pos = proj_inv * cursor_pos;
	from = modelview_inv * proj_cursor_pos;
	to = modelview_inv * (proj_cursor_pos + float3d(0.0f, 0.0f, -1.0f));

	return core::tuple<float3d, float3d>(from, to);
}