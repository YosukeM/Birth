#include "gameSubordinate.h"

using namespace game;

Subordinate::Subordinate(core::shared_ptr<rsc::IManager>)
{
	_velocity = float3d(0.0f, 0.0f, -20.0f);
}

void Subordinate::update(f32 t) {
	_position += _velocity * t;
}

void Subordinate::_drawSolid() {

}