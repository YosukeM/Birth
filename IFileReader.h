#pragma once

namespace fs {
	class IFileReader {
	public:
		typedef enum {
			E_SEEK_BEG,
			E_SEEK_CUR,
			E_SEEK_END,
		} ESeekMode;
		virtual ~IFileReader() {};
		virtual unsigned read(void* buffer, unsigned size_to_read) = 0;
		virtual bool seek(u64 pos, ESeekMode whence = E_SEEK_BEG) = 0;
		virtual u64 getSize() const = 0;
		virtual u64 tell() const = 0;

		virtual void getAllAsString(core::string&);
	};
};
