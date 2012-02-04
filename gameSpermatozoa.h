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
	class Ovum;

	/**
	 * PlayerとSubordinatesの基底クラス。
	 * このクラスを継承したら、実装側で_tail.updateを呼んでください
	 */
	class Spermatozoa : public Node {
	protected:
		ogl::Material _material;
		core::shared_ptr<rsc::Program> _program;
		core::shared_ptr<rsc::Mesh> _mesh;

		geom::Tail _tail;
		core::shared_ptr<Ovum> _ovum;

		void _drawSolid();
		virtual void _onDraw() {};

		Spermatozoa(core::shared_ptr<rsc::IManager>);

	public:
		void draw(Node::EDrawState);

		virtual void setOvum(core::shared_ptr<Ovum>);
	};
}
