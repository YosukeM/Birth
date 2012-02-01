#include "TitleSequence.h"

#include "rscSyncManager.h"
#include "rscTexture.h"

#include "guiImage.h"
#include "guiImageButton.h"
#include "guiBackground.h"

#include "GameSequence.h"

#include <GL/glfw.h>

TitleSequence::TitleSequence() {
	_rm = core::make_shared<rsc::SyncManager>();
	_rm->setBasePath("./data/");

	_bg = core::make_shared<gui::Background>(float2d(800.0f, 450.0f));
	_bg->setColor(Color(255, 255, 255));

	// タイトルを作る
	_title = core::make_shared<gui::Image>(_rm->getTexture("title.tga"));
	_title->setPosition(float2d(400.0f, 225.0f));
	_title->setAlignType(gui::PositionalElement::EAT_CENTER_CENTER);
	_title->getTexture()->setMinFilter(rsc::Texture::EFilter::EF_LINEAR);
	_title->getTexture()->setMagFilter(rsc::Texture::EFilter::EF_LINEAR);
	_title->setPosition(float2d(0.0f, -50.0f));

	// ボタンを作る
	_buttons.push_back(core::make_shared<gui::ImageButton>(_rm->getTexture("start.tga")));
	_buttons.push_back(core::make_shared<gui::ImageButton>(_rm->getTexture("tutorial.tga")));

	foreach (auto& button, _buttons) {
		button->setAlignType(gui::PositionalElement::EAT_CENTER_CENTER);
		button->getTexture()->setMinFilter(rsc::Texture::EFilter::EF_LINEAR);
		button->getTexture()->setMagFilter(rsc::Texture::EFilter::EF_LINEAR);
		button->onMouseover = [this] (gui::ImageButton* btn) {
			btn->setColor(Color(0xFF0000FF));
		};
		button->onMouseout = [this] (gui::ImageButton* btn) {
			btn->setColor(Color(0x000000FF));
		};
	}

	_buttons[0]->setPosition(float2d(0.0f, 100.0f));
	_buttons[1]->setPosition(float2d(0.0f, 130.0f));

	_buttons[0]->onClick = [this] (gui::ImageButton*) {
		if (_getFadeState() == Sequence::EFS_NONE) {
			_fadeout(2.0f);
		}
	};

	// フェードイン
	_fadein(2.0f);
}

TitleSequence::~TitleSequence() {
}

void TitleSequence::_update(f32 t) {
	foreach (auto& button, _buttons) {
		button->update(t);
	}
}

void TitleSequence::_draw() {
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// 投影行列の設定
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

	// GUIの描画
	glPushMatrix();
		glTranslatef(400.0f, 400.0f * h_w_ratio, 0.0f);
		_title->draw();
		foreach (auto& button, _buttons) {
			button->draw();
		}
	glPopMatrix();

	glDisable(GL_BLEND);
}

core::shared_ptr<Sequence> TitleSequence::_getNextSequence() {
	return core::make_shared<GameSequence>();
}