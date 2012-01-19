#pragma once

#include "Vector2d.h"
#include "Vector3d.h"

namespace ogl {
class Shader;
class Program
{
	unsigned _id;
public:
	Program();
	~Program();

	void attach(const Shader&);
	void detach(const Shader&);
	void link();
	void use();
	void unuse();

	void setUniform(const char* variable, float);
	void setUniform(const char* variable, const float2d&);
	void setUniform(const char* variable, const float3d&);

	void setUniform(const char* variable, int);
	void setUniform(const char* variable, const int2d&);
	void setUniform(const char* variable, const int3d&);};
}
