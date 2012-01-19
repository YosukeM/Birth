#pragma once

class Color
{
public:
	u8 r, g, b, a;
	Color();
	Color(unsigned);
	Color(s32 r, s32 g, s32 b, s32 a = 255);

	void getAs4Values(float*) const;
};
