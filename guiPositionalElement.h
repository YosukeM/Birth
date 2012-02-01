#pragma once

#include "guiElement.h"

namespace gui {
	class PositionalElement : public Element {
	public:
		typedef enum {
			EAT_LEFT_TOP,
			EAT_RIGHT_TOP,
			EAT_CENTER_TOP,
			EAT_LEFT_BOTTOM,
			EAT_RIGHT_BOTTOM,
			EAT_CENTER_BOTTOM,
			EAT_LEFT_CENTER,
			EAT_RIGHT_CENTER,
			EAT_CENTER_CENTER,
		} EAlignmentType;
	protected:
		float2d _position;
		EAlignmentType _alignType;

		virtual float2d _getLeftTopPosition() const;
		virtual void _drawPositionally(const float2d&) = 0;

	public:
		PositionalElement();

		virtual float2d getSize() const = 0;
		virtual float2d getPosition() const {
			return _position;
		}
		virtual void setPosition(const float2d& pos) {
			_position = pos;
		}

		void setAlignType(EAlignmentType);

		void draw();
	};
}