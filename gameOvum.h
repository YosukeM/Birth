#pragma once

#include "gameNode.h"
#include "oglMaterial.h"

namespace rsc {
	class IManager;
	class Program;
}

class GLUquadric;

namespace game {
	class Ovum : public Node {
		GLUquadric* _gluQuad;
		ogl::Material _outerMaterial, _innerMaterial;
		core::shared_ptr<rsc::Program> _program;
	public:
		static const float RADIUS;

		Ovum(core::shared_ptr<rsc::IManager>);
		~Ovum();
		void update(f32 t);

	protected:
		void _drawSolid();
	};
}