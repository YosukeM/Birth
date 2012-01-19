#pragma once

#include "oglTexture.h"

namespace fs {
	class IFileReader;
}

namespace rsc {
	namespace textureloader {
		class ITextureLoader {
		public:
			ITextureLoader() {}
			virtual ~ITextureLoader() {}
			
			virtual bool isAvailableExtension(const core::string&) const { return false; }
			virtual void load(core::shared_ptr<fs::IFileReader>, ogl::Texture&) = 0;
		};
	}
}