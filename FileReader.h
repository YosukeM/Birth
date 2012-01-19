#pragma once

#include "IFileReader.h"
#include <fstream>

namespace fs {

class FileReader : public IFileReader {
	std::ifstream* _ifstream;
	u64 _size;
public:
	FileReader(std::ifstream* ifstream, u64 size);
	~FileReader();
	
	virtual unsigned read(void* buffer, unsigned size_to_read);
	virtual bool seek(u64 pos, ESeekMode whence = E_SEEK_BEG);
	virtual u64 getSize() const;
	virtual u64 tell() const;
};

}
