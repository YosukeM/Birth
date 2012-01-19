#pragma once

namespace gui {
	class Element {
	protected:
		Element() {}
		
	public:
		virtual ~Element() {}
		virtual void draw() = 0;
	};
}