#include "gameStatus.h"

using namespace game;

const u32 Status::MAX_RIVALS_NUM = 3000000;
const u32 Status::MAX_ENERGY_NUM = 8;

Status::Status()
	: _playerRank(100), _totalNum(100), _energyNum(MAX_ENERGY_NUM)
{

}

u32 Status::getPlayerRank() {
	return _playerRank;
}

u32 Status::getTotalNum() const {
	return _totalNum;
}

void Status::setTotalNum(u32 v) {
	_totalNum = v;
}

void Status::increaseEnergyNum() {
	_energyNum++;
}

bool Status::decreaseEnergyNum() {
	_energyNum--;
	if (_energyNum < 0) {
		_energyNum = 0;
		return false;
	} else {
		return true;
	}
}

void Status::setEnergyNum(u32 n) {
	assert(0 <= n && n <= MAX_ENERGY_NUM);

}

u32 Status::getEnergyNum() const {
	return _energyNum;
}