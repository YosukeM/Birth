#include "gameOvum.h"

#include <GL/glfw.h>
#ifdef _WIN32
	#include <GL\GLU.h>
#endif

using namespace game;

Ovum::Ovum(core::shared_ptr<rsc::IManager>)
	: _gluQuad(NULL)
{
	_gluQuad = gluNewQuadric();
}

Ovum::~Ovum() {
	gluDeleteQuadric(_gluQuad);
}

void Ovum::update(f32) {
}

void Ovum::_drawSolid() {
	gluSphere(_gluQuad, 100.0, 20, 60);
}