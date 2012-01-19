#pragma once

#include <stdexcept>

class Error : public std::runtime_error
{
public:
	Error();
	Error(const char*);
	Error(const core::string&);
};
