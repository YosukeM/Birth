#include "TitleSequence.h"

TitleSequence::TitleSequence() {
	_rm = core::make_shared<rsc::SyncResourceManager>();
}

TitleSequence::~TitleSequence() {
}

void TitleSequence::_update(f32) {
	
}

void TitleSequence::_draw() {

}

core::shared_ptr<Sequence> TitleSequence::_getNextSequence() {
	return core::shared_ptr<Sequence>();
}