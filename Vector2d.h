#pragma once

#include <cmath>

template <class T> class Vector2d {
public:
	T x, y;

	Vector2d() : x(0), y(0) {}
	Vector2d(T nx, T ny) : x(nx), y(ny) {}
	explicit Vector2d(T n) : x(n), y(n) {}
	Vector2d(const Vector2d<T>& other) : x(other.x), y(other.y) {}

	// operators

	Vector2d<T> operator-() const { return Vector2d<T>(-x, -y); }

	Vector2d<T>& operator=(const Vector2d<T>& other) { x = other.x; y = other.y; return *this; }

	Vector2d<T> operator+(const Vector2d<T>& other) const { return Vector2d<T>(x + other.x, y + other.y); }
	Vector2d<T>& operator+=(const Vector2d<T>& other) { x+=other.x; y+=other.y; return *this; }
	Vector2d<T>& operator+=(const T v) { x+=v; y+=v; return *this; }

	Vector2d<T> operator-(const Vector2d<T>& other) const { return Vector2d<T>(x - other.x, y - other.y); }
	Vector2d<T>& operator-=(const Vector2d<T>& other) { x-=other.x; y-=other.y; return *this; }

	Vector2d<T> operator*(const Vector2d<T>& other) const { return Vector2d<T>(x * other.x, y * other.y); }
	Vector2d<T>& operator*=(const Vector2d<T>& other) { x*=other.x; y*=other.y; return *this; }
	Vector2d<T> operator*(const T v) const { return Vector2d<T>(x * v, y * v); }
	Vector2d<T>& operator*=(const T v) { x*=v; y*=v; return *this; }

	Vector2d<T> operator/(const Vector2d<T>& other) const { return Vector2d<T>(x / other.x, y / other.y); }
	Vector2d<T>& operator/=(const Vector2d<T>& other) { x/=other.x; y/=other.y; return *this; }
	Vector2d<T> operator/(const T v) const { return Vector2d<T>(x / v, y / v); }
	Vector2d<T>& operator/=(const T v) { x/=v; y/=v; return *this; }

	bool operator==(const Vector2d<T>& other) const { return equals(other); }
	bool operator!=(const Vector2d<T>& other) const { return !equals(other); }

	// functions
	bool equals(const Vector2d<T>& other) const
	{
		return abs(x - other.x) < 0.001f && abs(y - other.y) < 0.001f;
	}

	Vector2d<T>& set(T nx, T ny) {x=nx; y=ny; return *this; }
	Vector2d<T>& set(const Vector2d<T>& p) { x=p.x; y=p.y; return *this; }

	T getLength() const { return std::sqrt( x*x + y*y ); }

	T getLengthSQ() const { return x*x + y*y; }

	T dotProduct(const Vector2d<T>& other) const
	{
		return x*other.x + y*other.y;
	}

	T getDistanceFrom(const Vector2d<T>& other) const
	{
		return Vector2d<T>(x - other.x, y - other.y).getLength();
	}

	T getDistanceFromSQ(const Vector2d<T>& other) const
	{
		return Vector2d<T>(x - other.x, y - other.y).getLengthSQ();
	}

	Vector2d<T>& normalize()
	{
		float length = (float)(x*x + y*y);
		if (std::abs(length - 0.f) < 0.001f) return *this;
		length = std::sqrt(length);
		x = (T)(x * length);
		y = (T)(y * length);
		return *this;
	}

	Vector2d<T> getNormalized() const {
		Vector2d<T> n = this;
		n.normalize();
		return n;
	}
};

//! Typedef for f32 2d vector.
typedef Vector2d<float> float2d;
typedef Vector2d<f64> double2d;

//! Typedef for integer 2d vector.
typedef Vector2d<int> int2d;
typedef Vector2d<u32> uint2d;