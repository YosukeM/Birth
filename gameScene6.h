#pragma once

#include "gameScene.h"

#include "gamePlayer.h"
#include "Random.h"
#include "rscIManager.h"
#include "gameSubordinate.h"
#include "gameOvum.h"

#include "TitleSequence.h"
#include "gameStatus.h"
#include "inputManager.h"
#include "inputMouse.h"

namespace game {
	class Scene6 : public Scene {
		core::shared_ptr<Ovum> _ovum;
		core::list<core::shared_ptr<Subordinate> > _subordinates;
		
		static const u32 SUBORDINATES_NUM = 80;
		int _playerRank, _realRank;
		int _totalNum;
		u32 _subordinatesNum;
		core::shared_ptr<game::Status> _status;
		bool _hasAttached;

		double _pTime, _tTime;
		bool _hasBegan;

	public:
		Scene6(core::shared_ptr<rsc::IManager> rm, core::shared_ptr<game::Status> status)
			: Scene(rm, status, 38.0f),
			_status(status), _pTime(0.0f), _tTime(0.0f),
			_hasAttached(false), _hasBegan(false)
		{
			_player->setPosition(float3d(0.0f, 0.0f, 400.0f));
			_subordinatesNum = core::random::getInt(SUBORDINATES_NUM, SUBORDINATES_NUM * 3);

			// 他の精子を配置
			for (u32 i = 0; i < SUBORDINATES_NUM; ++i) {
				core::shared_ptr<Subordinate> sub = core::make_shared<Subordinate>(rm, this);
				_nodeList.push_back(sub);
				_subordinates.push_back(sub);
				sub->setPosition(float3d(
					core::random::getFloat(-150.0f, 150.0f),
					core::random::getFloat(-120.0f, 120.0f),
					core::random::getFloat(-170.0f, 450.0f))
				);
			}

			// 卵子を配置
			_ovum = core::make_shared<Ovum>(rm);
			_ovum->setPosition(float3d(0.0f, 0.0f, -100.0f));
			_nodeList.push_back(_ovum);
		}
	protected:
		void _onUpdate(f32 t) {
			if (!_hasBegan) {
				// 最初のフレーム
				_playerRank = _status->getPlayerRank() / 3;
				_totalNum = _status->getTotalNum() / 3;
				_hasBegan = true;
			}

			// 精子が卵子に向かうように設定
			if (_count > 15.0f && _count - t <= 15.0f) {
				foreach (auto sub, _subordinates) {
					sub->setOvum(_ovum);
				}
				_player->setOvum(_ovum);
			}

			// プレイヤーの順位を実際の順位に近づける
			if (!_player->isOvumAttached()) {
				_realRank = 1;
				f32 distance_sq = (_ovum->getPosition() - _player->getPosition()).getLengthSQ();
				foreach (auto sub, _subordinates) {
					if ((sub->getPosition() - _ovum->getPosition()).getLengthSQ() <= distance_sq) {
						_realRank++;
					}
				}
				int prev_player_rank = _playerRank;
				if (_count < 15.0f) {
					_playerRank -= std::floor((_playerRank - _realRank) / 30.0 * _pTime);
				} else {
					_playerRank -= std::floor((_playerRank - _realRank) / 5.0 * _pTime);
				}
				if (_playerRank == prev_player_rank) {
					_pTime += t;
				}
				if (_playerRank < _realRank || _playerRank > 1000000) _playerRank = _realRank;
			} else {
				if (!_hasAttached) {
					_playerRank = _realRank;
					_hasAttached = true;
				}
				if (core::random::getFloat() > 0.95) {
					_playerRank++;
				}
				if (input::Manager::instance()->getMouse()->isPressed(input::Mouse::EB_LEFT)) {
					if (core::random::getFloat() > 0.8f) {
						_playerRank--;
					}
				}
				if (_playerRank <= 0) _playerRank = 1;
				if (_playerRank > SUBORDINATES_NUM) _playerRank = SUBORDINATES_NUM;
			}

			// 精子の総数を徐々に減らす
			int prev_total_num = _totalNum;
			if (_totalNum > _subordinatesNum + 1) {
				_totalNum -= std::floor((_totalNum - (_subordinatesNum + 1)) / 1000.0 * _tTime);
				if (prev_total_num == _totalNum) {
					_tTime += t;
				}
			}

			_status->setPlayerRank(_playerRank);
			_status->setTotalNum(_totalNum);
		}

		void _setupCamera() {
			_camera.setFar(1000.0f);
			_camera.setNear(5.0f);

			float3d target = _player->getPosition() + float3d(0.0f, 0.0f, -1.3f);
			float far = 1.0f;
			float r = 0.0f;
			if (_count < 12.0f) {
				r = 1.0f - _count / 12.0f;
			}
			if (_count < 8.0f) {
				far = 1.0f + pow(_count / 8.0f, 32.0f * 8.0f / 12.0f);
			} else if (_count < 20.0f) {
				far = 2.0f + 32.0f / (20.0f - 8.0f) * (_count - 8.0f);
			} else {
				float level = 0.0f;
				f32 time = (_count - 20.0f) / (39.0f - 20.0f);
				level = sqrt(sin(time * Angle2d::PI * 0.5f));
				far = 34.0f - 32.5f * level;
			}

			if (_count < 12.0f) {
				Angle2d theta = (_count / 12.0f - 1.0f) * Angle2d::PI;
				_camera.setPosition(
					_player->getPosition()
					+ float3d(10.0f * theta.sin() * r, 10.0f * far, 30.0f * theta.cos() * r)
				);
			} else {
				_camera.setPosition(
					_player->getPosition()
					+ float3d(0.0f, 10.0f * far, 0.0f)
				);
			}

			if (8.0f < _count) {
				float level;
				if ( _count < 20.0f) {
					level = std::abs(_count - 8.0f) / 24.0f;
					level = 0.5f - 0.5f * sin(level * Angle2d::PI - Angle2d::PI * 0.5f);
				} else {
					level = std::abs(_count - 20.0f) / 12.0f + 0.5f;
					if (level > 1.0f) level = 1.0f;
					level = 0.5f + 0.5f * sin(level * Angle2d::PI - Angle2d::PI * 0.5f);
				}
				target = target * level + _ovum->getPosition() * (1.0f - level);
			}

			_camera.setLookAt(target);
		}

		core::shared_ptr<Sequence> _getNextSequence() {
			return core::shared_static_cast<Sequence>(core::make_shared<TitleSequence>());
		}
	};
}