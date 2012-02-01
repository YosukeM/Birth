#pragma once

#include "guiPositionalElement.h"

#include "Color.h"

namespace rsc {
	class Texture;
}

namespace gui {
	class Image : public PositionalElement {
		core::shared_ptr<rsc::Texture> _texture;
		Color _color;
	public:
		Image(core::shared_ptr<rsc::Texture>);

		float2d getSize() const;
		core::shared_ptr<rsc::Texture> getTexture() const {
			return _texture;
		}

		void setColor(const Color& color);
		Color getColor() const;

	protected:
		virtual void _drawPositionally(const float2d&);
	};
}