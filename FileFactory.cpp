#include "FileFactory.h"
#include "Error.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <boost/filesystem/convenience.hpp>
#endif

core::shared_ptr<fs::IFileReader> fs::FileFactory::createFileReader(const core::string& filepath) {
	std::ifstream* stream;
	u64 size;
	try {
#ifdef _WIN32
		HANDLE handle = CreateFileA(filepath.c_str(), GENERIC_READ , 0 , NULL, OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL , NULL);
		if (handle == INVALID_HANDLE_VALUE) {
			throw Error("");
		}
		DWORD low, high;
		low = GetFileSize(handle, &high);
		size = low + (high << 16);
		CloseHandle(handle);
#else
		size = boost::filesystem::file_size(core::string(filepath));
#endif
		stream = new std::ifstream(filepath, std::ios::binary);
	} catch (...) {
		throw Error("Cannot open file " + filepath);
	}
	try {
		return core::shared_static_cast<fs::IFileReader>(core::make_shared<fs::FileReader>(stream, size));
	} catch (std::runtime_error& e) {
		delete stream;
		throw e;
	} catch (...) {
		delete stream;
	}
}