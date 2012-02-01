#pragma once

#include "gameScene.h"

#include "gamePlayer.h"
#include "Random.h"
#include "rscIManager.h"
#include "gameSubordinate.h"

namespace game {
	class Scene4 : public Scene {
	public:
		Scene4(core::shared_ptr<rsc::IManager> rm, core::shared_ptr<game::Status> status)
			: Scene(rm, 14.0f)
		{
			_player->setPosition(float3d(0.0f, 0.0f, 100.0f));

			const u32 SUBORDINATES_NUM = 100;
			for (u32 i = 0; i < SUBORDINATES_NUM; ++i) {
				core::shared_ptr<Subordinate> sub = core::make_shared<Subordinate>(rm, this);
				_nodeList.push_back(sub);
				sub->setPosition(float3d(
					core::random::getFloat(-40.0f, 40.0f),
					core::random::getFloat(-40.0f, 40.0f),
					100.0f + core::random::getFloat(-100.0f, 100.0f))
				);
			}
		}
	protected:
		void _onUpdate(f32 t) {

		}

		void _setupCamera() {
			_camera.setPosition(_player->getPosition() + float3d(- 15.0f, 30.0f, 7.0f));
			_camera.setLookAt(_player->getPosition() + float3d(0, 0, 0.0f));
		}
	};
}