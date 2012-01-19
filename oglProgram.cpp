#include "oglProgram.h"
#include <GL/glew.h>

#include "oglLinkError.h"
#include "oglShader.h"
#include <GL/glfw.h>

using namespace ogl;

Program::Program()
	: _id(0)
{
	_id = glCreateProgram();
}

Program::~Program() {
	glDeleteProgram(_id);
}

void Program::attach(const Shader& shader) {
	glAttachShader(_id, shader.getId());
}

void Program::detach(const Shader& shader) {
	glDetachShader(_id, shader.getId());
}

void Program::link() {
	int linked;
	glLinkProgram(_id);
	glGetProgramiv(_id, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE) {
		int buf_size, length;
		glGetProgramiv(_id, GL_INFO_LOG_LENGTH , &buf_size);
		char* buffer = new char[buf_size];
		glGetProgramInfoLog(_id, buf_size, &length, buffer);
		core::string message(buffer);
		delete[] buffer;
		throw LinkError(message);
	}
}

void Program::use() {
	glUseProgram(_id);
}

void Program::unuse() {
	glUseProgram(0);
}

void Program::setUniform(const char* variable, float v) {
	glUniform1f(glGetUniformLocation(_id, variable), v);
}

void Program::setUniform(const char* variable, const float2d& v) {
	glUniform2f(glGetUniformLocation(_id, variable), v.x, v.y);
}

void Program::setUniform(const char* variable, const float3d& v) {
	glUniform3f(glGetUniformLocation(_id, variable), v.x, v.y, v.z);
}


void Program::setUniform(const char* variable, int v) {
	glUniform1i(glGetUniformLocation(_id, variable), v);
}

void Program::setUniform(const char* variable, const int2d& v) {
	glUniform2i(glGetUniformLocation(_id, variable), v.x, v.y);
}

void Program::setUniform(const char* variable, const int3d& v) {
	glUniform3i(glGetUniformLocation(_id, variable), v.x, v.y, v.z);
}
