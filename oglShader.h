#pragma once

#include "oglCompileError.h"

namespace ogl {

class Shader
{
public:
	typedef enum {
		ET_VERTEX,
		ET_FRAGMENT,
		ET_GEOMETRY
	} EType;
private:
	EType _type;
	unsigned _id;
	Shader(const Shader&);
	Shader& operator=(const Shader&);
public:
	Shader(EType type);
	~Shader();

	unsigned getId() const;

	void source(const core::string& program);

	void compile();
};
}
