#pragma once

#include "guiImage.h"

namespace gui {
	class ImageButton : public Image {
		bool _isMouseout;
	public:
		ImageButton(core::shared_ptr<rsc::Texture>);

		virtual void update(f32);

		virtual void draw();

		core::function<void(ImageButton*)> onClick;
		core::function<void(ImageButton*)> onMouseover;
		core::function<void(ImageButton*)> onMouseout;
	};
}