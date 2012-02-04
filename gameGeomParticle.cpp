#include "gameGeomParticle.h"

#include "rscTexture.h"

#include "Random.h"
#include <GL/glfw.h>

using namespace game;
using namespace geom;

Emitter::Emitter(core::shared_ptr<rsc::Texture> texture, u32 max_num)
	: _texture(texture), _particles(max_num)
{

}

Emitter::~Emitter() {

}

void Emitter::update(f32 t) {
	foreach (auto& particle, _particles) {
		particle.position += particle.v * t;
		particle.life -= t;
	}
}

void Emitter::emit(u32 num, const float3d& v, const float3d& random, float life) {
	Particle p;
	p.life = life;
	for (u32 i = 0; i < num; ++i) {
		p.v = v;
		p.v.x += random.x * core::random::getFloat(-1.0f, 1.0f);
		p.v.y += random.y * core::random::getFloat(-1.0f, 1.0f);
		p.v.z += random.z * core::random::getFloat(-1.0f, 1.0f);
		_particles.push_back(p);
	}
}

void Emitter::draw(Color color) {
	float v[16];

	const float sizeX = 0.2f;
	const float sizeY = 0.2f;

	_texture->bind();

	float colorv[4];
	color.getAs4Values(colorv);

	foreach (auto& particle, _particles) {
		glPushMatrix();
			glTranslatef(particle.position.x, particle.position.y, particle.position.z);
			glGetFloatv(GL_MODELVIEW_MATRIX, v);
			glLoadIdentity();
			glColor4f(colorv[0], colorv[1], colorv[2], particle.life);
			glBegin(GL_POLYGON);
				glTexCoord2f(0, _texture->getRBTexCoord().y);
				glVertex3d( v[12]-sizeX, v[13]-sizeY, v[14]);//¶‰º
				glTexCoord2f(0, 0);
				glVertex3d( v[12]-sizeX, v[13]+sizeY, v[14]);//¶ã
				glTexCoord2f(_texture->getRBTexCoord().x, 0);
				glVertex3d( v[12]+sizeX, v[13]+sizeY, v[14]);//‰Eã
				glTexCoord2f(_texture->getRBTexCoord().x, _texture->getRBTexCoord().y);
				glVertex3d( v[12]+sizeX, v[13]-sizeY, v[14]);//‰E‰º
			glEnd();
		glPopMatrix();
	}

	_texture->unbind();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}