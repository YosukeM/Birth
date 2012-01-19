#pragma once

namespace fs {
	class IFileReader;

	class IFileFactory {
	public:
		virtual ~IFileFactory() {}

		virtual core::shared_ptr<IFileReader> createFileReader(const core::string& filepath) = 0;
	};
}
