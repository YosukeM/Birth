#pragma once

#include <cmath>

template <class T> class Vector3d
{
public:
	T x, y, z;

	//! Default constructor (null vector).
	Vector3d() : x(0), y(0), z(0) {}
	//! Constructor with three different values
	Vector3d(T nx, T ny, T nz) : x(nx), y(ny), z(nz) {}
	//! Constructor with the same value for all elements
	explicit Vector3d(T n) : x(n), y(n), z(n) {}
	//! Copy constructor
	Vector3d(const Vector3d<T>& other) : x(other.x), y(other.y), z(other.z) {}

	// operators

	Vector3d<T> operator-() const { return Vector3d<T>(-x, -y, -z); }

	Vector3d<T>& operator=(const Vector3d<T>& other) { x = other.x; y = other.y; z = other.z; return *this; }

	Vector3d<T> operator+(const Vector3d<T>& other) const { return Vector3d<T>(x + other.x, y + other.y, z + other.z); }
	Vector3d<T>& operator+=(const Vector3d<T>& other) { x+=other.x; y+=other.y; z+=other.z; return *this; }
	Vector3d<T> operator+(const T val) const { return Vector3d<T>(x + val, y + val, z + val); }
	Vector3d<T>& operator+=(const T val) { x+=val; y+=val; z+=val; return *this; }

	Vector3d<T> operator-(const Vector3d<T>& other) const { return Vector3d<T>(x - other.x, y - other.y, z - other.z); }
	Vector3d<T>& operator-=(const Vector3d<T>& other) { x-=other.x; y-=other.y; z-=other.z; return *this; }
	Vector3d<T> operator-(const T val) const { return Vector3d<T>(x - val, y - val, z - val); }
	Vector3d<T>& operator-=(const T val) { x-=val; y-=val; z-=val; return *this; }

	Vector3d<T> operator*(const Vector3d<T>& other) const { return Vector3d<T>(x * other.x, y * other.y, z * other.z); }
	Vector3d<T>& operator*=(const Vector3d<T>& other) { x*=other.x; y*=other.y; z*=other.z; return *this; }
	Vector3d<T> operator*(const T v) const { return Vector3d<T>(x * v, y * v, z * v); }
	Vector3d<T>& operator*=(const T v) { x*=v; y*=v; z*=v; return *this; }

	Vector3d<T> operator/(const Vector3d<T>& other) const { return Vector3d<T>(x / other.x, y / other.y, z / other.z); }
	Vector3d<T>& operator/=(const Vector3d<T>& other) { x/=other.x; y/=other.y; z/=other.z; return *this; }
	Vector3d<T> operator/(const T v) const { T i=(T)1.0/v; return Vector3d<T>(x * i, y * i, z * i); }
	Vector3d<T>& operator/=(const T v) { T i=(T)1.0/v; x*=i; y*=i; z*=i; return *this; }


	//! use weak float compare
	bool operator==(const Vector3d<T>& other) const
	{
		return this->equals(other);
	}

	bool operator!=(const Vector3d<T>& other) const
	{
		return !this->equals(other);
	}

	// functions

	//! returns if this vector equals the other one, taking floating point rounding errors into account
	bool equals(const Vector3d<T>& other, const T tolerance = (T)0.001f ) const
	{
		return std::abs(x - other.x) < tolerance &&
			std::abs(y - other.y) < tolerance &&
			std::abs(z - other.z) < tolerance;
	}

	Vector3d<T>& set(const T nx, const T ny, const T nz) {x=nx; y=ny; z=nz; return *this;}
	Vector3d<T>& set(const Vector3d<T>& p) {x=p.x; y=p.y; z=p.z;return *this;}

	//! Get length of the vector.
	T getLength() const { return std::sqrt( x*x + y*y + z*z ); }

	//! Get squared length of the vector.
	/** This is useful because it is much faster than getLength().
	\return Squared length of the vector. */
	T getLengthSQ() const { return x*x + y*y + z*z; }

	//! Get the dot product with another vector.
	T dotProduct(const Vector3d<T>& other) const
	{
		return x*other.x + y*other.y + z*other.z;
	}

	//! Get distance from another point.
	/** Here, the vector is interpreted as point in 3 dimensional space. */
	T getDistanceFrom(const Vector3d<T>& other) const
	{
		return Vector3d<T>(x - other.x, y - other.y, z - other.z).getLength();
	}

	//! Returns squared distance from another point.
	/** Here, the vector is interpreted as point in 3 dimensional space. */
	T getDistanceFromSQ(const Vector3d<T>& other) const
	{
		return Vector3d<T>(x - other.x, y - other.y, z - other.z).getLengthSQ();
	}

	//! Calculates the cross product with another vector.
	/** \param p Vector to multiply with.
	\return Crossproduct of this vector with p. */
	Vector3d<T> crossProduct(const Vector3d<T>& p) const
	{
		return Vector3d<T>(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
	}


	//! Normalizes the vector.
	/** In case of the 0 vector the result is still 0, otherwise
	the length of the vector will be 1.
	\return Reference to this vector after normalization. */
	Vector3d<T>& normalize()
	{
		f64 length = x*x + y*y + z*z;
		if (std::abs(length) < 0.0) // this check isn't an optimization but prevents getting NAN in the sqrt.
			return *this;
		length = 1.0f / std::sqrt(length);

		x = (T)(x * length);
		y = (T)(y * length);
		z = (T)(z * length);
		return *this;
	}

	Vector3d<T> getNormalized() const
	{
		f32 length = x*x + y*y + z*z;
		if (std::abs(length) < 0.001f) // this check isn't an optimization but prevents getting NAN in the sqrt.
			return *this;
		length = 1.0f / sqrt(length);

		return Vector3d<T>(x, y, z) * length;
	}

	//! Sets the length of the vector to a new value
	Vector3d<T>& setLength(T newlength)
	{
		normalize();
		return (*this *= newlength);
	}

	//! Inverts the vector.
	Vector3d<T>& invert()
	{
		x *= -1;
		y *= -1;
		z *= -1;
		return *this;
	}
};

//! Typedef for a f32 3d vector.
typedef Vector3d<f32> float3d;

//! Typedef for an integer 3d vector.
typedef Vector3d<s32> int3d;

//! Function multiplying a scalar and a vector component-wise.
template<class S, class T>
Vector3d<T> operator*(const S scalar, const Vector3d<T>& vector) { return vector*scalar; }
