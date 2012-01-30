#include "Quaternion.h"

#include "Angle2d.h"

Quaternion::Quaternion()
	: w(1.0f), x(0.0f), y(0.0f), z(0.0f)
{
}

Quaternion::Quaternion(float w_, float x_, float y_, float z_)
	: w(w_), x(x_), y(y_), z(z_)
{

}

Quaternion::Quaternion(const float3d& euler) {
	float2d vx, vy, vz;
	vx = (Angle2d(euler.x) * 0.5f).getVector();
	vy = (Angle2d(euler.y) * 0.5f).getVector();
	vz = (Angle2d(euler.z) * 0.5f).getVector();

	w = vx.x * vy.x * vz.x + vx.y * vy.y * vy.y;
	x = vx.y * vy.x * vz.x + vx.x * vy.y * vy.y;
	y = vx.x * vy.y * vz.x + vx.y * vy.x * vy.y;
	z = vx.x * vy.x * vz.y + vx.y * vy.y * vy.x;
}

Quaternion::Quaternion(const Angle2d& angle, const float3d& axis) {
	float3d vn = axis.getNormalized();
	Angle2d rad = angle * 0.5f;
	f32 sin = rad.sin();
	w = rad.cos();
	x = vn.x * sin;
	y = vn.y * sin;
	z = vn.z * sin;
}

f32 Quaternion::dotProduct(const Quaternion&q) const {
	return w*q.w + x*q.x + y*q.y + z*q.z;
}

Quaternion Quaternion::operator*(const Quaternion& q) const {
	Quaternion out;

	out.w = q.w * w - q.x * x - q.y * y - q.z * z;
	out.x = q.w * x - q.x * w - q.z * y - q.y * z;
	out.y = q.w * y - q.y * w - q.x * z - q.z * x;
	out.z = q.w * z - q.z * w - q.y * x - q.x * y;

	return out;
}

Quaternion& Quaternion::operator*=(const Quaternion& q) {
	*this = *this * q;
	return *this;
}

Quaternion Quaternion::power(float exponent) {
	if (w > 0.9999f) {
		return *this;
	}

	float alpha = std::acos(w);
	float new_alpha = alpha * exponent;

	Quaternion result;
	result.w = std::cos(new_alpha);

	float mult = std::sin(new_alpha) / std::sin(alpha);
	result.x = x * mult;
	result.y = y * mult;
	result.z = z * mult;

	return result;
}

core::tuple<Angle2d, float3d> Quaternion::getAngleAxis() const {
	Angle2d angle = Angle2d::acos(w);
	angle *= 2.0f;

	float3d axis;
	f32 sin_half_sq = 1.0f - std::pow(w, 2);
	if (sin_half_sq <= 0.0f) {
		axis = float3d(1.0f, 0.0f, 0.0f);
	} else {
		f32 one_per_sin_half = 1.0f / std::sqrt(sin_half_sq);
		axis = float3d(x * one_per_sin_half, y * one_per_sin_half, z * one_per_sin_half);
	}
	return core::tuple<Angle2d, float3d>(angle, axis);
}

void Quaternion::normalize() {
	f32 mag = std::sqrt(pow(w, 2) + pow(x, 2) + pow(y, 2) + pow(z, 2));
	if (mag > 0.0f) {
		float mag_inv = 1.0f / mag;
		w *= mag_inv;
		x *= mag_inv;
		y *= mag_inv;
		z *= mag_inv;
	} else {
		assert(false);
	}
}


Quaternion Quaternion::getConjugate() const {
	return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::slerp(const Quaternion& a, const Quaternion& b_, f32 t) {
	if (t < 0.0f) t = 0.0f;
	else if (t > 1.0f) t = 1.0f;

	float cos_omega = a.dotProduct(b_);

	Quaternion b = b_;
	if (cos_omega < 0.0f) {
		b.w = - b.w;
		b.x = - b.x;
		b.y = - b.y;
		b.z = - b.z;
		cos_omega = - cos_omega;
	}

	// assert(cos_omega < 1.1f);

	float k0, k1;
	if (cos_omega > 0.999f) {
		k0 = 1.0f - t;
		k1 = t;
	} else {
		float sin_omega = std::sqrt(1.0f - pow(cos_omega, 2));
		float omega = std::atan2(sin_omega, cos_omega);

		float cos_per_sin = 1.0f / sin_omega;

		k0 = sin((1.0f - t) * omega) * cos_per_sin;
		k1 = sin(t * omega) * cos_per_sin;
	}

	b.w = k0 * a.w + k1 * b.w;
	b.x = k0 * a.x + k1 * b.x;
	b.y = k0 * a.y + k1 * b.y;
	b.z = k0 * a.z + k1 * b.z;

	return b;
}

float3d Quaternion::getRotated(const float3d& v) {
	Quaternion out = (*this) * Quaternion(0.0f, v.x, v.y, v.z);
	return float3d(out.x, out.y, out.z);
}