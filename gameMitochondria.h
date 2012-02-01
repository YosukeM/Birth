#pragma once

#include "gameNode.h"

namespace rsc {
	class Texture;
	class IManager;
}

namespace game {
	class Player;
	class Status;

	class Mitochondria : public Node {
		core::shared_ptr<rsc::Texture> _texture;
		core::shared_ptr<Player> _player;
		core::shared_ptr<Status> _status;
		bool _isPickedUp;
	public:
		const static float RADIUS;

		Mitochondria(core::shared_ptr<rsc::IManager>, core::shared_ptr<Player> player, core::shared_ptr<Status>);
		void update(float);

	protected:
		void _drawEffect();
	};
}