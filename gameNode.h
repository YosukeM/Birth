#pragma once

namespace game {
	class Node {
	public:
		Node() {}
		virtual ~Node() {}

		virtual void update(float) = 0;
		virtual void render() = 0;
	};
}