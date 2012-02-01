#include "TgaTextureLoader.h"

#include <GL/glfw.h>
#include "IFileReader.h"
#include "Error.h"

#include <cstdlib>

using namespace rsc::textureloader;

bool TgaTextureLoader::isAvailableExtension(const core::string& ext) const {
	return ext == "tga";
}

void TgaTextureLoader::load(core::shared_ptr<fs::IFileReader> fr, ogl::Texture& texture) {
	ogl::Texture::Source source;

	GLFWimage image;
	core::string str;
	fr->getAllAsString(str);

	if (glfwReadMemoryImage(str.data(), str.size(), &image, GLFW_NO_RESCALE_BIT) == GL_FALSE) {
		throw Error("Cannot load tga texture");
	}

	source.size = Vector2d<u32>(image.Width, image.Height);

	switch (image.Format) {
	case GL_LUMINANCE:
		source.pixelStore = ogl::Texture::Source::EPS_LUMINANCE;
		break;
	case GL_ALPHA:
		source.pixelStore = ogl::Texture::Source::EPS_LUMINANCE;
		break;
	case GL_LUMINANCE_ALPHA:
		source.pixelStore = ogl::Texture::Source::EPS_LUMINANCE_ALPHA;
		break;
	case GL_RGB:
		source.pixelStore = ogl::Texture::Source::EPS_RGB;
		break;
	case GL_RGBA:
		source.pixelStore = ogl::Texture::Source::EPS_RGBA;
		break;
	}
	
	u64 total_size = u64(image.BytesPerPixel) * u64(image.Width) * u64(image.Height);
	source.data = image.Data;

	texture.source(source);

	glfwFreeImage(&image);
}