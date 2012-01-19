#pragma once

#include "Error.h"

namespace ogl {
class LinkError : public Error {
public:
	LinkError(const core::string& msg)
		: Error(msg)
	{};
};
}
