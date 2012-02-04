#pragma once

#include "guiPositionalElement.h"

#include "Color.h"

namespace gui {
	class Rectangle : public PositionalElement {
		Color _color;
		float2d _size;
	public:
		Rectangle(const float2d& size, const Color&);

		void setSize(const float2d&);
		float2d getSize() const;

		void setColor(const Color& color);
		Color getColor() const;

	protected:
		virtual void _drawPositionally(const float2d&);
	};
}