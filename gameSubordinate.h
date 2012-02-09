#pragma once

#include "gameSpermatozoa.h"
#include "Angle2d.h"

namespace rsc {
	class Texture;
}

namespace game {
	class Scene;

	namespace geom {
		class Emitter;
	}

	class Subordinate : public Spermatozoa {
		Scene* _scene;
		float3d _velocity;
		Angle2d _theta;
		float _speed;
		float _omega, _width;
		bool _hasOvumAttached;
		core::shared_ptr<rsc::Texture> _particleTex;
		core::shared_ptr<geom::Emitter> _emitter;

		void _drawEffect();

	public:
		Subordinate(core::shared_ptr<rsc::IManager>, Scene* _scene);

		void update(f32);

		void setOvum(core::shared_ptr<Ovum>);

		bool hasOvumAttached() const { return _hasOvumAttached; }
	};
}