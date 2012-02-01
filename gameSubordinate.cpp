#include "gameSubordinate.h"
#include "Random.h"

using namespace game;

Subordinate::Subordinate(core::shared_ptr<rsc::IManager> rm, Scene* scene)
	: Spermatozoa(rm), _scene(scene)
{
	// 速度をランダムに決める
	_velocity = float3d(0.0f, 0.0f, core::random::getFloat(-21.0f, -14.0f));

	// 尻尾の振れ方をランダムに決める
	_theta = core::random::getFloat(0.0f, 2.0f * Angle2d::PI);
	_omega = core::random::getFloat(0.8f, 1.2f);
	_width = core::random::getFloat(0.35f, 0.45f);
}

void Subordinate::update(f32 t) {
	_theta += _omega * Angle2d::PI * 2.0f * t;
	_position += _velocity * t;

	_tail.update(t, Quaternion(_width * _theta.sin(), float3d(0, 1, 0)) * _rotation);
}
