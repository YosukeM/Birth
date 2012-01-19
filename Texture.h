#pragma once

#include "Resource.h"
#include "oglTexture.h"

namespace rsc {
	class Texture : public Resource {
	public:
		typedef ogl::Texture::EFilter EFilter;

	private:
		ogl::Texture _texture;
		bool _repeatX, _repeatY;
		EFilter _magFilter, _minFilter;

	public:

		Texture();
		~Texture();

		void bind();
		void unbind();

		void setRepeatX(bool);
		void setRepeatY(bool);

		void setMagFilter(EFilter);
		void setMinFilter(EFilter);

		Vector2d<u32> getSize() const;
		bool hasAlpha() const;

	protected:
		void _load(core::shared_ptr<fs::IFileReader>);
	};
}