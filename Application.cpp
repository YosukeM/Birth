#include "Application.h"

#include "rscMesh.h"
#include "oglMeshbuffer.h"

#include "Error.h"

#include "Sequence.h"
#include "TitleSequence.h"
#include "GameSequence.h"

#include "rscSyncManager.h"

#include <GL/glfw.h>
#include <gameaudio/gameaudio.h>
#include <boost/lexical_cast.hpp>

namespace {
	Application *gApp = NULL;
}


bool Application::hasInstance() {
	return gApp != NULL;
}

Application* Application::instance() {
	if (!gApp) {
		gApp = new Application();
		gApp->init();
	}
	return gApp;
}

void Application::deleteInstance() {
	delete gApp;
	gApp = NULL;
}

Application::Application()
	: _bgm(NULL)
{
}

void Application::init() {
	// Extensionsを確認
	_checkExtensions();

	// BGM
	_bgm = gameaudio::getSoundManager().createSound("data/bgm.ogg", false, false);

	// リソースマネージャ
	_rm = core::make_shared<rsc::SyncManager>();
	_rm->setBasePath("./data/");

	// Sequenceをロードする
	using namespace core;
	_seq = shared_static_cast<Sequence>(make_shared<TitleSequence>());
}

Application::~Application() {
	if (_bgm) gameaudio::getSoundManager().removeSound(_bgm);
}

void Application::_checkExtensions() {
	core::vector<core::string> errors;

	// Extensionの有無を調べる
	if (!GLEW_EXT_framebuffer_object) errors.push_back("Framebuffer object is not supported");
	if (!GLEW_EXT_texture_rectangle) errors.push_back("Texture rectangle is not supported");

	// OpenGLのバージョンを調べる
	// バージョンの書式に関する規格がないので、パースの仕方は適当である。
	try {
		core::string version(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		if (version.size() > 3) {
			double v = boost::lexical_cast<double>(version.substr(0, 3));
			if (v < 2.0) errors.push_back(core::string("Your OpenGL version is ") + version + ", require 2.0 or greater");
		}
	} catch (...) {
	}

	// エラーがあったら投げる
	if (errors.size()) {
		core::string message;
		foreach (const core::string& str, errors) {
			message += str + "\n";
		}
		throw Error(message);
	}
}

void Application::update(f32 delta_time) {
	if (delta_time > 1.0f) delta_time = 1.0f;

	// 最小フレームレートを60とする。
	f32 internal_frames_num = std::ceil(delta_time / (1.0f / 60.0f));
	f32 small_dt = delta_time / internal_frames_num;

	// Sequenceをupdate
	core::shared_ptr<Sequence> next_seq;
	for (u32 counter = u32(internal_frames_num); counter > 0; --counter) {
		next_seq = _seq->update(small_dt);
		if (next_seq) {
			_seq = next_seq;
			next_seq.reset();
		}
	}

	// 描画
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_seq->draw();
}

void Application::onResize(const uint2d& viewport_size) {
	_seq->onResize(viewport_size);
}

bool Application::onClose() {
	return true;
}

gameaudio::ISound* Application::getBGM() const {
	return _bgm;
}

core::shared_ptr<rsc::SyncManager> Application::getResourceManager() const {
	return _rm;
}
