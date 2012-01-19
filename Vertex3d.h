#pragma once

#include <GL/glew.h>

#include "Color.h"
#include <boost/utility/enable_if.hpp>

namespace ogl {

class Vertex3dTCN {
public:
	struct hasColor { enum {value = 1}; };
	struct hasNormal { enum {value = 1}; };
	struct hasTexCoord { enum {value = 1}; };
	static const u32 format = GL_T2F_C4F_N3F_V3F;

	float2d texCoord;
	Color color;
	float3d normal;
	float3d position;

	Vertex3dTCN() {}

	void setTexCoord(const float2d& v) { texCoord = v; }
	void setColor(const Color& v) { color = v; }
	void setNormal(const float3d& v) { normal = v; }
};

class Vertex3dCN {
public:
	struct hasColor { enum {value = 1}; };
	struct hasNormal { enum {value = 1}; };
	struct hasTexCoord { enum {value = 0}; };
	static const u32 format = GL_C4F_N3F_V3F;

	Color color;
	float3d normal;
	float3d position;

	Vertex3dCN() {}

	void setTexCoord(const float2d& v) {}
	void setColor(const Color& v) { color = v; }
	void setNormal(const float3d& v) { normal = v; }
};

class Vertex3dTC {
public:
	struct hasColor { enum {value = 1}; };
	struct hasNormal { enum {value = 0}; };
	struct hasTexCoord { enum {value = 1}; };
	static const u32 format = GL_T2F_C4UB_V3F;

	float2d texCoord;
	Color color;
	float3d position;

	Vertex3dTC() {}
	void setTexCoord(const float2d& v) { texCoord = v; }
	void setColor(const Color& v) { color = v; }
	void setNormal(const float3d& v) {}
};

class Vertex3dC {
public:
	struct hasColor { enum {value = 1}; };
	struct hasNormal { enum {value = 0}; };
	struct hasTexCoord { enum {value = 0}; };
	static const u32 format = GL_C4UB_V3F;

	Color color;
	float3d position;

	Vertex3dC() {}
	void setTexCoord(const float2d& v) {}
	void setColor(const Color& v) { color = v; }
	void setNormal(const float3d& v) {}
};

class Vertex3dTN {
public:
	struct hasColor { enum {value = 0}; };
	struct hasNormal { enum {value = 1}; };
	struct hasTexCoord { enum {value = 1}; };
	static const u32 format = GL_T2F_N3F_V3F;

	float2d texCoord;
	float3d normal;
	float3d position;

	Vertex3dTN() {}
	void setTexCoord(const float2d& v) { texCoord = v; }
	void setColor(const Color& v) {}
	void setNormal(const float3d& v) { normal = v; }
};

class Vertex3dN {
public:
	struct hasColor { enum {value = 0}; };
	struct hasNormal { enum {value = 1}; };
	struct hasTexCoord { enum {value = 0}; };
	static const u32 format = GL_N3F_V3F;

	float3d normal;
	float3d position;

	Vertex3dN() {}
	void setTexCoord(const float2d& v) {}
	void setColor(const Color& v) {}
	void setNormal(const float3d& v) { normal = v; }
};

class Vertex3dT {
public:
	struct hasColor { enum {value = 0}; };
	struct hasNormal { enum {value = 0}; };
	struct hasTexCoord { enum {value = 1}; };
	static const u32 format = GL_T2F_V3F;

	float2d texCoord;
	float3d position;

	Vertex3dT() {}
	void setTexCoord(const float2d& v) { texCoord = v; }
	void setColor(const Color& v) {}
	void setNormal(const float3d& v) {}
};

class Vertex3d {
public:
	struct hasColor { enum {value = 0}; };
	struct hasNormal { enum {value = 0}; };
	struct hasTexCoord { enum {value = 0}; };
	static const u32 format = GL_V3F;

	float3d position;

	Vertex3d() {}
	void setTexCoord(const float2d& v) {}
	void setColor(const Color& v) {}
	void setNormal(const float3d& v) {}
};

}
