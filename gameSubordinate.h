#pragma once

#include "gameSpermatozoa.h"
#include "Angle2d.h"

namespace game {
	class Scene;

	class Subordinate : public Spermatozoa {
		Scene* _scene;
		float3d _velocity;
		Angle2d _theta;
		float _omega, _width;
	public:
		Subordinate(core::shared_ptr<rsc::IManager>, Scene* _scene);

		void update(f32);
	};
}