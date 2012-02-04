#pragma once

#include "gameScene.h"

#include "gamePlayer.h"
#include "Random.h"
#include "rscIManager.h"
#include "gameSubordinate.h"

namespace game {
	class Scene3 : public Scene {
	public:
		Scene3(core::shared_ptr<rsc::IManager> rm, core::shared_ptr<game::Status> status)
			: Scene(rm, status, 16.0f)
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

			// ミトコンドリアを配置
			float2d pos;
			f32 z = 40.0f;
			for (u32 i = 1; i < 3; ++i) {
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
			f32 pos_level = abs( (0.5f - _count / _countLimit) / 0.5f);
			_camera.setPosition(
				(_player->getPosition() + float3d(10.0f, -8.0f, -50.0f)) * pos_level
				+ float3d(10.0f, _player->getPosition().y * 0.1f - 6.0f, -40.0f) * (1.0f - pos_level)
			);
			float3d up = _player->getPosition() - _camera.getPosition();
			
			const float MAX_DISTANCE = 165.0f;
			float distance = up.getLength();
			
			up = Quaternion(float3d(Angle2d::PI * 0.5f, 0.0f, 0.0f)).getRotated(up);
			_camera.setUpVector(up);

			float level = std::sqrt(distance / MAX_DISTANCE);
			_camera.setFov(Angle2d::PI / 6.0f * (1.0f - level) + Angle2d::PI / 65.0f * level);
			_camera.setLookAt(_player->getPosition());
		}
	};
}