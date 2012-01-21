#pragma once

#include "rscIManager.h"

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include "Error.h"
#include <boost/optional.hpp>

namespace fs {
	class IFileFactory;
}

namespace rsc {
	class Resource;

	class ASyncManager : public IManager {
		typedef core::unordered_map<core::string, core::shared_ptr<Mesh> > meshset_type;
		meshset_type _meshSet;

		typedef core::unordered_map<core::string, core::shared_ptr<Texture> > texset_type;
		texset_type _texSet;

		core::deque<core::shared_ptr<fs::IFileFactory> > _fileFactories;

		typedef core::shared_ptr<Resource> resource_type;
		typedef std::pair<core::string, resource_type> loading_type;
		core::deque<loading_type> _loadings;

		core::scoped_ptr<boost::thread> _thread;
		boost::mutex _mutex;

		boost::optional<Error> error;
	public:
		ASyncManager();
		~ASyncManager();

		void _threadFunc();

		core::shared_ptr<Mesh> getMesh(const core::string&);
		core::shared_ptr<Texture> getTexture(const core::string&);

		void addFileFactory(core::shared_ptr<fs::IFileFactory>);

		void update();
	};
}
