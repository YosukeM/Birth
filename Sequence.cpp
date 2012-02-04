#include "Sequence.h"
#include <GL/glfw.h>
#ifdef _WIN32
	#include <GL/GLU.h>
#else
	#include <OpenGL/glu.h>
#endif

Sequence::Sequence()
	: _fadeTimer(0.0f),
	_fadeDuration(0.0f),
	_fadeColor(0x000000FF),
	_fadeState(EFS_NONE)
{
}

Sequence::~Sequence() {
}

core::shared_ptr<Sequence> Sequence::update(f32 delta_time) {
	switch (_fadeState) {
	case EFS_FADEIN:
		_fadeTimer += delta_time;
		if (_fadeTimer > _fadeDuration) {
			_fadeState = EFS_NONE;
		}
		break;
	case EFS_FADEOUT:
		_fadeTimer += delta_time;
		if (_fadeTimer > _fadeDuration) {
			return _getNextSequence();
		}
		break;
	case EFS_NONE:
		break;
	}

	_update(delta_time);

	return core::shared_ptr<Sequence>();
}


void Sequence::_drawFading(f32 fade_level) {
	if (fade_level < 0.0f) {
		fade_level = 0.0f;
	} else if (fade_level > 1.0f) {
		fade_level = 1.0f;
	}

	if (fade_level <= 0.0f) return;

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	glEnable(GL_BLEND);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	f32 color[4];
	_fadeColor.getAs4Values(color);
	fade_level = 1.0f - fade_level;
	glColor3f(
		(1.0f - color[0]) * fade_level,
		(1.0f - color[1]) * fade_level,
		(1.0f - color[2]) * fade_level
	);

	glBegin(GL_QUADS);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(1.0f, 0.0f);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(0.0f, 1.0f);
	glEnd();

	glDisable(GL_BLEND);
}

void Sequence::draw() {
	_draw();
	_drawFading(_getFadeLevel());
}

void Sequence::_fadein(f32 duration, const Color& color) {
	_fadeDuration = duration;
	_fadeTimer = 0.0f;
	_fadeColor = color;
	_fadeState = EFS_FADEIN;
}

void Sequence::_fadeout(f32 duration, const Color& color) {
	_fadeDuration = duration;
	_fadeTimer = 0.0f;
	_fadeColor = color;
	_fadeState = EFS_FADEOUT;
}

float Sequence::_getFadeLevel() const {
	float value = 0.0f;
	switch (_fadeState) {
	case EFS_FADEIN:
		value = 1.0f - _fadeTimer / _fadeDuration;
		break;
	case EFS_FADEOUT:
		value = _fadeTimer / _fadeDuration;
		break;
	}
	return value;
}

Sequence::EFadeState Sequence::_getFadeState() const {
	return _fadeState;
}
