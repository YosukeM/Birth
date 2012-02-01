#pragma once

#include "gameNode.h"
#include "oglMaterial.h"

namespace rsc {
	class IManager;
}

class GLUquadric;

namespace game {
	class Ovum : public Node {
		GLUquadric* _gluQuad;
		ogl::Material _material;
	public:
		Ovum(core::shared_ptr<rsc::IManager>);
		~Ovum();
		void update(f32 t);

	protected:
		void _drawSolid();
	};
}