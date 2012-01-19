#include "Mesh.h"
#include "IFileReader.h"
#include "ObjMeshLoader.h"

using namespace rsc;

Mesh::Mesh()
{
}

Mesh::~Mesh() {
}

void Mesh::_load(core::shared_ptr<fs::IFileReader> fr) {
	meshloader::ObjMeshLoader loader;
	loader.load(fr, _meshbuf);
}

namespace {
	struct Drawer : boost::static_visitor<void> {
		template <typename T>
		void operator()(T* meshbuffer) const {
			meshbuffer->draw();
		}
	};
}

void Mesh::draw() {
	if (!_isLoaded) return;
	foreach (meshbuffer_type omb, _meshbuf) {
		boost::apply_visitor(Drawer(), omb);
	}
}
