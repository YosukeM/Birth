#pragma once

#include <GL/glfw.h>

namespace input {
	class Manager;
	class Mouse {
	public:
		typedef enum {
			EB_LEFT,
			EB_RIGHT,
			EB_MIDDLE,
		} EButton;
	private:
		int2d _position;
		bool _prevButton[GLFW_MOUSE_BUTTON_LAST - GLFW_MOUSE_BUTTON_1];
		bool _nextButton[GLFW_MOUSE_BUTTON_LAST - GLFW_MOUSE_BUTTON_1];

		Mouse(const Mouse&);
	public:
		Mouse();
		void update(f32);

		bool isDown(EButton) const;
		bool isUp(EButton) const;
		bool isPressed(EButton) const;

		int2d getPosition() const;
		float3d getTransformed() const;
		core::tuple<float3d, float3d> getRay() const;
	};
}