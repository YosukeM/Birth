#pragma once

#include "oglMeshbuffer.h"
#include "rscResource.h"

namespace rsc {
class Mesh : public Resource
{
public:
	typedef core::variant<
				ogl::Meshbuffer<ogl::Vertex3d>*,
				ogl::Meshbuffer<ogl::Vertex3dC>*,
				ogl::Meshbuffer<ogl::Vertex3dCN>*,
				ogl::Meshbuffer<ogl::Vertex3dN>*,
				ogl::Meshbuffer<ogl::Vertex3dT>*,
				ogl::Meshbuffer<ogl::Vertex3dTC>*,
				ogl::Meshbuffer<ogl::Vertex3dTCN>*,
				ogl::Meshbuffer<ogl::Vertex3dTN>*
	> meshbuffer_type;
	core::vector<meshbuffer_type> _meshbuf;
private:
	void _load(core::shared_ptr<fs::IFileReader>);
public:
	Mesh();
	~Mesh();

	void draw();
};
}
