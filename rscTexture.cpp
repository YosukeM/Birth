#include "rscTexture.h"

#include "TgaTextureLoader.h"

using namespace rsc;
using namespace textureloader;

Texture::Texture()
	: _repeatX(true),
	_repeatY(true),
	_magFilter(ogl::Texture::EF_NEAREST),
	_minFilter(ogl::Texture::EF_NEAREST)
{
}

Texture::~Texture() {
}

void Texture::bind() {
	if (!_isLoaded) return;
	_texture.bind();
}

void Texture::unbind() {
	_texture.unbind();
}

void Texture::setRepeatX(bool v) {
	if (_isLoaded) {
		_texture.setRepeatX(v);
	} else {
		_repeatX = v;
	}
}

void Texture::setRepeatY(bool v) {
	if (_isLoaded) {
		_texture.setRepeatY(v);
	} else {
		_repeatY = v;
	}
}

void Texture::setMagFilter(Texture::EFilter v) {
	if (_isLoaded) {
		_texture.setMagFilter(v);
	} else {
		_magFilter = v;
	}
}

void Texture::setMinFilter(Texture::EFilter v) {
	if (_isLoaded) {
		_texture.setMagFilter(v);
	} else {
		_minFilter = v;
	}
}

Vector2d<u32> Texture::getSize() const {
	if (!_isLoaded) return Vector2d<u32>();
	return _texture.getSize();
}

bool Texture::hasAlpha() const {
	if (!_isLoaded) return false;
	return _texture.hasAlpha();
}

void Texture::_load(core::shared_ptr<fs::IFileReader> fr) {
	TgaTextureLoader loader;
	loader.load(fr, _texture);
	_texture.setMagFilter(_magFilter);
	_texture.setMinFilter(_minFilter);
	_texture.setRepeatX(_repeatX);
	_texture.setRepeatY(_repeatY);
}
