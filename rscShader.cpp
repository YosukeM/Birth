#include "rscShader.h"

#include "IFileReader.h"

using namespace rsc;

Shader::Shader(EType type)
	: _shader(type)
{
}

Shader::~Shader() {
}

void Shader::_load(core::shared_ptr<fs::IFileReader> fr) {
	std::string str;
	fr->getAllAsString(str);
	_shader.source(str);
}

void Shader::compile() {
	_shader.compile();
}

ogl::Shader& Shader::getOglShader() {
	return _shader;
}