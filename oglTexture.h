#pragma once

#include "Vector2d.h"

namespace ogl {

class Texture {
	unsigned _id;
	Vector2d<u32> _size;
	bool _hasAlpha;
	bool _isRect;

	Texture(const Texture&);
	Texture& operator=(const Texture&);
public:
	class Source {
	public:
		typedef enum {
			EPS_RGB,
			EPS_RGBA,
			EPS_LUMINANCE,
			EPS_LUMINANCE_ALPHA,
			EPS_DEPTH
		} EPixelStore;
		EPixelStore pixelStore;
		Vector2d<u32> size;
		void* data;
	};

	typedef enum {
		EF_NEAREST,
		EF_LINEAR
	} EFilter;

	Texture();
	Texture(const uint2d&, Source::EPixelStore);
	Texture(const Source&);
	~Texture();

	void source(const Source&);

	unsigned getId() const;

	void bind();
	void unbind();

	void setRepeatX(bool);
	void setRepeatY(bool);

	void setMagFilter(EFilter);
	void setMinFilter(EFilter);

	Vector2d<u32> getSize() const { return _size; }

	bool hasAlpha() const { return _hasAlpha; }
	bool isRect() const {return _isRect; }

	void draw();
	float2d getRBTexCoord() const;
};

}
