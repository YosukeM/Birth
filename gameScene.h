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
	class Status;

	/**
	 * game::Sceneはカメラの1カットに相当する
	 */
	class Scene : public Sequence {
	public:
		typedef enum {
			EDS_SOLID = game::Node::EDS_SOLID,
			EDS_EFFECT = game::Node::EDS_EFFECT,
			EDS_FADE = game::Node::EDS_EFFECT + 1
		} EDrawState;

		void _update(f32);
		void _draw();

	protected:
		core::shared_ptr<Player> _player;
		core::list<core::shared_ptr<Node> > _nodeList;
		
		ogl::Light _light;
		ogl::PerspectiveCamera _camera;
		EDrawState _drawState;

		f32 _count;
		f32 _countLimit;
		core::shared_ptr<Sequence> _nextSequence;
		
		core::shared_ptr<Sequence> _getNextSequence();

		virtual void _onUpdate(float t) = 0;
		virtual void _setupCamera() = 0;

	public:
		Scene(core::shared_ptr<rsc::IManager>, core::shared_ptr<Status>, float length);

		void init();

		void setNextSequence(core::shared_ptr<Sequence>);

		void setDrawState(EDrawState);

		void draw();

		f32 getCountLimit() const { return _countLimit; }
	};
}