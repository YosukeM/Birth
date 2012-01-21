#include "Angle2d.h"

#include <cmath>

const float Angle2d::PI(3.1415926535897932f);

Angle2d Angle2d::acos(float v) {
	return Angle2d(std::acos(v));
}

Angle2d Angle2d::asin(float v) {
	return Angle2d(std::asin(v));
}

Angle2d Angle2d::atan(float v) {
	return Angle2d(std::atan(v));
}

Angle2d Angle2d::atan2(float y, float x) {
	return Angle2d(std::atan2(y, x));
}

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
	f32 cosine = cos();
	if (_v >= 0.0f) {
		return float2d(cosine, std::sqrt(1.0f - pow(cosine, 2)));
	} else {
		return float2d(cosine, - std::sqrt(1.0f - pow(cosine, 2)));
	}
}

float Angle2d::degree() const {
	return _v * 180.0f / PI; 
}

Angle2d::operator float() const {
	return _v;
}
