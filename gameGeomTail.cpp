#include "gameGeomTail.h"

#include <GL/glfw.h>

using namespace game;
using namespace geom;

void Joint::update(float t, const Joint& prev_joint, float interval) {
	rotation = Quaternion::slerp(rotation, prev_joint.rotation, t * 30.0f);
	rotation.normalize();
	float3d target = prev_joint.position + rotation.getRotated(float3d(0, 0, - interval));
	position += (target - position) * 50.0f * t;
}

Tail::Tail(float radius, float length, u32 spirit_r, u32 spirit_h)
	: _drawed(false), _radius(radius), _length(length), _radiusSpirit(spirit_r), _heightSpirit(spirit_h)
{
	// create joints
	_joints.resize(spirit_h + 1);
	{
		u32 i = 0;
		foreach (Joint& joint, _joints) {
			joint.position.z = f32(i) / f32(spirit_h) * length;
			++i;
		}
	}

	// cache sin and cos
	for (u32 i = 0; i < spirit_r; ++i) {
		f32 theta = float(i) / float(spirit_r) * Angle2d::PI * 2.0f;
		_cos.push_back(std::cos(theta));
		_sin.push_back(std::sin(theta));
	}

	// push verts
	for (u32 j = 0; j < spirit_h; ++j) {
		f32 level = f32(j) / f32(spirit_h);
		f32 z = level * length;
		f32 r = _levelToRadius(level);
		for (u32 i = 0; i < spirit_r; ++i) {
			_verts.push_back(float3d(r * _cos[i], r * _sin[i], z));
		}
	}
	_verts.push_back(float3d(0.0f, 0.0f, length));

	// push indices
	for (u32 i = 0; i < spirit_h - 1; ++i) {
		for (u32 j = 0; j < spirit_r; ++j) {
			_indices.push_back(i * spirit_r + j);
			_indices.push_back(i * spirit_r + (j + 1) % spirit_r);
			_indices.push_back((i + 1) * spirit_r + j);

			_indices.push_back((i + 1) * spirit_r + j);
			_indices.push_back(i * spirit_r + (j + 1) % spirit_r);
			_indices.push_back((i + 1) * spirit_r + (j + 1) % spirit_r);
		}
	}

	u32 last_index = _verts.size() - 1;
	u32 offset = last_index - spirit_r;
	for (u32 i = 0; i < spirit_r; ++i) {
		_indices.push_back(offset + i);
		_indices.push_back(offset + (i + 1) % spirit_r);
		_indices.push_back(last_index);
	}

	// create norms
	_norms.resize(_verts.size());
	_updateNormals();
}

float Tail::_levelToRadius(float level) const {
	return _radius * (level < 0.5f? 1.0f : 1.5f - level);
}

void Tail::_updateNormals() {
	for (u32 i = 0; i < _indices.size(); i += 3) {
		u32 i0 = _indices[i];
		u32 i1 = _indices[i+1];
		u32 i2 = _indices[i+2];

		float3d n = (_verts[i1] - _verts[i0]).crossProduct(_verts[i2] - _verts[i0]);
		_norms[i0] += n;
		_norms[i1] += n;
		_norms[i2] += n;
	}

	foreach (float3d& norm, _norms) {
		norm.normalize();
	}
}

void Tail::update(f32 t, const Quaternion& rotation) {
	_drawed = false;

	// update joints
	_joints[0].rotation = rotation;
	for (u32 i = 1; i < _joints.size(); ++i) {
		_joints[i].update(t, _joints[i - 1], _length / _heightSpirit);
	}

	// update verts
	f32 part_len = _length / f32(_heightSpirit);
	for (u32 j = 0; j < _heightSpirit; ++j) {
		f32 level = f32(j) / f32(_heightSpirit);
		f32 r = _levelToRadius(level);
		for (u32 i = 0; i < _radiusSpirit; ++i) {
			_verts[i + _radiusSpirit * j] = _joints[j].position + float3d(r * _cos[i], r * _sin[i], 0.0f);
		}
	}
	_verts[_verts.size() - 1] = _joints[_joints.size() - 1].position;
}

void Tail::draw() {
	if (!_drawed) {
		//_updateNormals();
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _verts.data());
	glNormalPointer(GL_FLOAT, 0, _norms.data());
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, _indices.data());
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	_drawed = true;
}
