#pragma once

namespace input {
	class Manager;
	class Mouse {
		int2d _position;

		Mouse(const Mouse&);
	public:
		Mouse();
		void update(f32);

		int2d getPosition() const;
		core::tuple<float3d, float3d> getRay() const;
	};
}