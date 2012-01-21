#include "Matrix4d.h"

#include <GL/glfw.h>

Matrix4d Matrix4d::getModelView() {
	Matrix4d mat;
	glGetFloatv(GL_MODELVIEW_MATRIX, mat._m.data());
	return mat;
}

Matrix4d Matrix4d::getProjection() {
	Matrix4d mat;
	glGetFloatv(GL_PROJECTION_MATRIX, mat._m.data());
	return mat;
}

void Matrix4d::load() {
	glLoadMatrixf(_m.data());
}

Matrix4d::Matrix4d() {
	for (u32 i = 0; i < 4; ++i) {
		for (u32 j = 0; j < 4; ++j) {
			_m[i * 4 + j] = (i == j)? 1.0f : 0.0f;
		}
	}
}

Matrix4d& Matrix4d::operator*=(const Matrix4d& m) {
	core::array<f32, 16> dst;
	for (u32 i=0; i<16; i++) {
		float sum = 0.0f;
		for(u32 j=0; j<4; j++) {
			sum += _m[i%4*4 + j] * m._m[j*4 + (i>>2)];
		}
		dst[i] = sum;
	}
	_m = dst;
	return *this;
}

Matrix4d& Matrix4d::operator+=(const Matrix4d& m) {
	for (u32 i = 0; i < 16; ++i) {
		_m[i] += m._m[i];
	}
	return *this;
}

Matrix4d& Matrix4d::operator-=(const Matrix4d& m) {
	for (u32 i = 0; i < 16; ++i) {
		_m[i] -= m._m[i];
	}
	return *this;
}

float3d Matrix4d::operator*(const float3d& v) const {
	float3d out;
	float w;
	out.x = _m[0] * v.x + _m[4] * v.y + _m[8] * v.z + _m[12] * 1.0f;
	out.y = _m[1] * v.x + _m[5] * v.y + _m[9] * v.z + _m[13] * 1.0f;
	out.z = _m[2] * v.x + _m[6] * v.y + _m[10] * v.z + _m[14] * 1.0f;
	w = _m[3] * v.x + _m[7] * v.y + _m[11] * v.z + _m[15] * 1.0f;
	return out;
}


float& Matrix4d::operator()(u32 i, u32 j) {
	return _m[j * 4 + i];
}

const float& Matrix4d::operator()(u32 i, u32 j) const {
	return _m[j * 4 + i];
}

float& Matrix4d::at(u32 i, u32 j) {
	return _m[j * 4 + i];
}

const float& Matrix4d::at(u32 i, u32 j) const {
	return _m[j * 4 + i];
}

Matrix4d Matrix4d::operator-() const {
	Matrix4d out;
	for (u32 i = 0; i < 16; ++i) {
		out._m[i] = - _m[i];
	}
	return out;
}

void Matrix4d::normalize() {
	f32 det = getDeterminant();
	for (u32 i = 0; i < 16; ++i) {
		_m[i] /= det;
	}
}

Matrix4d Matrix4d::getNormalized() const {
	Matrix4d mat = *this;
	mat.normalize();
	return mat;
}

void Matrix4d::invert() {
	Matrix4d& in = *this;
	Matrix4d out;
	float buf;
	u32 i, j, k;
	const u32 n=4;

	for(i=0;i<n;i++){
		buf=1.0f/in(i, i);
		for(j=0;j<n;j++){
			in(i, j)*=buf;
			out(i, j)*=buf;
		}
		for(j=0;j<n;j++){
			if(i!=j){
				buf=in(j, i);
				for(k=0;k<n;k++){
				in(j, k)-=in(i, k)*buf;
				out(j, k)-=out(i, k)*buf;
				}
			}
		}
	}

	_m = out._m;
}

Matrix4d Matrix4d::getInverse() const {
	Matrix4d mat = *this;
	mat.invert();
	return mat;
}

float Matrix4d::getDeterminant() const {
	Matrix4d mat = *this;

	f32 det = 1.0f, buf;
	u32 i, j, k;
	const u32 n = 4;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i<j){
				buf=mat(j, i) / mat(i, i);
				for(k=0;k<n;k++){
					mat(j, k) -= mat(i, k)*buf;
				}
			}
		}
	}
	//‘ÎŠp•”•ª‚ÌÏ
	for(i=0;i<n;i++){
		det*=mat(i, i);
	}
	return det;
}