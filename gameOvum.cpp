#include "gameOvum.h"

#include "rscIManager.h"
#include "rscProgram.h"

#include <GL/glfw.h>
#ifdef _WIN32
	#include <GL\GLU.h>
#endif

using namespace game;

const float Ovum::RADIUS = 20.0f;

Ovum::Ovum(core::shared_ptr<rsc::IManager> rm)
	: _gluQuad(NULL)
{
	_gluQuad = gluNewQuadric();
	
	_outerMaterial.setAmbientColor(Color(0x00000066));
	_outerMaterial.setDiffuseColor(Color(0xFFD8DB66));
	_innerMaterial.setAmbientColor(Color(0xFF667FFF));
	_innerMaterial.setDiffuseColor(Color(0xFFC1C6FF));

	_program = rm->getProgram("spermatozoa");
}

Ovum::~Ovum() {
	gluDeleteQuadric(_gluQuad);
}

void Ovum::update(f32) {
}

void Ovum::_drawSolid() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_program->use();

	_innerMaterial.bind();
	gluSphere(_gluQuad, RADIUS * 0.96f, 20, 60);
	_innerMaterial.unbind();
	
	_outerMaterial.bind();
	gluSphere(_gluQuad, RADIUS, 20, 60);
	_outerMaterial.unbind();

	_program->unuse();
	glDisable(GL_BLEND);
}