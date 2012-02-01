#include "IFileReader.h"

void fs::IFileReader::getAllAsString(core::string& str) {
	str.clear();
	u64 size = getSize();
	char c;
	str.reserve(size);
	for (u64 i = 0; i < size; ++i) {
		read(static_cast<void*>(&c), 1);
		str.push_back(c);
	}
}

