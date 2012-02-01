#pragma once

#include "Quaternion.h"

namespace game {
	namespace geom {

		/**
		 * geom::Tailはプレイヤーの尻尾の動きだけを担当するクラス
		 * 汎用性はほぼない
		 * JointはTailが内部で使ってるクラスだから気にする必要はない
		 */

		class Joint {
		public:
			float3d position;
			Quaternion rotation;
			void update(float, const Joint& prev_joint, float interval);
		};

		class Tail
		{
		public:
			float _radius, _length;
			u32 _radiusSpirit, _heightSpirit;
			core::vector<Joint> _joints;
			core::vector<float3d> _verts;
			core::vector<float3d> _norms;
			core::vector<u32> _indices;
			bool _drawed;
			core::vector<f32> _cos, _sin;

			float _levelToRadius(float) const;
			void _updateNormals();
		public:
			Tail(float radius, float length, u32 spirit_r, u32 spirit_h);
			void update(f32 t, const Quaternion& rotation);
			void draw();

		};

	}
}
