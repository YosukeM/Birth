#pragma once

#include "gameNode.h"

namespace rsc {
	class IManager;
}

namespace game {
	class Subordinate : public Node {
	public:
		Subordinate(core::shared_ptr<rsc::IManager>);

		void update(f32);
	protected:
		float3d _velocity;
		void _drawSolid();
	};
}