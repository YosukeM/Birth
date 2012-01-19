#pragma once

#include "Sequence.h"
#include "SyncResourceManager.h"

#include "Material.h"
#include "Light.h"
#include "oglPerspectiveCamera.h"

#include "oglFramebuffer.h"
#include "oglProgram.h"

namespace rsc {
	class SyncResourceManager;
}

namespace game {
	class Player;
}

class GameSequence : public Sequence {
	core::shared_ptr<rsc::SyncResourceManager> _rm;
	ogl::Light _light;
	ogl::PerspectiveCamera _camera;
	float3d _cameraPosition;

	core::shared_ptr<ogl::Texture> _colorBuffer, _depthBuffer, _blurBuffer, _blurBuffer2;
	ogl::Framebuffer _framebuffer, _framebuffer2, _framebuffer3;
	ogl::Program _blurProgram;

	core::shared_ptr<game::Player> _player;

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
