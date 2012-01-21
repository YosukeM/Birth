#pragma once

#include <boost/operators.hpp>

class Matrix4d : private
	boost::additive<Matrix4d>,
	boost::multipliable<Matrix4d>
{
	core::array<float, 16> _m;
public:
	Matrix4d();

	static Matrix4d getModelView();
	static Matrix4d getProjection();

	void load();

	Matrix4d& operator*=(const Matrix4d&);
	Matrix4d& operator+=(const Matrix4d&);
	Matrix4d& operator-=(const Matrix4d&);

	float3d operator*(const float3d&) const;

	float& operator()(u32 i, u32 j);
	const float& operator()(u32 i, u32 j) const;

	float& at(u32 i, u32 j);
	const float& at(u32 i, u32 j) const;

	Matrix4d operator-() const;

	float getDeterminant() const;

	void normalize();
	Matrix4d getNormalized() const;

	void invert();
	Matrix4d getInverse() const;
};