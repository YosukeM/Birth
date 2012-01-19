#pragma once

typedef int s32;
typedef unsigned u32;
typedef short s16;
typedef unsigned short u16;
typedef signed char s8;
typedef unsigned char u8;

#if defined(_MSC_VER) || defined(__BORLANDC__)
	typedef __int64 s64;
	typedef unsigned __int64 u64;
#else
	typedef long long s64;
	typedef unsigned long long u64;
#endif

typedef float f32;
typedef double f64;

#include "Vector2d.h"
#include "Vector3d.h"

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#include "core.h"
