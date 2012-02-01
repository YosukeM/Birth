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

	/**
	 * Player��Subordinates�̊��N���X�B
	 * ���̃N���X���p��������A��������_tail.update���Ă�ł�������
	 */
	class Spermatozoa : public Node {
	protected:
		ogl::Material _material;
		core::shared_ptr<rsc::Program> _program;
		core::shared_ptr<rsc::Mesh> _mesh;

		geom::Tail _tail;

		void _drawSolid();
		virtual void _onDraw() {};

		Spermatozoa(core::shared_ptr<rsc::IManager>);

	public:
		void draw(Node::EDrawState);
	};
}
