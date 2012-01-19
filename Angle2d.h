#pragma once

#include <boost/operators.hpp>

class Angle2d : private
	boost::totally_ordered<Angle2d>,
	boost::additive<Angle2d>,
	boost::multiplicative<Angle2d, float>
{
	float _v;
	void _normalize();

public:
	static const float PI;

	Angle2d(float v = 0.0f);
	Angle2d(const float2d& v);

	bool operator<(const Angle2d& x) const;
	bool operator==(const Angle2d& x) const;
	Angle2d& operator+=(const Angle2d& x);
	Angle2d& operator-=(const Angle2d& x);
	Angle2d& operator*=(const float& x);
	Angle2d& operator/=(const float& x);

	Angle2d operator-() const;

	float cos() const;
	float sin() const;
	float tan() const;

	float2d getVector() const;
	float degree() const;

	operator float() const;
};