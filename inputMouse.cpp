#include "inputMouse.h"

#include "Matrix4d.h"
#include <GL/glfw.h>

using namespace input;

Mouse::Mouse() {

}

void Mouse::update(f32) {
	glfwGetMousePos(&_position.x, &_position.y);
}

int2d Mouse::getPosition() const {
	return _position;
}

core::tuple<float3d, float3d> Mouse::getRay() const {
	float3d from, to;

	double modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	double projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	int win_w, win_h;
	glfwGetWindowSize(&win_w, &win_h);

	double obj_x, obj_y, obj_z;
	gluUnProject(
		_position.x, win_h - _position.y, 0.0,
		modelview, projection, viewport,
		&obj_x, &obj_y, &obj_z
	);
	from = float3d(f32(obj_x), f32(obj_y), f32(obj_z));
	gluUnProject(
		_position.x, win_h - _position.y, 1.0,
		modelview, projection, viewport,
		&obj_x, &obj_y, &obj_z
	);
	to = float3d(f32(obj_x), f32(obj_y), f32(obj_z));

	/*GLint viewport[4];
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
	to = modelview_inv * (proj_cursor_pos + float3d(0.0f, 0.0f, -1.0f));*/

	return core::tuple<float3d, float3d>(from, to);
}
