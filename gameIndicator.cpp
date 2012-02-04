#include "gameIndicator.h"

#include "gameStatus.h"

#include "guiText.h"
#include "guiImage.h"
#include "guiRectangle.h"

#include "rscIManager.h"

#include <GL/glfw.h>
#include <boost/lexical_cast.hpp>

using namespace game;

Indicator::Indicator(core::shared_ptr<rsc::IManager> rm, core::shared_ptr<Status> status)
	: _status(status)
{
	// 順位表示部分
	core::unordered_map<char, uint2d> map;
	for (u32 i = 0; i < 10; ++i) {
		map['0' + i] = uint2d(90.0f / 10.0f * i, 0.0f);
	}

	_rank = core::make_shared<gui::Text>(rm->getTexture("numbers.tga"), uint2d(10, 1), map);
	auto slash = core::make_shared<gui::Image>(rm->getTexture("slash.tga"));
	_totalNum = core::make_shared<gui::Text>(rm->getTexture("numbers.tga"), uint2d(10, 1), map);

	_rank->setPosition(float2d(694, 12));
	_rank->setAlignType(gui::PositionalElement::EAT_RIGHT_TOP);
	slash->setPosition(float2d(697, 7));
	_totalNum->setPosition(float2d(708, 17));

	// ミトコンドリア残量
	auto mitochondria = core::make_shared<gui::Image>(rm->getTexture("slider.tga"));
	mitochondria->setPosition(float2d(11, 6));
	_bar = core::make_shared<gui::Rectangle>(float2d(), Color(0xB0FD8AFF));
	_bar->setPosition(mitochondria->getPosition() + float2d(7.0f, 7.0f));

	// 描画リストを設定
	_guiElements.push_back(_totalNum);
	_guiElements.push_back(_rank);
	_guiElements.push_back(slash);
	_guiElements.push_back(_bar);
	_guiElements.push_back(mitochondria);
}

void Indicator::draw(const uint2d& viewport_size) {
	// GUIを更新
	_totalNum->setText(boost::lexical_cast<core::string>(_status->getTotalNum()));
	_rank->setText(boost::lexical_cast<core::string>(_status->getPlayerRank()));
	_bar->setSize(float2d(93.0f * (f32)_status->getEnergyNum() / (f32)game::Status::MAX_ENERGY_NUM, 16));

	// 描画
	f32 w_h_ratio =  (f32)viewport_size.x / (f32)viewport_size.y;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 450.0 * w_h_ratio, 450.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	foreach (auto gui, _guiElements) {
		gui->draw();
	}

	glDisable(GL_BLEND);
}