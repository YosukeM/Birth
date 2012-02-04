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
			: Scene(rm, status, 29.0f)
		{
			_player->setPosition(float3d(0.0f, 0.0f, 100.0f));

			// 他の精子を配置
			const u32 SUBORDINATES_NUM = 120;
			for (u32 i = 0; i < SUBORDINATES_NUM; ++i) {
				core::shared_ptr<Subordinate> sub = core::make_shared<Subordinate>(rm, this);
				_nodeList.push_back(sub);
				sub->setPosition(float3d(
					core::random::getFloat(-40.0f, 40.0f),
					core::random::getFloat(-40.0f, 40.0f),
					core::random::getFloat(-130.0f, 110.0f)
				));
			}

			// ミトコンドリアを配置
			float2d pos;
			f32 z = -50.0f;
			for (u32 i = 0; i < 11; ++i) {
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
			float3d pos = _player->getPosition() + float3d(0.0f, 10.0f, 40.0f);
			float3d lookat = _player->getPosition();
			_camera.setPosition( _camera.getPosition() + (pos - _camera.getPosition()) * 0.3f );
			_camera.setLookAt( _camera.getLookAt() + (lookat - _camera.getLookAt()) * 0.3f );
		}
	};
}