#include "Resource.h"
#include "Error.h"

using namespace rsc;

Resource::Resource()
	: _isLoaded(false)
{
}

Resource::~Resource()
{
}


void Resource::load(core::shared_ptr<fs::IFileReader> fr) {
	_load(fr);
	_isLoaded = true;
}

bool Resource::isLoaded() const {
	return _isLoaded;
}
