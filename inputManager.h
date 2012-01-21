#pragma once

namespace input {
	class Mouse;
	class Keyboard;
	class Joypad;

	class Manager {
		core::shared_ptr<Mouse> _mouse;
		core::shared_ptr<Keyboard> _keyboard;
		Manager(const Manager&);
	public:
		static core::shared_ptr<Manager> instance();
		
		Manager();
		void update(f32);

		core::shared_ptr<Mouse> getMouse() const;
	};
}