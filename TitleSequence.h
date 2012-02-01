#pragma once

#include "Sequence.h"

namespace rsc {
	class SyncManager;
}

namespace gui {
	class Background;
	class Image;
	class ImageButton;
}

class TitleSequence : public Sequence {
	core::shared_ptr<rsc::SyncManager> _rm;

	core::shared_ptr<gui::Background> _bg;
	core::shared_ptr<gui::Image> _title;
	core::vector<core::shared_ptr<gui::ImageButton> > _buttons;

public:
	TitleSequence();
	~TitleSequence();

protected:
	void _update(f32);
	void _draw();
	core::shared_ptr<Sequence> _getNextSequence();
};