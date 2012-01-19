#include "AsyncResourceManager.h"
#include "FileFactory.h"

#include "Resource.h"
#include "Mesh.h"

using namespace rsc;
/*
ASyncResourceManager::ASyncResourceManager() {
	_fileFactories.push_back(core::make_shared<fs::FileFactory>());
	_thread.reset(new boost::thread(
					  boost::bind(&ASyncResourceManager::_threadFunc, this))
				  );
}

ASyncResourceManager::~ASyncResourceManager() {
	if (_thread->joinable()) _thread->join();
}

void ASyncResourceManager::_threadFunc() {
	try {
		while (true) {
			{
				boost::mutex::scoped_lock(_mutex);
				if (_loadings.size()) {
					loading_type p = _loadings.front();
					_loadings.pop_front();
					fs::IFileReader *fr = NULL;
					foreach (core::shared_ptr<fs::IFileFactory> ff, _fileFactories) {
						fr = ff->createFileReader(p.first.c_str());
						if (fr) break;
					}
					if (!fr) {
						throw Error("Cannot find available file reader");
					}
					p.second->load(fr);
				}
			}
			boost::thread::sleep(boost::get_system_time() + boost::posix_time::milliseconds(1));
		}
	} catch (Error& e) {
		boost::mutex::scoped_lock(_mutex);
		error = e;
	} catch (std::bad_alloc&e) {
		boost::mutex::scoped_lock(_mutex);
		error = Error("Allocation failed while loading");
	} catch (...) {
		boost::mutex::scoped_lock(_mutex);
		error = Error("Unknown Error occured while loading");
	}
}

core::shared_ptr<Mesh> ASyncResourceManager::getMesh(const core::string& id) {
	meshset_type::iterator itr = _meshSet.find(id);
	if (itr == _meshSet.end()) {
		core::shared_ptr<Mesh> mesh = core::make_shared<Mesh>();
		_meshSet[id] = mesh;

		boost::mutex::scoped_lock(_mutex);
		_loadings.push_back(loading_type(id, core::shared_static_cast<Resource>(mesh)));
		return mesh;
	} else {
		return itr->second;
	}
}

core::shared_ptr<Texture> ASyncResourceManager::getTexture(const core::string&) {
	return core::shared_ptr<Texture>();
}

void ASyncResourceManager::addFileFactory(core::shared_ptr<fs::IFileFactory> ff) {
	_fileFactories.push_front(ff);
}

void ASyncResourceManager::update() {
	boost::mutex::scoped_lock(_mutex);
	if (error)	{
		throw error.get();
	}
}
*/
