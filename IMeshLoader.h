#pragma once

#include "Mesh.h"

namespace rsc {
	namespace meshloader {
		class IMeshLoader {
		public:
			IMeshLoader() {}
			virtual ~IMeshLoader() {}
			virtual bool isAvailableExtension(const core::string&) const { return false; }
			virtual void load(core::shared_ptr<fs::IFileReader>, core::vector<Mesh::meshbuffer_type>&) = 0;
		};
	}
}
