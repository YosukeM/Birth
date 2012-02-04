#include "gameMitochondria.h"

#include "rscIManager.h"
#include "rscTexture.h"
#include "gamePlayer.h"
#include "gameStatus.h"

#include <GL/glfw.h>

using namespace game;

const float Mitochondria::RADIUS = 0.9f;

Mitochondria::Mitochondria(
	core::shared_ptr<rsc::IManager> rm,
	core::shared_ptr<Player> player,
	core::shared_ptr<Status> status
) : _player(player), _status(status), _isPickedUp(false)
{
	_texture = rm->getTexture("mitochondria.tga");
}

void Mitochondria::update(float) {
	if (_isPickedUp) return;
	if ((_player->getPosition() - _position).getLengthSQ() < std::pow(RADIUS + game::Player::RADIUS, 2)) {
		_isPickedUp = true;
		_status->increaseEnergyNum();
	}
}

void Mitochondria::_drawEffect() {
	if (_isPickedUp) return;

	float v[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, v);

	const float sizeX = 0.4f;
	const float sizeY = 0.4f;

	glLoadIdentity();

	_texture->bind();
	
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

	_texture->unbind();
}