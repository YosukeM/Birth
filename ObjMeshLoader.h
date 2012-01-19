#pragma once

#include "IMeshLoader.h"

namespace rsc {
	namespace meshloader {
		class ObjMeshLoader : public IMeshLoader {
		public:
			ObjMeshLoader() {}
			virtual bool isAvailableExtension(const core::string&) const;
			virtual void load(core::shared_ptr<fs::IFileReader>, core::vector<Mesh::meshbuffer_type>&);
		};
	}
}
