#pragma once

#include "gameNode.h"
#include "oglMaterial.h"
#include "rscMesh.h"
#include "rscProgram.h"
#include "Angle2d.h"

#include "gameGeomTail.h"

namespace rsc {
	class IManager;
}

namespace game {
	class Player : public Node {
		ogl::Material _material;
		core::shared_ptr<rsc::Program> _program;
		core::shared_ptr<rsc::Mesh> _mesh;

		geom::Tail _tail;
		Angle2d _theta;
		float2d _pointer;

		void _drawSolid();

	public:
		Player(core::shared_ptr<rsc::IManager>);

		float3d getPosition() const;

		void update(float);
		void draw(Node::EDrawState);
	};
}
