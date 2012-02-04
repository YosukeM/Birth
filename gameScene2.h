#pragma once

#include "gameScene.h"

#include "gamePlayer.h"
#include "Random.h"
#include "rscIManager.h"
#include "gameSubordinate.h"

namespace game {
	class Scene2 : public Scene {
	public:
		Scene2(core::shared_ptr<rsc::IManager> rm, core::shared_ptr<game::Status> status)
			: Scene(rm, status, 14.0f)
		{
			_player->setPosition(float3d(0.0f, 0.0f, 160.0f));

			// 精子を配置
			const u32 SUBORDINATES_NUM = 100;
			for (u32 i = 0; i < SUBORDINATES_NUM; ++i) {
				core::shared_ptr<Subordinate> sub = core::make_shared<Subordinate>(rm, this);
				_nodeList.push_back(sub);
				sub->setPosition(float3d(
					core::random::getFloat(-40.0f, 40.0f),
					core::random::getFloat(-40.0f, 40.0f),
					160.0f + core::random::getFloat(-100.0f, 100.0f))
				);
			}

			// ミトコンドリアを配置
			float2d pos;
			f32 z = 80.0f;
			for (u32 i = 1; i < 4; ++i) {
				auto mito = core::make_shared<Mitochondria>(rm, _player, status);
				mito->setPosition(float3d(pos.x, pos.y, z));
				_nodeList.push_back(mito);
				z += -50.0f;
				pos += Angle2d(core::random::getFloat(0.0f, Angle2d::PI * 2.0f)).getVector() * 5.0f;
			}

		}
	protected:
		void _onUpdate(f32 t) {

		}

		void _setupCamera() {
			_camera.setPosition(float3d(-15.0f, 0.0f, 0.0f));
			_camera.setLookAt(_player->getPosition());
		}
	};
}