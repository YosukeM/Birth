#include "Color.h"

Color::Color()
	: r(0), g(0), b(0), a(255)
{
}

Color::Color(unsigned v)
	: r(v >> 24), g((v >> 16) & 255), b((v >> 8) & 255), a(v & 255)
{
}

Color::Color(s32 red, s32 green, s32 blue, s32 alpha) {

#define SET(var, val)\
	if (val < 0) var = 0;\
	else if (val > 255) var = 255;\
	else var = val;

	SET(r, red)
	SET(g, green)
	SET(b, blue)
	SET(a, alpha)
}

void Color::getAs4Values(float* v) const {
	v[0] = r / 255.0f;
	v[1] = g / 255.0f;
	v[2] = b / 255.0f;
	v[3] = a / 255.0f;
}
