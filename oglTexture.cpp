#include "oglTexture.h"

#include <GL/glew.h>
#include <GL/glfw.h>

using namespace ogl;

namespace {
int filter_val(Texture::EFilter filter) {
	switch (filter) {
	case Texture::EF_LINEAR: return GL_LINEAR;
	case Texture::EF_NEAREST: return GL_NEAREST;
	}
	return GL_LINEAR;
}
int pixelstore_val(Texture::Source::EPixelStore ps) {
	int format;
	switch (ps) {
	case Texture::Source::EPS_RGB: format = GL_RGB; break;
	case Texture::Source::EPS_LUMINANCE: format = GL_LUMINANCE; break;
	case Texture::Source::EPS_LUMINANCE_ALPHA: format = GL_LUMINANCE_ALPHA; break;
	case Texture::Source::EPS_DEPTH: format = GL_DEPTH_COMPONENT; break;
	default: format = GL_RGBA; break;
	}
	return format;
}
bool sizeIsRect(const uint2d& size) {
	if (size.x != size.y) return true;
	if (size.x == 0) return false;
	if ( ( size.x & (size.x - 1) ) == 0) return true;
	else return false;
}

u32 sizeOfNotRect(const uint2d& size) {
	int max = size.x > size.y? size.x : size.y;
	int ret = 0;
	for(u16 shift=2; shift<31; shift++){
		ret = 1 << shift;
		if (ret > max) {
			return ret;
		}
	}
	return ret;
}

}

Texture::Texture()
	: _id(0), _hasAlpha(false), _isRect(false)
{
	glGenTextures(1, &_id);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	unbind();
}

Texture::Texture(const uint2d& size, Source::EPixelStore ps)
	: _id(0), _hasAlpha(false), _isRect(false)
{
	_isRect = sizeIsRect(size);
	_size = size;
	if (ps == Source::EPS_LUMINANCE_ALPHA || ps == Source::EPS_RGBA) {
		_hasAlpha = true;
	}
	glGenTextures(1, &_id);
	bind();
	int format = pixelstore_val(ps);
	int format_byte = (ps == Source::EPS_DEPTH? GL_FLOAT : GL_UNSIGNED_BYTE);
	u32 texture_type = _isRect? GL_TEXTURE_RECTANGLE_EXT : GL_TEXTURE_2D;
	glTexImage2D(texture_type, 0, format, size.x, size.y, 0, format, format_byte, NULL);
	glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	unbind();
}

Texture::Texture(const Source& src)
	: _id(0), _hasAlpha(false), _isRect(false)
{
	glGenTextures(1, &_id);
	source(src);
}

void Texture::source(const Source& src) {
	int format = pixelstore_val(src.pixelStore);
	_isRect = sizeIsRect(src.size);

	switch (src.pixelStore) {
	case Source::EPS_LUMINANCE_ALPHA:
	case Source::EPS_RGBA:
		_hasAlpha = true;
	default:
		_hasAlpha = false;
	}

	bind();
	_size = src.size;

	u32 texture_type = _isRect? GL_TEXTURE_RECTANGLE_EXT : GL_TEXTURE_2D;

	glTexImage2D(texture_type, 0, format, src.size.x, src.size.y, 0, format, GL_UNSIGNED_BYTE, src.data);
	glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(texture_type, 0);
	glDisable(texture_type);
}

Texture::~Texture() {
	glDeleteTextures(1, &_id);
}

unsigned Texture::getId() const {
	return _id;
}

void Texture::bind() {
	u32 texture_type = _isRect? GL_TEXTURE_RECTANGLE_EXT : GL_TEXTURE_2D;
	glEnable(texture_type);
	glBindTexture(texture_type, _id);
}

void Texture::unbind() {
	u32 texture_type = _isRect? GL_TEXTURE_RECTANGLE_EXT : GL_TEXTURE_2D;
	glBindTexture(texture_type, 0);
	glDisable(texture_type);
}

#define WRAP_VAL(v) ((v)? GL_REPEAT : GL_CLAMP)

void Texture::setRepeatX(bool repeat) {
	glTexParameteri(_isRect? GL_TEXTURE_RECTANGLE_EXT : GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WRAP_VAL(repeat));
}

void Texture::setRepeatY(bool repeat) {
	glTexParameteri(_isRect? GL_TEXTURE_RECTANGLE_EXT : GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WRAP_VAL(repeat));
}

void Texture::setMagFilter(EFilter filter) {
	glTexParameteri(_isRect? GL_TEXTURE_RECTANGLE_EXT : GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_val(filter));
}

void Texture::setMinFilter(EFilter filter) {
	glTexParameteri(_isRect? GL_TEXTURE_RECTANGLE_EXT : GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_val(filter));
}

void Texture::draw() {
	bind();
	float2d size = getRBTexCoord();
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		glTexCoord2f(size.x, 0.0);
		glVertex2f(1.0f, 0.0f);
		glTexCoord2f(size.x, size.y);
		glVertex2f(1.0f, 1.0f);
		glTexCoord2f(0.0f, size.y);
		glVertex2f(0.0f, 1.0f);
	glEnd();
	unbind();
}

float2d Texture::getRBTexCoord() const {
	if (_isRect) {
		return float2d(getSize().x, getSize().y);
	} else {
		u32 size = sizeOfNotRect(getSize());
		return float2d(float(size), float(size));
	}
}