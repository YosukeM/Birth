#pragma once

namespace rsc {
	class IManager;
	class Texture;
}

namespace gui {
	class Text;
	class Image;
	class Element;
	class Rectangle;
}

namespace game {
	class Status;

	class Indicator {
		core::shared_ptr<Status> _status;
		core::shared_ptr<gui::Text> _rank, _totalNum;
		core::shared_ptr<gui::Rectangle> _bar;
		core::vector<core::shared_ptr<gui::Element> > _guiElements;
	public:
		Indicator(core::shared_ptr<rsc::IManager>, core::shared_ptr<Status>);
		void draw(const uint2d& viewport_size);
	};
}