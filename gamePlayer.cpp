#include "gamePlayer.h"

#include "rscIManager.h"
#include "rscMesh.h"
#include "oglShader.h"

#include "Angle2d.h"
#include "inputManager.h"
#include "inputMouse.h"

#include "rscShader.h"

using namespace game;

const float Player::RADIUS = 1.3f;

Player::Player(core::shared_ptr<rsc::IManager> rm)
	: Spermatozoa(rm), _speedUpCounter(0.0f)
{
	// �F��ݒ�
	_material.setDiffuseColor(Color(0xC2F5FFFF));
}

void Player::update(float t) {
	// �J�[�\�������ɉ�]������
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

	// ���x�����߂�
	float speed = 20.0f;
	if (_speedUpCounter > 0.75f) {
		speed = 40.0f;
		_speedUpCounter -= t;
	} else if (_speedUpCounter > 0.0f) {
		speed = 20.0f + 20.0f * _speedUpCounter / 0.75f;
		_speedUpCounter -= t;
	}

	// �ʒu���X�V
	float3d velocity = speed * _rotation.getRotated(float3d(0.0f, 0.0f, -1.0f));
	_position += velocity * t;

	// �K����h�炷
	_theta += Angle2d::PI * speed / 10.0f * t;
	_tail.update(t, _rotation * Quaternion(0.4f * _theta.sin(), float3d(0, 1, 0)));

	// �N���b�N�ŉ���
	if (_speedUpCounter <= 0.4f) {
		if (input::Manager::instance()->getMouse()->isPressed(input::Mouse::EB_LEFT)) {
			_speedUpCounter = 1.5f;
		}
	}
}

void Player::_onDraw() {
	// �}�E�X��3D�ʒu���v�Z
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