#pragma once

#include "rscResource.h"

#include "oglProgram.h"

namespace rsc {
	class Shader;

	class Program : public Resource {
		ogl::Program _program;
		void _load(core::shared_ptr<fs::IFileReader>) {};

	public:
		void load(core::shared_ptr<rsc::Shader>, core::shared_ptr<rsc::Shader>);

		void use();
		void unuse();

		void setUniform(const char* variable, float);
		void setUniform(const char* variable, const float2d&);
		void setUniform(const char* variable, const float3d&);

		void setUniform(const char* variable, int);
		void setUniform(const char* variable, const int2d&);
		void setUniform(const char* variable, const int3d&);
	};
}