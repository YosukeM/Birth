#pragma once

#include "guiElement.h"
#include "Color.h"

namespace rsc {
	class Texture;
}

namespace gui {
	class Background : public Element {
	public:
		typedef enum {
			EBM_MAXIMIZE,
			EBM_FIT_WIDTH,
			EBM_FIT_HEIGHT,
			EBM_INCLUDE,
		} EBackgroundMode;
	private:
		float2d _ortho;
		EBackgroundMode _mode;
		core::shared_ptr<rsc::Texture> _texture;
		Color _color;
	public:
		Background(const float2d&);

		void setMode(EBackgroundMode);
		EBackgroundMode getMode() const;

		void setColor(const Color&);
		Color getColor() const;

		void setTexture(core::shared_ptr<rsc::Texture>);
		core::shared_ptr<rsc::Texture> getTexture() const;

		void draw();
		void onResize(const float2d& ortho);
	};
}