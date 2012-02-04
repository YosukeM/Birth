#pragma once

#include "Angle2d.h"

class Quaternion{
public:
	f32 w, x, y, z;

	Quaternion();
	Quaternion(float w, float x, float y, float z);
	explicit Quaternion(const float3d& euler);
	Quaternion(const Angle2d& rad, const float3d& axis);

	f32 dotProduct(const Quaternion&) const;

	Quaternion operator*(const Quaternion&) const;
	Quaternion& operator*=(const Quaternion&);

	Quaternion power(float exponent);

	Quaternion getConjugate() const;

	core::tuple<Angle2d, float3d> getAngleAxis() const;

	void normalize();

	static Quaternion slerp(const Quaternion& a, const Quaternion& b, f32 blend);

	static Quaternion fromDirection(const float3d& n, const float3d& axis);

	float3d getRotated(const float3d&);
};