#pragma once

#include "IFileFactory.h"
#include "FileReader.h"

namespace fs {
	class FileFactory : public IFileFactory {
	public:
		core::shared_ptr<IFileReader> createFileReader(const core::string& filepath);
	};
};
