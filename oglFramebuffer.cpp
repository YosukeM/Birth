#include "oglFramebuffer.h"

#include <GL/glew.h>
#include <GL/glfw.h>

using namespace ogl;

Framebuffer::Framebuffer()
	:_id(0)
{
	glGenFramebuffersEXT(1, &_id);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _id);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

Framebuffer::~Framebuffer() {
	glDeleteFramebuffersEXT(1, &_id);
}

void Framebuffer::attach(EAttachment attach, const Texture& texture) {
	int attach2 = 0;
	switch (attach) {
	case EA_COLOR_0: attach2 = GL_COLOR_ATTACHMENT0_EXT; break;
	case EA_COLOR_1: attach2 = GL_COLOR_ATTACHMENT1_EXT; break;
	case EA_COLOR_2: attach2 = GL_COLOR_ATTACHMENT2_EXT; break;
	case EA_COLOR_3: attach2 = GL_COLOR_ATTACHMENT3_EXT; break;
	case EA_COLOR_4: attach2 = GL_COLOR_ATTACHMENT4_EXT; break;
	case EA_COLOR_5: attach2 = GL_COLOR_ATTACHMENT5_EXT; break;
	case EA_COLOR_6: attach2 = GL_COLOR_ATTACHMENT6_EXT; break;
	case EA_COLOR_7: attach2 = GL_COLOR_ATTACHMENT7_EXT; break;
	case EA_COLOR_8: attach2 = GL_COLOR_ATTACHMENT8_EXT; break;
	case EA_COLOR_9: attach2 = GL_COLOR_ATTACHMENT9_EXT; break;
	case EA_COLOR_10: attach2 = GL_COLOR_ATTACHMENT10_EXT; break;
	case EA_COLOR_11: attach2 = GL_COLOR_ATTACHMENT11_EXT; break;
	case EA_COLOR_12: attach2 = GL_COLOR_ATTACHMENT12_EXT; break;
	case EA_COLOR_13: attach2 = GL_COLOR_ATTACHMENT13_EXT; break;
	case EA_COLOR_14: attach2 = GL_COLOR_ATTACHMENT14_EXT; break;
	case EA_COLOR_15: attach2 = GL_COLOR_ATTACHMENT15_EXT; break;
	case EA_DEPTH: attach2 = GL_DEPTH_ATTACHMENT_EXT; break;
	case EA_STENCIL: attach2 = GL_STENCIL_ATTACHMENT_EXT; break;
	}

	bind();
	glFramebufferTexture2DEXT(
		GL_FRAMEBUFFER_EXT,
		attach2,
		texture.isRect()? GL_TEXTURE_RECTANGLE_EXT : GL_TEXTURE_2D,
		texture.getId(),
		0
	);
	unbind();
}

void Framebuffer::bind() {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _id);
}

void Framebuffer::unbind() {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}
