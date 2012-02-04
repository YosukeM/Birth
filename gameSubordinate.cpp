#include "gameSubordinate.h"

#include "gameOvum.h"
#include "Random.h"

#include "gameGeomParticle.h"
#include "rscIManager.h"

using namespace game;

Subordinate::Subordinate(core::shared_ptr<rsc::IManager> rm, Scene* scene)
	: Spermatozoa(rm), _scene(scene), _hasOvumAttached(false)
{
	// ‘¬“x‚ðƒ‰ƒ“ƒ_ƒ€‚ÉŒˆ‚ß‚é
	_speed = core::random::getFloat(14.0f, 21.0f);
	_velocity = float3d(0.0f, 0.0f, - _speed);

	// K”ö‚ÌU‚ê•û‚ðƒ‰ƒ“ƒ_ƒ€‚ÉŒˆ‚ß‚é
	_theta = core::random::getFloat(0.0f, 2.0f * Angle2d::PI);
	_omega = core::random::getFloat(0.8f, 1.2f);
	_width = core::random::getFloat(0.35f, 0.45f);

	_particleTex = rm->getTexture("particle.tga");
}

void Subordinate::update(f32 t) {
	_theta += _omega * Angle2d::PI * 2.0f * t;
	if (!_hasOvumAttached) {
		_position += _velocity * t;
	}

	if (_ovum && !_hasOvumAttached) {
		// —‘Žq‚Ì•ûŒü‚É‰ñ“]
		float3d direction = (_ovum->getPosition() - _position);
		_rotation = Quaternion::slerp(_rotation, Quaternion::fromDirection(direction, float3d(0.0f, 0.0f, -1.0f)), 3.0f * t);
		_velocity = _speed * _rotation.getRotated(float3d(0.0f, 0.0f, -1.0f));

		// ÚG”»’è
		if ((_ovum->getPosition() - _position).getLengthSQ() < std::pow(1.3f + Ovum::RADIUS, 2)) {
			_hasOvumAttached = true;
		}
	}

	if (_hasOvumAttached) {
		_emitter->emit(5, float3d(0.0f, 0.0f, 0.5f), float3d(1.5f, 1.5f, 1.0f), 1.0f);
		_emitter->update(t);
	}

	_tail.update(t, Quaternion(_width * _theta.sin(), float3d(0, 1, 0)) * _rotation);
}

void Subordinate::_drawEffect() {
	if (_emitter) {
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -1.3f);
			_emitter->draw(Color(0xFFFFFFFF));
		glPopMatrix();
	}
}

void Subordinate::setOvum(core::shared_ptr<Ovum> ovum) {
	if (!_ovum) {
		_emitter.reset(new geom::Emitter(_particleTex, 300));
	}
	_ovum = ovum;
}