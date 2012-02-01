#pragma once

namespace game {
	class Status {
		u32 _playerRank;
		u32 _totalNum;
		u32 _energyNum;
	public:
		static const u32 MAX_ENERGY_NUM;
		static const u32 MAX_RIVALS_NUM;

		Status();

		u32 getPlayerRank();
		u32 getTotalNum() const;
		void setTotalNum(u32);

		void increaseEnergyNum();
		bool decreaseEnergyNum();

		void setEnergyNum(u32);
		u32 getEnergyNum() const;
	};
}