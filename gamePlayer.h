#pragma once

#include "gameNode.h"
#include "oglMaterial.h"
#include "rscMesh.h"
#include "oglProgram.h"
#include "Angle2d.h"

namespace rsc {
	class IManager;
}

namespace game {
	class Player : public Node {
		ogl::Material _material;
		ogl::Program _program;
		core::shared_ptr<rsc::Mesh> _mesh;

		class TailGeom {
			float _radius, _length;
			u32 _radiusSpirit, _heightSpirit;
			core::vector<float3d> _joints;
			core::vector<float3d> _verts;
			core::vector<float3d> _norms;
			core::vector<u32> _indices;
			bool _drawed;
			core::vector<f32> _cos, _sin;

			float _levelToRadius(float) const;
			void _updateNormals();
		public:
			TailGeom(float radius, float length, u32 spirit_r, u32 spirit_h);
			void update(f32 t, const float3d& dir);
			void draw();
		};

		TailGeom _tail;
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