#include "GameSequence.h"

#include "rscSyncManager.h"
#include "gamePlayer.h"
#include <GL/glfw.h>

#include "gameScene1.h"
#include "gameScene2.h"
#include "gameScene3.h"
#include "gameScene4.h"
#include "gameScene5.h"
#include "gameScene6.h"

#include "gameStatus.h"
#include "guiText.h"
#include "rscShader.h"
#include <gameaudio/gameaudio.h>

#include "Random.h"
#include <boost/lexical_cast.hpp>

GameSequence::GameSequence()
	: _rm(core::make_shared<rsc::SyncManager>())
{
	// リソースマネージャを初期化
	_rm->setBasePath("./data/");

	// game::Statusを初期化
	_status = core::make_shared<game::Status>();
	_initialSpermatozoaNum = std::floor(core::random::getDouble(100000000.0, 400000000.0));
	_status->setTotalNum((u32)_initialSpermatozoaNum);

	// シーンを作成
	_scenes.push_back(core::make_shared<game::Scene1>(_rm, _status));
	_scenes.push_back(core::make_shared<game::Scene2>(_rm, _status));
	_scenes.push_back(core::make_shared<game::Scene3>(_rm, _status));
	_scenes.push_back(core::make_shared<game::Scene4>(_rm, _status));
	_scenes.push_back(core::make_shared<game::Scene5>(_rm, _status));
	_scenes.push_back(core::make_shared<game::Scene6>(_rm, _status));
	for (u32 i = 1; i < _scenes.size(); ++i) {
		_scenes[i-1]->setNextSequence(_scenes[i]);
	}
	_currentScene = _scenes[5];

	// GUIの定義
	core::unordered_map<char, uint2d> map;
	for (u32 i = 0; i < 10; ++i) {
		map['0' + i] = uint2d(273.0f / 11.0f * i, 0.0f);
	}
	map['/'] = uint2d(35.45f * 10, 0.0f);
	_text = core::make_shared<gui::Text>(_rm->getTexture("numbers.tga"), uint2d(11, 1), map);

	// レンダリングパスの準備
	{
		using namespace ogl;

		// FBOを作成
		int values[4];
		glGetIntegerv(GL_VIEWPORT, values);
		_createTextures(uint2d(values[2], values[3]));

		// シェーダを読み込む
		core::shared_ptr<rsc::Shader> blur_shader = _rm->getShader("blur.frag");
		blur_shader->compile();
		_blurProgram.attach(blur_shader->getOglShader());
		_blurProgram.link();
	}

	// BGMを再生
	_bgm = gameaudio::getSoundManager().createSound("data/bgm.ogg", false, true);
}

GameSequence::~GameSequence() {
	gameaudio::getSoundManager().removeSound(_bgm);
}


void GameSequence::_createTextures(const uint2d& viewport) {
	using namespace ogl;

	// テクスチャを作る
	_colorBuffer = core::make_shared<Texture>(viewport, Texture::Source::EPS_RGB);
	_depthBuffer = core::make_shared<Texture>(viewport, Texture::Source::EPS_DEPTH);
	_blurBuffer = core::make_shared<Texture>(uint2d(viewport.x / 2, viewport.y / 2), Texture::Source::EPS_RGB);
	_blurBuffer2 = core::make_shared<Texture>(uint2d(viewport.x / 4, viewport.y / 4), Texture::Source::EPS_RGB);
	
	// フィルタを設定
	_blurBuffer->setMagFilter(Texture::EF_LINEAR);
	_blurBuffer->setMinFilter(Texture::EF_LINEAR);
	_blurBuffer2->setMagFilter(Texture::EF_LINEAR);
	_blurBuffer2->setMinFilter(Texture::EF_LINEAR);

	// FBOにアタッチ
	_framebuffer.attach(Framebuffer::EA_COLOR_0, *_colorBuffer);
	_framebuffer.attach(Framebuffer::EA_DEPTH, *_depthBuffer);
	_framebuffer2.attach(Framebuffer::EA_COLOR_0, *_blurBuffer);
	_framebuffer3.attach(Framebuffer::EA_COLOR_0, *_blurBuffer2);
}

void GameSequence::_update(f32 t) {
	// BGMを再生する
	if (!_bgm->isPlaying()) _bgm->play();

	// シーンを更新する
	core::shared_ptr<Sequence> next_scene = _currentScene->update(t);
	if (next_scene) {
		_currentScene = core::shared_dynamic_cast<game::Scene>(next_scene);
	}

	// 精子の数を計算する
	double total_num = _status->getTotalNum();
	double minus_num = total_num * t / 8.0;
	total_num -= minus_num;
	_status->setTotalNum((u32)total_num);
}

void GameSequence::onResize(const uint2d& viewport) {
	_createTextures(viewport);
}

void GameSequence::_beginPostEffect() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GameSequence::_draw() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// 基本的な3Dオブジェクトの描画
	_framebuffer.bind();
	glViewport(0, 0, viewport[2], viewport[3]);
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_currentScene->setDrawState(game::Scene::EDS_SOLID);
		_currentScene->draw();

		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		_currentScene->setDrawState(game::Scene::EDS_EFFECT);
		_currentScene->draw();
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}
	_framebuffer.unbind();

	// ぼかしをかけるために縮小バッファを作成する
	_framebuffer2.bind();
	{
		glViewport(0, 0, _blurBuffer->getSize().x, _blurBuffer->getSize().y);
		glClear(GL_COLOR_BUFFER_BIT);
		_beginPostEffect();
		_colorBuffer->draw();
	}
	_framebuffer2.unbind();
	_framebuffer3.bind();
	{
		glViewport(0, 0, _blurBuffer2->getSize().x, _blurBuffer2->getSize().y);
		glClear(GL_COLOR_BUFFER_BIT);
		_beginPostEffect();
		_blurBuffer->draw();
	}
	_framebuffer3.unbind();

	// バッファの内容をぼかしてスクリーン合成する
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	glClear(GL_COLOR_BUFFER_BIT);
	_beginPostEffect();

	_colorBuffer->draw();

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);

	_blurProgram.use();
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	_blurProgram.setUniform("textureSize", float2d(f32(_blurBuffer->getSize().x), f32(_blurBuffer->getSize().y)));
	_blurBuffer->draw();

	glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
	_blurProgram.setUniform("textureSize", float2d(f32(_blurBuffer2->getSize().x), f32(_blurBuffer2->getSize().y)));
	_blurBuffer2->draw();
	_blurProgram.unuse();

	_blurBuffer2->draw();

	glDisable(GL_BLEND);

	// GUIを描画する
	f32 w_h_ratio =  (f32)viewport[2] / (f32)viewport[3];
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 450.0 * w_h_ratio, 450.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_text->setText(boost::lexical_cast<core::string>(_status->getTotalNum()));
	_text->draw();
	glDisable(GL_BLEND);

	// フェードを描画する
	_currentScene->setDrawState(game::Scene::EDS_FADE);
	_currentScene->draw();
}

core::shared_ptr<Sequence> GameSequence::_getNextSequence() {
	return core::shared_ptr<Sequence>();
}
