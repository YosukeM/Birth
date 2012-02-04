#pragma once

namespace game {
	class Status {
		u32 _playerRank;
		u32 _totalNum;
		int _energyNum;
		int _ovumClickedNum;
		bool _speedUpFlag;
	public:
		static const u32 MAX_ENERGY_NUM;
		static const u32 MAX_RIVALS_NUM;

		Status();

		void update();

		bool getSpeedUpFlag() const;

		u32 getPlayerRank();
		void setPlayerRank(u32);

		u32 getTotalNum() const;
		void setTotalNum(u32);

		void increaseEnergyNum();
		bool decreaseEnergyNum();

		void setEnergyNum(u32);
		u32 getEnergyNum() const;

		void increaseOvumClickedNum();
		int getOvumClickedNum() const;
	};
}