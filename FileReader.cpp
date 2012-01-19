#include "FileReader.h"

using namespace fs;

FileReader::FileReader(std::ifstream* ifstream, u64 size)
	: _ifstream(ifstream), _size(size)
{

}

FileReader::~FileReader() {
	delete _ifstream;
}

unsigned FileReader::read(void* buffer, unsigned size_to_read) {
	_ifstream->read((char*)buffer, size_to_read);
	if (_ifstream->eof()) _ifstream->clear();
	return u32(_ifstream->gcount());
}

bool FileReader::seek(u64 pos, ESeekMode whence) {
	std::ios::seekdir dir;
	switch (whence) {
	case E_SEEK_BEG:
		dir = std::ios::beg;
		break;
	case E_SEEK_CUR:
		dir = std::ios::cur;
		break;
	case E_SEEK_END:
		dir = std::ios::end;
		break;
	}
	_ifstream->seekg(pos, dir);
	
	return _ifstream->good();
}

u64 FileReader::getSize() const {
	return _size;
}

u64 FileReader::tell() const {
	return _ifstream->tellg();
}
