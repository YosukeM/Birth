#include "Error.h"

Error::Error()
	: std::runtime_error("")
{
}

Error::Error(const char* message)
	: std::runtime_error(message)
{
}

Error::Error(const core::string& message)
	: std::runtime_error(message.c_str())
{
}
