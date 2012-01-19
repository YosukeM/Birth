#pragma once

#include "Error.h"

namespace ogl {
class CompileError : public Error {
public:
	CompileError(const core::string& msg)
		: Error(msg)
	{};
};
}
