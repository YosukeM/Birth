#pragma once

#include "oglTexture.h"

namespace ogl {

class Framebuffer {
	unsigned _id;
public:
	typedef enum {
		EA_COLOR_0,
		EA_COLOR_1,
		EA_COLOR_2,
		EA_COLOR_3,
		EA_COLOR_4,
		EA_COLOR_5,
		EA_COLOR_6,
		EA_COLOR_7,
		EA_COLOR_8,
		EA_COLOR_9,
		EA_COLOR_10,
		EA_COLOR_11,
		EA_COLOR_12,
		EA_COLOR_13,
		EA_COLOR_14,
		EA_COLOR_15,
		EA_STENCIL,
		EA_DEPTH
	} EAttachment;

	Framebuffer();
	~Framebuffer();

	void attach(EAttachment attach, const Texture& texture);
	void bind();
	void unbind();
};

}
