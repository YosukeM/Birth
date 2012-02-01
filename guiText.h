#pragma once

#include "guiPositionalElement.h"
#include "rscTexture.h"

namespace gui {
	class Text : public PositionalElement {
		core::shared_ptr<rsc::Texture> _texture;
		core::string _text;
		core::unordered_map<char, uint2d> _map;
		float2d _split;
		mutable float2d _cachedSize;
		mutable bool _hasCached;
	protected:
		void _drawPositionally(const float2d&);
	public:
		Text(core::shared_ptr<rsc::Texture> texture, uint2d split, const core::unordered_map<char, uint2d>&);
		void setText(const core::string& );
		float2d getSize() const;
	};
}