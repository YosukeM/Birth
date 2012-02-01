#include "guiPositionalElement.h"

using namespace gui;

PositionalElement::PositionalElement()
	: _alignType(EAT_LEFT_TOP)
{

}


void PositionalElement::setAlignType(EAlignmentType at) {
	_alignType = at;
}

float2d PositionalElement::_getLeftTopPosition() const {
	float2d pos = _position;
	float2d size = getSize();

	switch (_alignType) {
	case EAT_LEFT_TOP:
	case EAT_RIGHT_TOP:
	case EAT_CENTER_TOP:
		break;
	case EAT_LEFT_BOTTOM:
	case EAT_RIGHT_BOTTOM:
	case EAT_CENTER_BOTTOM:
		pos.y -= size.y;
		break;
	case EAT_LEFT_CENTER:
	case EAT_RIGHT_CENTER:
	case EAT_CENTER_CENTER:
		pos.y -= size.y * 0.5f;
		break;
	}
	
	switch (_alignType) {
	case EAT_LEFT_TOP:
	case EAT_LEFT_BOTTOM:
	case EAT_LEFT_CENTER:
		break;
	case EAT_RIGHT_TOP:
	case EAT_RIGHT_CENTER:
	case EAT_RIGHT_BOTTOM:
		pos.x -= size.x;
		break;
	case EAT_CENTER_TOP:
	case EAT_CENTER_BOTTOM:
	case EAT_CENTER_CENTER:
		pos.x -= size.x * 0.5f;
		break;
	}

	return pos;
}

void PositionalElement::draw() {
	_drawPositionally(_getLeftTopPosition());
}