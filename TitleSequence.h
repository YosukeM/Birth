#pragma once

#include "Sequence.h"

namespace rsc {
	class SyncManager;
}

namespace gui {
	class BackgroundImage;
	class Button;
}

class TitleSequence : public Sequence {
	core::shared_ptr<rsc::SyncManager> _rm;

	core::shared_ptr<gui::BackgroundImage> _bg;
	core::vector<core::shared_ptr<gui::Button>> _buttons;

public:
	TitleSequence();
	~TitleSequence();

protected:
	void _update(f32);
	void _draw();
	core::shared_ptr<Sequence> _getNextSequence();
};