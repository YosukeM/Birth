#include "DescriptionSequence.h"

#include "rscTexture.h"
#include "rscSyncManager.h"

#include "inputManager.h"
#include "inputMouse.h"

#include "guiBackground.h"
#include "guiImage.h"

#include "TitleSequence.h"
#include "Application.h"

#include <GL/glfw.h>

DescriptionSequence::DescriptionSequence() {
	auto rm = Application::instance()->getResourceManager();

	_image = core::make_shared<gui::Image>(rm->getTexture("description.tga"));
	_image->setAlignType(gui::PositionalElement::EAT_CENTER_CENTER);
	_bg = core::make_shared<gui::Background>(float2d(800.0f, 450.0f));
	_bg->setColor(Color(0xFFFFFFFF));

	_fadein(1.5f);
}

void DescriptionSequence::_update(f32) {
	if (_getFadeState() == EFS_NONE) {
		if (input::Manager::instance()->getMouse()->isPressed(input::Mouse::EB_LEFT)) {
			_fadeout(1.5f);
		}
	}
}

void DescriptionSequence::_draw() {
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// “Š‰es—ñ‚ÌÝ’è
	f32 h_w_ratio =  (f32)viewport[3] / (f32)viewport[2];
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800.0, 800.0 * h_w_ratio, 0.0);
	_bg->onResize(float2d(800.0f, 800.0f * h_w_ratio));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	_bg->draw();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// GUI‚Ì•`‰æ
	glPushMatrix();
		glTranslatef(400.0f, 400.0f * h_w_ratio, 0.0f);
		_image->draw();
	glPopMatrix();

	glDisable(GL_BLEND);
	
}

core::shared_ptr<Sequence> DescriptionSequence::_getNextSequence() {
	return core::make_shared<TitleSequence>();
}