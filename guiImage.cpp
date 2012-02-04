#include "guiImage.h"
#include "rscTexture.h"

#include <GL/glfw.h>

using namespace gui;

Image::Image(core::shared_ptr<rsc::Texture> tex)
	: _texture(tex), _color(0xFFFFFFFF)
{
}

float2d Image::getSize() const {
	return float2d((f32)_texture->getSize().x, (f32)_texture->getSize().y);
}

void Image::setColor(const Color& color) {
	_color = color;
}

Color Image::getColor() const {
	return _color;
}

void Image::_drawPositionally(const float2d& pos) {
	float color[4];
	_color.getAs4Values(color);
	glColor4f(color[0], color[1], color[2], color[3]);
	_texture->bind();

	float2d texsize = _texture->getRBTexCoord();
	float2d size = getSize();
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, texsize.y);
		glVertex2f(pos.x, pos.y);
		glTexCoord2f(texsize.x, texsize.y);
		glVertex2f(pos.x + size.x, pos.y);
		glTexCoord2f(texsize.x, 0.0f);
		glVertex2f(pos.x + size.x, pos.y + size.y);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(pos.x, pos.y + size.y);
	glEnd();

	_texture->unbind();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}