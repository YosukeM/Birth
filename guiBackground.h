#pragma once

#include "guiElement.h"

namespace rsc {
	class Texture;
}

namespace gui {
	class Background : public Element {
		core::shared_ptr<rsc::Texture> _texture;
	public:
		Background();

		void draw();
	};
}