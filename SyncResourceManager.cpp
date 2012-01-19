#include "SyncResourceManager.h"
#include "FileFactory.h"
#include "Mesh.h"
#include "Texture.h"

using namespace rsc;

SyncResourceManager::SyncResourceManager()
{
	_fileFactory.reset(new fs::FileFactory());
}

core::shared_ptr<Mesh> SyncResourceManager::getMesh(const core::string& id) {
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

core::shared_ptr<Texture> SyncResourceManager::getTexture(const core::string& id) {
	return core::shared_ptr<Texture>();
}
