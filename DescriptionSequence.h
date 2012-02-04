#pragma once

#include "Sequence.h"

namespace rsc {
	class Texture;
}

namespace gui {
	class Background;
	class Image;
}

class DescriptionSequence : public Sequence {
	core::shared_ptr<gui::Background> _bg;
	core::shared_ptr<gui::Image> _image;
public:
	DescriptionSequence();
	
protected:
	void _update(f32);
	void _draw();
	core::shared_ptr<Sequence> _getNextSequence();
};