#pragma once

#include "Sequence.h"
#include "rscSyncManager.h"

#include "oglMaterial.h"
#include "oglLight.h"
#include "oglPerspectiveCamera.h"

#include "oglFramebuffer.h"
#include "oglProgram.h"

#include "gameScene.h"

namespace rsc {
	class SyncResourceManager;
}

namespace game {
	class Player;
}

namespace gameaudio {
	class ISound;
}

class GameSequence : public Sequence {
	core::shared_ptr<rsc::SyncManager> _rm;

	core::vector<core::shared_ptr<game::Scene> > _scenes;
	u32 _sceneIndex;

	core::shared_ptr<ogl::Texture> _colorBuffer, _depthBuffer, _blurBuffer, _blurBuffer2;
	ogl::Framebuffer _framebuffer, _framebuffer2, _framebuffer3;
	ogl::Program _blurProgram;

	gameaudio::ISound* _bgm;

	void _createTextures(const uint2d& viewport);
	void _beginPostEffect();

public:
	GameSequence();
	~GameSequence();

protected:
	void _update(f32);
	void _draw();
	core::shared_ptr<Sequence> _getNextSequence();

	void onResize(const uint2d&);
};
