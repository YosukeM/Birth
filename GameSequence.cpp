#include "GameSequence.h"

#include "rscSyncManager.h"
#include "gamePlayer.h"
#include <GL/glfw.h>

#include "gameScene.h"
#include "rscShader.h"
#include <gameaudio/gameaudio.h>

GameSequence::GameSequence()
	: _rm(core::make_shared<rsc::SyncManager>()),
	_sceneIndex(0)
{
	_rm->setBasePath("./data/");
	_scenes.push_back(core::make_shared<game::Scene>(_rm));

	using namespace ogl;

	// create fbo
	int values[4];
	glGetIntegerv(GL_VIEWPORT, values);
	_createTextures(uint2d(values[2], values[3]));

	// create shader
	core::shared_ptr<rsc::Shader> blur_shader = _rm->getShader("blur.frag");
	blur_shader->compile();
	_blurProgram.attach(blur_shader->getOglShader());
	_blurProgram.link();

	_bgm = gameaudio::getSoundManager().createSound("data/bgm.ogg", false, true);
	// _bgm->play();
}

GameSequence::~GameSequence() {
	gameaudio::getSoundManager().removeSound(_bgm);
}


void GameSequence::_createTextures(const uint2d& viewport) {
	using namespace ogl;

	_colorBuffer = core::make_shared<Texture>(viewport, Texture::Source::EPS_RGB);
	_depthBuffer = core::make_shared<Texture>(viewport, Texture::Source::EPS_DEPTH);
	_blurBuffer = core::make_shared<Texture>(uint2d(viewport.x / 2, viewport.y / 2), Texture::Source::EPS_RGB);
	_blurBuffer2 = core::make_shared<Texture>(uint2d(viewport.x / 4, viewport.y / 4), Texture::Source::EPS_RGB);
	
	_blurBuffer->setMagFilter(Texture::EF_LINEAR);
	_blurBuffer->setMinFilter(Texture::EF_LINEAR);
	
	_blurBuffer2->setMagFilter(Texture::EF_LINEAR);
	_blurBuffer2->setMinFilter(Texture::EF_LINEAR);

	_framebuffer.attach(Framebuffer::EA_COLOR_0, *_colorBuffer);
	_framebuffer.attach(Framebuffer::EA_DEPTH, *_depthBuffer);

	_framebuffer2.attach(Framebuffer::EA_COLOR_0, *_blurBuffer);

	_framebuffer3.attach(Framebuffer::EA_COLOR_0, *_blurBuffer2);
}

void GameSequence::_update(f32 t) {
	_scenes[_sceneIndex]->update(t);
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

		_scenes[_sceneIndex]->setDrawState(game::Scene::EDrawState::EDS_SOLID);
		_scenes[_sceneIndex]->draw();
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

	_scenes[_sceneIndex]->setDrawState(game::Scene::EDS_FADE);
	_scenes[_sceneIndex]->draw();
}

core::shared_ptr<Sequence> GameSequence::_getNextSequence() {
	return core::shared_ptr<Sequence>();
}
