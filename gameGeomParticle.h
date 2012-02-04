#pragma once

#include "Color.h"

namespace rsc {
	class Texture;
}

namespace game {
	namespace geom {
		class Particle {
		public:
			float3d position;
			float3d v;
			float life;
		};

		class Emitter {
			core::circular_buffer<Particle> _particles;
			core::shared_ptr<rsc::Texture> _texture;
		public:
			Emitter(core::shared_ptr<rsc::Texture>, u32 max_num);
			~Emitter();

			void update(f32);
			void emit(u32 num, const float3d& v, const float3d& random, float life);

			void draw(Color color);
		};
	}
}