#include "rscSyncManager.h"
#include "FileFactory.h"
#include "rscMesh.h"
#include "rscTexture.h"

using namespace rsc;

SyncManager::SyncManager()
{
	_fileFactory.reset(new fs::FileFactory());
}

core::shared_ptr<Mesh> SyncManager::getMesh(const core::string& id) {
	MeshMapType::iterator itr = _meshMap.find(id);
	if (itr == _meshMap.end()) {
		core::shared_ptr<Mesh> mesh = core::make_shared<Mesh>();
		_meshMap[id] = mesh;
		mesh->load(_fileFactory->createFileReader(id.c_str()));
		return mesh;
	} else {
		return itr->second;
	}
}

core::shared_ptr<Texture> SyncManager::getTexture(const core::string& id) {
	return core::shared_ptr<Texture>();
}
