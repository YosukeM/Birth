#pragma once

#include "gameScene.h"

#include "gamePlayer.h"
#include "Random.h"
#include "rscIManager.h"
#include "gameSubordinate.h"

namespace game {
	class Scene5 : public Scene {
	public:
		Scene5(core::shared_ptr<rsc::IManager> rm, core::shared_ptr<game::Status> status)
			: Scene(rm, status, 16.0f)
		{
			_player->setPosition(float3d(0.0f, 0.0f, 100.0f));

			// 他の精子を配置
			const u32 SUBORDINATES_NUM = 100;
			for (u32 i = 0; i < SUBORDINATES_NUM; ++i) {
				core::shared_ptr<Subordinate> sub = core::make_shared<Subordinate>(rm, this);
				_nodeList.push_back(sub);
				sub->setPosition(float3d(
					core::random::getFloat(-40.0f, 40.0f),
					core::random::getFloat(-40.0f, 40.0f),
					core::random::getFloat(-80.0f, 120.0f))
				);
			}

			// ミトコンドリアを配置
			float2d pos;
			f32 z = 20.0f;
			for (u32 i = 0; i < 6; ++i) {
				auto mito = core::make_shared<Mitochondria>(rm, _player, status);
				mito->setPosition(float3d(pos.x, pos.y, z));
				_nodeList.push_back(mito);
				z += -50.0f;
				pos.x += core::random::getFloat(-5.0f, 5.0f);
				pos.y += core::random::getFloat(-2.0f, 2.0f);
			}
			
			// カメラ位置を初期化
			float3d campos = _player->getPosition() + float3d(2.0f, 2.0f, 12.0f);
			float3d lookat = _player->getPosition() + float3d(0, 0, -30.0f);
			_camera.setPosition(campos);
			_camera.setLookAt(lookat);
		}
	protected:
		void _onUpdate(f32 t) {

		}

		void _setupCamera() {
			f32 level = 1.5f * _count / _countLimit;
			level = 1.0f + pow(level, 2);

			float3d pos = _player->getPosition() + float3d(2.0f, 2.0f, 12.0f) * level;
			float3d lookat = _player->getPosition() + float3d(0, 0, -30.0f);
			_camera.setPosition( _camera.getPosition() + (pos - _camera.getPosition()) * 0.1f );
			_camera.setLookAt( _camera.getLookAt() + (lookat - _camera.getLookAt()) * 0.1f );
		}
	};
}