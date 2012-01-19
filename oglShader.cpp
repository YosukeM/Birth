#include "oglShader.h"

#include <GL/glew.h>
#include <GL/glfw.h>

using namespace ogl;

Shader::Shader(EType type)
	: _id(0)
{
	unsigned t;
	switch (type) {
	case ET_VERTEX:
		t = GL_VERTEX_SHADER; break;
	case ET_FRAGMENT:
		t = GL_FRAGMENT_SHADER; break;
	}

	_id = glCreateShader(t);
}

Shader::~Shader() {
	glDeleteShader(_id);
}

unsigned Shader::getId() const {
	return _id;
}

void Shader::source(const core::string& program) {
	const char* data = program.c_str();
	int length = program.size();
	glShaderSource(_id, 1, &data, &length);
}

void Shader::compile() {
	int compiled;
	glCompileShader(_id);
	glGetShaderiv(_id, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE) {
		int buf_size, length;
		glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &buf_size);
		char* buffer = new char[buf_size];
		glGetShaderInfoLog(_id, buf_size, &length, buffer);
		core::string message(buffer);
		delete[] buffer;
		throw CompileError(message);
	}
}
