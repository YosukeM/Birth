#pragma once

#include "Sequence.h"
#include "gameNode.h"

#include "oglLight.h"
#include "oglPerspectiveCamera.h"

namespace rsc {
	class IManager;
}

namespace game {
	class Player;
	class Node;
	class Subordinate;
	class Enemy;
	class Item;
	class Mother;

	class Scene : public Sequence {
	public:
		typedef enum {
			EDS_SOLID = game::Node::EDS_SOLID,
			EDS_EFFECT = game::Node::EDS_EFFECT,
			EDS_FADE = game::Node::EDS_EFFECT + 1
		} EDrawState;

	protected:
		core::shared_ptr<Player> _player;
		core::list<core::shared_ptr<Node> > _nodeList;
		
		ogl::Light _light;
		ogl::PerspectiveCamera _camera;
		float3d _cameraPosition;
		EDrawState _drawState;

		f32 _count;
		f32 _countLimit;

		void _update(f32);
		void _draw();
		
		core::shared_ptr<Sequence> _getNextSequence();

	public:
		Scene(core::shared_ptr<rsc::IManager>);

		void setDrawState(EDrawState);

		void draw();
	};
}