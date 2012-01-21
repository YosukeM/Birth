#pragma once

#include "Vector3d.h"
#include "Color.h"

namespace ogl {
	class Light {
		float3d _position;
		bool _isDirectional;

		Color _ambientColor;
		Color _diffuseColor;
		Color _specularColor;

		float3d _spotDirection;
		float _spotCutoff;
		float _spotExponent;
		bool _isSpotCutoffEnabled;

		float _constantAttenuation;
		float _linearAttenuation;
		float _quadraticAttenuation;

		int _id;

	public:
		Light(bool is_directional);

		void setPosition(const float3d&);
		float3d getPosition() const;

		void isDirectional() const;
		void setIsDirectional(bool);
		bool getIsDirectional() const;

		void setAmbientColor(const Color& color);
		Color getAmbientColor() const;

		void setDiffuseColor(const Color& color);
		Color getDiffuseColor() const;

		void setSpecularColor(const Color& color);
		Color getSpecularColor() const;

		void setSpotDirection(const float3d&);
		float3d getSpotDirection() const;

		void setSpotCutoff(float);
		float getSpotCutoff() const;
		void disableSpotCutoff();

		void setSpotExponent(float);
		float getSpotExponent() const;

		void setAttenuation(float constant, float linear = 0.0f, float quadratic = 0.0f);

		void setConstantAttenuation(float);
		float getConstantAttenuation() const;

		void setLinearAttenuation(float);
		float getLinearAttenuation() const;

		void setQuadraticAttenuation(float);
		float getQuadraticAttenuation() const;

		void attach(int light_tag);
	};
}
