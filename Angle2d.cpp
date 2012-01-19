#include "Angle2d.h"

#include <cmath>

const float Angle2d::PI(3.1415926535897932f);

void Angle2d::_normalize() {
	while (_v <= -PI) {
		_v += PI * 2.0f;
	}
	while (_v > PI) {
		_v -= PI * 2.0f;
	}
}

Angle2d::Angle2d(float v)
	: _v(v)
{
}

Angle2d::Angle2d(const float2d& v) {
	
}

bool Angle2d::operator<(const Angle2d& x) const {
	return _v < x._v;
}

bool Angle2d::operator==(const Angle2d& x) const {
	return _v == x._v;
}

Angle2d& Angle2d::operator+=(const Angle2d& x) {
	_v += x._v;
	_normalize();
	return *this;
}

Angle2d& Angle2d::operator-=(const Angle2d& x) {
	_v -= x._v;
	_normalize();
	return *this;
}

Angle2d& Angle2d::operator*=(const float& x) {
	_v *= x;
	_normalize();
	return *this;
}

Angle2d& Angle2d::operator/=(const float& x) {
	_v /= x;
	_normalize();
	return *this;
}

Angle2d Angle2d::operator-() const {
	return Angle2d(-_v);
}

float Angle2d::cos() const {
	return std::cos(_v);
}

float Angle2d::sin() const {
	return std::sin(_v);
}

float Angle2d::tan() const {
	return std::tan(_v);
}

float2d Angle2d::getVector() const {
	return float2d(cos(), sin());
}

float Angle2d::degree() const {
	return _v * 180.0f / PI; 
}

Angle2d::operator float() const {
	return _v;
}
