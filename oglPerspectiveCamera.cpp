#include "oglPerspectiveCamera.h"
#include "GetterSetter.h"

#include <GL/glfw.h>
#ifdef _WIN32
	#include <GL/GLU.h>
#else
	#include <OpenGL/glu.h>
#endif

using namespace ogl;

PerspectiveCamera::PerspectiveCamera()
	: _near(1.0f), _far(1000.0f), _fov(3.1415926535897932f / 4.0f)
{
}

#define GETSET_L(tp, ex, in) GETSET(PerspectiveCamera, tp, ex, in)
#define GETSET_LP(tp, ex, in) GETSET_P(PerspectiveCamera, tp, ex, in)

GETSET_L(float3d, Position, _position)
GETSET_L(float3d, LookAt, _lookAt)

GETSET_LP(float, Near, _near)
GETSET_LP(float, Far, _far)
GETSET_LP(float, Fov, _fov)

void PerspectiveCamera::setMatrix() {
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(_fov / 3.1415926535897932 * 180.0, double(viewport[2]) / double(viewport[3]), _near, _far);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		_position.x, _position.y, _position.z,
		_lookAt.x, _lookAt.y, _lookAt.z,
		0.0, 1.0, 0.0
	);
}
