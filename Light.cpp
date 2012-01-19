#include "Light.h"
#include "GL/glfw.h"

#include "GetterSetter.h"

using namespace ogl;

Light::Light(bool is_directional)
	: _isDirectional(is_directional),
	_position(0.0f), _spotDirection(0.0f, -1.0f, 0.0f),
	_isSpotCutoffEnabled(false), _spotExponent(0.0f), _spotCutoff(3.1415926535f * 0.25f),
	_constantAttenuation(1.0f), _linearAttenuation(0.0f), _quadraticAttenuation(0.0f)
{

}

#define GETSET_L(type, ev, iv) GETSET(Light, type, ev, iv)
#define GETSET_PL(type, ev, iv) GETSET_P(Light, type, ev, iv)

GETSET_L(Color, AmbientColor, _ambientColor)
GETSET_L(Color, DiffuseColor, _diffuseColor)
GETSET_L(Color, SpecularColor, _specularColor)

GETSET_PL(bool, IsDirectional, _isDirectional)
GETSET_L(float3d, Position, _position)
GETSET_L(float3d, SpotDirection, _spotDirection)

GETSET_PL(float, SpotExponent, _spotExponent)
GETTER_P(Light, float, SpotCutoff, _spotCutoff)

void Light::setSpotCutoff(float v) {
	_spotCutoff = v;
	_isSpotCutoffEnabled = true;
}

void Light::disableSpotCutoff() {
	_isSpotCutoffEnabled = false;
}

GETSET_PL(float, ConstantAttenuation, _constantAttenuation)
GETSET_PL(float, LinearAttenuation, _linearAttenuation)
GETSET_PL(float, QuadraticAttenuation, _quadraticAttenuation)

void Light::setAttenuation(float constant, float linear, float quadratic) {
	_constantAttenuation = constant;
	_linearAttenuation = linear;
	_quadraticAttenuation = quadratic;
}

void Light::attach(int light_tag) {
	float ambient[4], diffuse[4], specular[4];
	_ambientColor.getAs4Values(ambient);
	_diffuseColor.getAs4Values(diffuse);
	_specularColor.getAs4Values(specular);
	const float pos[4] = {
		_position.x, _position.y, _position.z, _isDirectional? 0.0f : 1.0f
	};
	const float dir[4] = {
		_spotDirection.x, _spotDirection.y, _spotDirection.z
	};

	glLightfv(light_tag, GL_AMBIENT, ambient);
	glLightfv(light_tag, GL_DIFFUSE, diffuse);
	glLightfv(light_tag, GL_SPECULAR, specular);
	glLightfv(light_tag, GL_POSITION, pos);
	glLightfv(light_tag, GL_SPOT_DIRECTION, dir);
	glLightf(light_tag, GL_SPOT_EXPONENT, _spotExponent);
	if (_isSpotCutoffEnabled) {
		glLightf(light_tag, GL_SPOT_CUTOFF, _spotCutoff * 180.0f / 3.1415926535897932f);
	} else {
		glLighti(light_tag, GL_SPOT_CUTOFF, 180);
	}
	glLightf(light_tag, GL_CONSTANT_ATTENUATION, _constantAttenuation);
	glLightf(light_tag, GL_LINEAR_ATTENUATION, _linearAttenuation);
	glLightf(light_tag, GL_QUADRATIC_ATTENUATION, _quadraticAttenuation);
}
