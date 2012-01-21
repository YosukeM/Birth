#pragma once

#include "rscIManager.h"
#include "IFileFactory.h"

namespace rsc {
class SyncManager : public IManager
{
	typedef core::unordered_map<core::string, core::shared_ptr<Mesh> > MeshMapType;
	MeshMapType _meshMap;
	typedef core::unordered_map<core::string, core::shared_ptr<Texture> > TexMapType;
	TexMapType _texMap;
	core::scoped_ptr<fs::IFileFactory> _fileFactory;
public:
	SyncManager();

	core::shared_ptr<Mesh> getMesh(const core::string& id);
	core::shared_ptr<Texture> getTexture(const core::string& id);
};

}
