#pragma once

#include "rscResource.h"

#include "oglShader.h"

namespace rsc {
	class Shader : public Resource {
		ogl::Shader _shader;
	private:
		void _load(core::shared_ptr<fs::IFileReader>);
	public:
		typedef ogl::Shader::EType EType;
		Shader(EType);
		~Shader();

		void compile();
		ogl::Shader& getOglShader();
	};
}