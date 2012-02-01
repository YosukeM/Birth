#include "guiText.h"

#include <GL/glfw.h>

using namespace gui;

Text::Text(core::shared_ptr<rsc::Texture> texture, uint2d split, const core::unordered_map<char, uint2d>& map)
	: _texture(texture), _split((f32)split.x, (f32)split.y), _map(map), _hasCached(false)
{

}

void Text::setText(const core::string& str) {
	_hasCached = false;
	_text = str;
}

void Text::_drawPositionally(const float2d& p) {
	float2d pos = p;
	float2d tex = _texture->getRBTexCoord();
	float2d texsize(tex.x / _split.x, tex.y / _split.y);
	f32 char_width = _texture->getSize().x / _split.x;
	f32 line_height = _texture->getSize().y / _split.y;

	_texture->bind();
	foreach (char c, _text) {
		if (c == '\n') {
			pos.x = p.x;
			pos.y += line_height;
			continue;
		}
		uint2d lt = _map[c];
		float2d texpos(tex.x * (f32)lt.x / (f32)_texture->getSize().x, tex.y * (f32)lt.y / (f32)_texture->getSize().y);
		glBegin(GL_QUADS);
			glTexCoord2f(texpos.x, tex.y - texpos.y);
			glVertex2f(pos.x, pos.y);
			glTexCoord2f(texpos.x + texsize.x, tex.y - texpos.y);
			glVertex2f(pos.x + char_width, pos.y);
			glTexCoord2f(texpos.x + texsize.x, tex.y - (texpos.y + texsize.y) );
			glVertex2f(pos.x + char_width, pos.y + line_height);
			glTexCoord2f(texpos.x, tex.y - (texpos.y + texsize.y) );
			glVertex2f(pos.x, pos.y + line_height);
		glEnd();
		pos.x += char_width;
	}
	_texture->unbind();
}

float2d Text::getSize() const {
	if (_hasCached) return _cachedSize;

	u32 max_w = 0;
	u32 w = 0, h = 1;
	foreach (char c, _text) {
		if (c == '\n') {
			if (w > max_w) max_w = w;
			w = 0;
			++h;
		} else {
			++w;
		}
	}
	if (w > max_w) max_w = w;
	
	f32 char_width = _texture->getSize().x / _split.x;
	f32 line_height = _texture->getSize().y / _split.y;
	_cachedSize = float2d(max_w * char_width, h * line_height);
	_hasCached = true;
	return _cachedSize;
}