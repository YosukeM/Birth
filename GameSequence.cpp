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
#include "gameIndicator.h"
#include "guiText.h"
#include "rscShader.h"
#include <gameaudio/gameaudio.h>

#include "Random.h"
#include "Application.h"

GameSequence::GameSequence()
	: _rm(Application::instance()->getResourceManager())
{
	// game::Statusを初期化
	_status = core::make_shared<game::Status>();
	_initialSpermatozoaNum = std::floor(core::random::getDouble(100000000.0, 400000000.0));
	_playerRank = core::random::getDouble(0.4, 0.7);
	_status->setTotalNum((u32)_initialSpermatozoaNum);
	_status->setPlayerRank((u32)(_initialSpermatozoaNum * _playerRank));

	// game::Indicatorを初期化
	_indicator = core::make_shared<game::Indicator>(_rm, _status);

	// シーンを作成
	const u32 CURRENT_SCENE = 0;
	_scenes.push_back(core::make_shared<game::Scene1>(_rm, _status));
	_scenes.push_back(core::make_shared<game::Scene2>(_rm, _status));
	_scenes.push_back(core::make_shared<game::Scene3>(_rm, _status));
	_scenes.push_back(core::make_shared<game::Scene4>(_rm, _status));
	_scenes.push_back(core::make_shared<game::Scene5>(_rm, _status));
	_scenes.push_back(core::make_shared<game::Scene6>(_rm, _status));
	for (u32 i = 1; i < _scenes.size(); ++i) {
		_scenes[i-1]->setNextSequence(_scenes[i]);
	}
	_currentScene = _scenes[CURRENT_SCENE];
	_sceneIndex = CURRENT_SCENE;

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
	f32 seek = 0.0f;
	for (u32 i = 0; i < CURRENT_SCENE; ++i) {
		seek += _scenes[i]->getCountLimit();
	}
	gameaudio::ISound* bgm = Application::instance()->getBGM();
	bgm->setGain(1.0f);
	bgm->setPlayPositionBySecs(seek);
	bgm->play();
}

GameSequence::~GameSequence() {
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
	// シーンを更新する
	core::shared_ptr<Sequence> next_scene = _currentScene->update(t);
	if (next_scene) {
		_sceneIndex++;
		try {
			_currentScene = core::shared_dynamic_cast<game::Scene>(next_scene);
			if (!_currentScene) {
				_nextSequence = next_scene;
				_fadeout(0.0f);
			}
		} catch (...) {
			_nextSequence = next_scene;
			_fadeout(0.0f);
		}
	}

	// 精子の数を計算する
	if (_sceneIndex != 5) {
		double total_num = _status->getTotalNum();
		double minus_num = total_num * t / 8.0;
		total_num -= minus_num;
		_status->setTotalNum((u32)total_num);
		_status->setPlayerRank((u32)(total_num * _playerRank));
	}

	if (_status->getSpeedUpFlag()) {
		_playerRank -= 0.02;
	}
	_status->update();
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

	if (!_currentScene) return;

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
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
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
	_indicator->draw(uint2d(viewport[2], viewport[3]));

	// フェードを描画する
	_currentScene->setDrawState(game::Scene::EDS_FADE);
	_currentScene->draw();
}

core::shared_ptr<Sequence> GameSequence::_getNextSequence() {
	return _nextSequence;
}
