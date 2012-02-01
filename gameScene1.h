#pragma once

#include "gameScene.h"

#include "gamePlayer.h"
#include "Random.h"
#include "rscIManager.h"
#include "gameSubordinate.h"
#include "gameMitochondria.h"

namespace game {
	class Status;
	class Scene1 : public Scene {
	public:
		Scene1(core::shared_ptr<rsc::IManager> rm, core::shared_ptr<game::Status> status)
			: Scene(rm, 29.0f)
		{
			_player->setPosition(float3d(0.0f, 0.0f, 100.0f));

			const u32 SUBORDINATES_NUM = 100;
			for (u32 i = 0; i < SUBORDINATES_NUM; ++i) {
				core::shared_ptr<Subordinate> sub = core::make_shared<Subordinate>(rm, this);
				_nodeList.push_back(sub);
				sub->setPosition(float3d(
					core::random::getFloat(-40.0f, 40.0f),
					core::random::getFloat(-40.0f, 40.0f),
					core::random::getFloat(-80.0f, 130.0f)
				));
			}

			auto mito = core::make_shared<Mitochondria>(rm, _player, status);
			mito->setPosition(float3d(0.0f, 0.0f, 50.0f));
			_nodeList.push_back(mito);
		}
	protected:
		void _onUpdate(f32 t) {

		}

		void _setupCamera() {
			_camera.setPosition(_player->getPosition() + float3d(0.0f, 10.0f, 40.0f));
			_camera.setLookAt(_player->getPosition());
		}
	};
}