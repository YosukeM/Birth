#pragma once

namespace ogl {
	class PerspectiveCamera {
		float3d _position, _lookAt, _up;
		float _near, _far, _fov;
	public:
		PerspectiveCamera();
		
		void setNear(float);
		float getNear() const;

		void setFar(float);
		float getFar() const;

		void setFov(float);
		float getFov() const;

		void setPosition(const float3d&);
		float3d getPosition() const;

		void setLookAt(const float3d&);
		float3d getLookAt() const;
		
		void setUpVector(const float3d&);
		float3d getUpVector() const;

		void setMatrix();
	};
}