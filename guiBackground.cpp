#include "guiBackground.h"

#include "rscTexture.h"

#include <GL/glfw.h>

using namespace gui;

Background::Background(const float2d& ortho)
	: _ortho(ortho), _mode(EBM_MAXIMIZE)
{

}

void Background::setMode(EBackgroundMode ebm) {
	_mode = ebm;
}

Background::EBackgroundMode Background::getMode() const {
	return _mode;
}

void Background::setColor(const Color& color) {
	_color = color;
}

Color Background::getColor() const {
	return _color;
}

void Background::setTexture(core::shared_ptr<rsc::Texture> texture) {
	_texture = texture;
}

core::shared_ptr<rsc::Texture> Background::getTexture() const {
	return _texture;
}

void Background::draw() {
	float color[4];
	_color.getAs4Values(color);
	glColor4f(color[0], color[1], color[2], color[3]);

	if (_texture) {
		_texture->bind();
		_texture->unbind();
	} else {
		glBegin(GL_QUADS);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(_ortho.x, 0.0f);
			glVertex2f(_ortho.x, _ortho.y);
			glVertex2f(0.0f, _ortho.y);
		glEnd();
	}

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void Background::onResize(const float2d& ortho) {
	_ortho = ortho;
}