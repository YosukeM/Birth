#include "gamePlayer.h"

#include "rscIManager.h"
#include "rscMesh.h"
#include "rscShader.h"
#include "oglShader.h"

#include "Angle2d.h"
#include "inputManager.h"
#include "inputMouse.h"

#include "gameOvum.h"
#include "gameGeomParticle.h"
#include "gameStatus.h"

using namespace game;

const float Player::RADIUS = 1.3f;

Player::Player(core::shared_ptr<rsc::IManager> rm, core::shared_ptr<Status> status)
	: Spermatozoa(rm), _speedUpCounter(0.0f), _hasOvumAttached(false), _rm(rm), _status(status)
{
	// 色を設定
	_material.setDiffuseColor(Color(0xC2F5FFFF));
}

void Player::_updateAttached(f32 t) {
	_theta += Angle2d::PI * 2.0f * t;
	_tail.update(t, _rotation * Quaternion(0.4f * _theta.sin(), float3d(0, 1, 0)));

	if (input::Manager::instance()->getMouse()->isPressed(input::Mouse::EB_LEFT)) {
		_emitter->emit(10, float3d(0.0f, 0.0f, 3.0f), float3d(2.5f, 2.5f, 1.0f), 1.0f);
		_status->increaseOvumClickedNum();
	}

	_emitter->update(t);
}

void Player::update(float t) {
	if (_hasOvumAttached) {
		_updateAttached(t);
		return;
	}

	// カーソル方向に回転させる
	if (_pointer.getLengthSQ() > 0.001f) {
		float2d n = _pointer.getNormalized();
		float3d axis(n.y, - n.x, 0.0f);
		f32 level = _pointer.getLength();
		if (level < 0.0f) level = 0.0f;
		if (level > 1.0f) level = 1.0f;
		Quaternion target(Angle2d::PI * 0.1f * level, axis);
		_rotation = Quaternion::slerp(_rotation, target, 10.0f * t);
	} else {
		_rotation = Quaternion::slerp(_rotation, Quaternion(), 10.0f * t);
	}
	_rotation.normalize();

	// 速度を決める
	float speed = 20.0f;
	if (_speedUpCounter > 0.75f) {
		speed = 40.0f;
		_speedUpCounter -= t;
	} else if (_speedUpCounter > 0.0f) {
		speed = 20.0f + 20.0f * _speedUpCounter / 0.75f;
		_speedUpCounter -= t;
	}

	// 位置を更新
	if (_ovum) {
		float3d direction = (_ovum->getPosition() - _position);
		_rotation = Quaternion::slerp(_rotation, Quaternion::fromDirection(direction, float3d(0.0f, 0.0f, -1.0f)), 30.0f * t);
	}
	float3d velocity = speed * _rotation.getRotated(float3d(0.0f, 0.0f, -1.0f));
	_position += velocity * t;
	
	// 接触判定
	if (!_hasOvumAttached) {
		if (_ovum) {
			if ((_ovum->getPosition() - _position).getLengthSQ() < std::pow(Player::RADIUS + Ovum::RADIUS, 2)) {
				_hasOvumAttached = true;
			}
		}
	}

	// 尻尾を揺らす
	_theta += Angle2d::PI * speed / 10.0f * t;
	_tail.update(t, _rotation * Quaternion(0.4f * _theta.sin(), float3d(0, 1, 0)));

	// クリックで加速
	if (_speedUpCounter <= 0.4f) {
		if (input::Manager::instance()->getMouse()->isPressed(input::Mouse::EB_LEFT)) {
			if (_status->decreaseEnergyNum()) {
				_speedUpCounter = 1.5f;
			}
		}
	}
}

void Player::_onDraw() {
	// マウスの3D位置を計算
	const core::tuple<float3d, float3d> ray = input::Manager::instance()->getMouse()->getRay();

	_material.setDiffuseColor(_speedUpCounter > 0.1f? Color(0xC2F5FFBB) : Color(0xC2F5FFFF));

	float3d p;
	if (abs(core::get<0>(ray).z - core::get<1>(ray).z) > 0.0001f) {
		float t = - core::get<1>(ray).z / (core::get<0>(ray).z - core::get<1>(ray).z);
		p = core::get<0>(ray) * t + core::get<1>(ray) * (1.0f - t);
	} else {
		p.x = core::get<0>(ray).x;
		p.y = core::get<0>(ray).y;
	}
	_pointer = float2d(p.x, p.y);
}

void Player::setOvum(core::shared_ptr<Ovum> ovum) {
	if (!_ovum) {
		_emitter.reset(new geom::Emitter(_rm->getTexture("particle.tga"), 300));
	}
	_ovum = ovum;
}

void Player::_drawEffect() {
	if (_emitter) {
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -1.3f);
			_emitter->draw(Color(0xc1fef1FF));
		glPopMatrix();
	}
}

bool Player::isOvumAttached() const {
	return _hasOvumAttached;
}