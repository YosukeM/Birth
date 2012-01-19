#pragma once

#include "ITextureLoader.h"

namespace rsc {
	namespace textureloader {
		class TgaTextureLoader : public ITextureLoader {
		public:
			TgaTextureLoader() {}
			~TgaTextureLoader() {}
			bool isAvailableExtension(const core::string&) const;
			void load(core::shared_ptr<fs::IFileReader>, ogl::Texture&);
		};
	}
}