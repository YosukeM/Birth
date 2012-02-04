#include "guiRectangle.h"

#include <GL/glfw.h>

using namespace gui;

Rectangle::Rectangle(const float2d& size, const Color& color)
	: _size(size), _color(color)
{
}

void Rectangle::setSize(const float2d& size) {
	_size = size;
}

float2d Rectangle::getSize() const {
	return _size;
}

void Rectangle::setColor(const Color& color) {
	_color = color;
}

Color Rectangle::getColor() const {
	return _color;
}

void Rectangle::_drawPositionally(const float2d& pos) {
	float color[4];
	_color.getAs4Values(color);
	glColor4f(color[0], color[1], color[2], color[3]);

	glBegin(GL_QUADS);
		glVertex2f(pos.x, pos.y);
		glVertex2f(pos.x + _size.x, pos.y);
		glVertex2f(pos.x + _size.x, pos.y + _size.y);
		glVertex2f(pos.x, pos.y + _size.y);
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}