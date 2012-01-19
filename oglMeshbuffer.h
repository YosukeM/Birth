#pragma once

#include <GL/glew.h>
#include <GL/glfw.h>

#include "Vertex3d.h"

namespace ogl {

template <typename VertT, typename IndxT = u32>
class Meshbuffer {
public:
	typedef enum {
		EDM_POINTS,
		EDM_LINES,
		EDM_LINE_STRIP,
		EDM_LINE_LOOP,
		EDM_TRIANGLES,
		EDM_TRIANGLE_STRIP,
		EDM_TRIANGLE_FAN,
		EDM_QUADS,
		EDM_QUAD_STRIP,
		EDM_POLYGON
	} EDrawMode;
	typedef VertT VertexType;
	typedef IndxT IndexType;
private:
	u32 _vertBuf;
	u32 _indxBuf;
	u32 _indicesSize;
	u32 _drawMode;
	Meshbuffer(const Meshbuffer&);
	Meshbuffer& operator=(const Meshbuffer&);

public:
	Meshbuffer()
		: _vertBuf(0), _indxBuf(0), _indicesSize(0), _drawMode(GL_TRIANGLES)
	{
	}

	~Meshbuffer() {
		glDeleteBuffers(1, &_vertBuf);
		glDeleteBuffers(1, &_indxBuf);
	}

	void generate(const core::vector<VertT>& verts, const core::vector<IndxT>& indices, EDrawMode draw_mode = EDM_TRIANGLES) {
		switch (draw_mode) {
		case EDM_POINTS: _drawMode = GL_POINTS; break;
		case EDM_LINES: _drawMode = GL_LINES; break;
		case EDM_LINE_STRIP: _drawMode = GL_LINE_STRIP; break;
		case EDM_LINE_LOOP: _drawMode = GL_LINE_LOOP; break;
		case EDM_TRIANGLES: _drawMode = GL_TRIANGLES; break;
		case EDM_TRIANGLE_STRIP: _drawMode = GL_TRIANGLE_STRIP; break;
		case EDM_TRIANGLE_FAN: _drawMode = GL_TRIANGLE_FAN; break;
		case EDM_QUADS: _drawMode = GL_QUADS; break;
		case EDM_QUAD_STRIP: _drawMode = GL_QUAD_STRIP; break;
		case EDM_POLYGON: _drawMode = GL_POLYGON; break;
		}

		glGenBuffers(1, &_vertBuf);
		glBindBuffer(GL_ARRAY_BUFFER, _vertBuf);
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(VertT), static_cast<const GLvoid*>(verts.data()), GL_STATIC_DRAW);

		glGenBuffers(1, &_indxBuf);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indxBuf);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(IndxT), static_cast<const GLvoid*>(indices.data()), GL_STATIC_DRAW);
		_indicesSize = indices.size();

		unbind();
	}

	void bind() {
		glBindBuffer(GL_ARRAY_BUFFER, _vertBuf);

		if (VertT::hasNormal::value) glEnableClientState(GL_NORMAL_ARRAY);
		if (VertT::hasColor::value) glEnableClientState(GL_COLOR_ARRAY);
		if (VertT::hasTexCoord::value) glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indxBuf);
	}

	void unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		if (VertT::hasNormal::value) glDisableClientState(GL_NORMAL_ARRAY);
		if (VertT::hasColor::value) glDisableClientState(GL_COLOR_ARRAY);
		if (VertT::hasTexCoord::value) glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	void draw() {
		bind();
		glInterleavedArrays(VertT::format, 0, NULL);
		glDrawElements(
			_drawMode,
			_indicesSize,
			sizeof(IndxT) == 4? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT,
			NULL
		);
		unbind();
	}
};

}
