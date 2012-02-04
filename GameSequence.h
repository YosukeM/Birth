#pragma once

#include "Sequence.h"
#include "rscSyncManager.h"

#include "oglMaterial.h"
#include "oglLight.h"
#include "oglPerspectiveCamera.h"

#include "oglFramebuffer.h"
#include "oglProgram.h"

namespace rsc {
	class SyncResourceManager;
}

namespace game {
	class Scene;
	class Status;
	class Indicator;
}

namespace gui {
	class Text;
}

namespace gameaudio {
	class ISound;
}

class Application;

/**
 * GameSequenceはゲーム全体のシーンの流れを制御する。
 * 適切な順番でシーンの描画メソッドを呼び、それにポストエフェクトを加えて、
 * 最終的な画面を出力する。
 */

class GameSequence : public Sequence {
	core::shared_ptr<rsc::SyncManager> _rm;

	core::vector<core::shared_ptr<game::Scene> > _scenes;
	core::shared_ptr<game::Scene> _currentScene;

	core::shared_ptr<ogl::Texture> _colorBuffer, _depthBuffer, _blurBuffer, _blurBuffer2;
	ogl::Framebuffer _framebuffer, _framebuffer2, _framebuffer3;
	ogl::Program _blurProgram;

	core::shared_ptr<game::Status> _status;
	core::shared_ptr<game::Indicator> _indicator;
	core::shared_ptr<Sequence> _nextSequence;
	double _initialSpermatozoaNum;
	double _playerRank;

	u32 _sceneIndex;

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
