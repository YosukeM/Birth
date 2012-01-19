#pragma once

#include "Color.h"

namespace ogl {
	class Material {
		Color _ambientColor, _diffuseColor, _specularColor, _emissionColor;
		float _shiness;
	public:
		Material();

		void setAmbientColor(const Color&);
		Color getAmbientColor() const;

		void setDiffuseColor(const Color&);
		Color getDiffuseColor() const;

		void setSpecularColor(const Color&);
		Color getSpecularColor() const;

		void setEmissionColor(const Color&);
		Color getEmissionColor() const;

		void setShiness(float);
		float getShiness() const;

		void bind();
		void unbind();
	};
}
