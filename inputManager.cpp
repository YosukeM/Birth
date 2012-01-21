#include "inputManager.h"
#include "inputMouse.h"

using namespace input;

namespace {
	core::shared_ptr<Manager> gInputManager;
}

Manager::Manager() {
	_mouse = core::make_shared<Mouse>();
}

core::shared_ptr<Manager> Manager::instance() {
	if (!gInputManager) {
		gInputManager = core::make_shared<Manager>();
	}
	return gInputManager;
}

void Manager::update(f32 t) {
	_mouse->update(t);
}

core::shared_ptr<Mouse> Manager::getMouse() const {
	return _mouse;
}
