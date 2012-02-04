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
	class Ovum;
	class Status;

	namespace geom {
		class Emitter;
	}

	class Player : public Spermatozoa {
		Angle2d _theta;
		float2d _pointer;

		core::shared_ptr<rsc::IManager> _rm;
		core::scoped_ptr<geom::Emitter> _emitter;
		bool _hasOvumAttached;

		float _speedUpCounter;

		core::shared_ptr<Status> _status;

		void _onDraw();
		void _updateAttached(float);
		void _drawEffect();

	public:
		static const float RADIUS;

		Player(core::shared_ptr<rsc::IManager>, core::shared_ptr<Status>);

		void update(float);

		void setOvum(core::shared_ptr<Ovum>);

		bool isOvumAttached() const;
	};
}
