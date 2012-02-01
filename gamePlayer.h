#pragma once

#include "gameSpermatozoa.h"
#include "oglMaterial.h"
#include "rscMesh.h"
#include "rscProgram.h"
#include "Angle2d.h"

#include "gameGeomTail.h"

namespace rsc {
	class IManager;
}

namespace game {
	class Player : public Spermatozoa {
		Angle2d _theta;
		float2d _pointer;

		float _speedUpCounter;

		void _onDraw();

	public:
		static const float RADIUS;

		Player(core::shared_ptr<rsc::IManager>);

		void update(float);
	};
}
