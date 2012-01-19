#include "Material.h"
#include "GL/glfw.h"

using namespace ogl;

Material::Material()
	: _ambientColor(0), _diffuseColor(0), _specularColor(0),
	_emissionColor(0), _shiness(0.0f)
{
}

#define GETSETCOLOR(ev, iv)\
	void Material::set ## ev ## Color(const Color& color) {\
		_ ## iv ## Color = color;\
	}\
	Color Material::get ## ev ## Color() const {\
		return _ ## iv ## Color;\
	}

GETSETCOLOR(Ambient, ambient)
GETSETCOLOR(Diffuse, diffuse)
GETSETCOLOR(Specular, specular)
GETSETCOLOR(Emission, emission)

void Material::setShiness(float s) {
	_shiness = s;
}

float Material::getShiness() const {
	return _shiness;
}

void Material::bind() {
	glEnable(GL_LIGHTING);

	float amb[4], dif[4], spec[4], emis[4];
	_ambientColor.getAs4Values(amb);
	_diffuseColor.getAs4Values(dif);
	_specularColor.getAs4Values(spec);
	_emissionColor.getAs4Values(emis);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emis);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _shiness *128.0);
}

void Material::unbind() {
	glDisable(GL_LIGHTING);
}
