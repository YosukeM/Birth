#include "rscProgram.h"

#include "rscShader.h"

using namespace rsc;

void Program::load(core::shared_ptr<rsc::Shader> vert, core::shared_ptr<rsc::Shader> frag) {
	_program.attach(vert->getOglShader());
	_program.attach(frag->getOglShader());
	_program.link();
}

void Program::use() {
	_program.use();
}

void Program::unuse() {
	_program.unuse();
}

void Program::setUniform(const char* variable, float v) {
	_program.setUniform(variable, v);
}

void Program::setUniform(const char* variable, const float2d& v) {
	_program.setUniform(variable, v);
}

void Program::setUniform(const char* variable, const float3d& v) {
	_program.setUniform(variable, v);
}

void Program::setUniform(const char* variable, int v) {
	_program.setUniform(variable, v);
}

void Program::setUniform(const char* variable, const int2d& v) {
	_program.setUniform(variable, v);
}

void Program::setUniform(const char* variable, const int3d& v) {
	_program.setUniform(variable, v);
}