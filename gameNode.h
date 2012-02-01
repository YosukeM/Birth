#pragma once

#include "Quaternion.h"

namespace game {

	/*
	 * game::Node�̓Q�[�����ŕ\������I�u�W�F�N�g�̊��N���X
	 */

	class Node {
	protected:
		float3d _position;
		Quaternion _rotation;

		virtual void _drawSolid() {}
		virtual void _drawEffect() {}

	protected:
		Node() {}

	public:
		typedef enum {
			EDS_SOLID,
			EDS_EFFECT,
		} EDrawState;

		virtual ~Node() {}

		float3d getPosition() const;
		void setPosition(const float3d&);

		Quaternion getRotation() const;
		void setRotation(const Quaternion&);

		virtual void update(float) {}
		virtual void draw(EDrawState);
	};
}