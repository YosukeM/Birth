#include "guiImageButton.h"

#include "inputManager.h"
#include "inputMouse.h"

using namespace gui;

ImageButton::ImageButton(core::shared_ptr<rsc::Texture> tex)
	: Image(tex), _isMouseout(true)
{
}

void ImageButton::update(f32) {
	auto mouse = input::Manager::instance()->getMouse();
	if (!_isMouseout && mouse->isPressed(input::Mouse::EB_LEFT)) {
		if (onClick) onClick(this);
	}
}

void ImageButton::draw() {
	auto mouse = input::Manager::instance()->getMouse();

	float2d lt= _getLeftTopPosition();
	float2d rb = _getLeftTopPosition() + getSize();

	float3d pos = mouse->getTransformed();
	if (lt.x < pos.x && pos.x <= rb.x && lt.y < pos.y && pos.y <= rb.y) {
		if (!_isMouseout) {
			if (onMouseover) onMouseover(this);
		}
		_isMouseout = false;
	} else {
		if (_isMouseout) {
			if (onMouseout) onMouseout(this);
		}
		_isMouseout = true;
	}

	Image::draw();
}