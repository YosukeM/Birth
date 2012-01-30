#include "gameScene.h"

#include "gamePlayer.h"
#include "gameSubordinate.h"

using namespace game;

Scene::Scene(core::shared_ptr<rsc::IManager> rm)
	: _light(true),
	_drawState(EDS_SOLID),
	_count(0.0f),
	_countLimit(10.0f)
{
	_fadein(2.0f);

	_light.setAmbientColor(Color(0xFFFFFFFF));
	_light.setDiffuseColor(Color(0xFFFFFFFF));
	_light.setSpecularColor(Color(0xFFFFFFFF));

	_cameraPosition = float3d(3.0f, 1.0f, 0.0f);
	_camera.setFar(500.0f);
	_camera.setFov(Angle2d::PI / 6.0f);

	_player = core::make_shared<Player>(rm);
	_player->setPosition(float3d(0.0f, 0.0f, 100.0f));

	_nodeList.push_back(_player);
}

void Scene::_update(f32 t) {
	_count += t;

	foreach (core::shared_ptr<game::Node>& node, _nodeList) {
		node->update(t);
	}

	if (_count > _countLimit - 2.0f && _getFadeState() == Sequence::EFS_NONE) {
		_fadeout(2.0f);
	}
}

void Scene::_draw() {
	if (_drawState == EDS_FADE) return;

	_camera.setPosition(_cameraPosition);
	_camera.setLookAt(_player->getPosition());
	_camera.setMatrix();

	glMatrixMode(GL_MODELVIEW);

	_light.setPosition(_cameraPosition);
	_light.setSpotDirection(float3d() - _cameraPosition);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	_light.attach(GL_LIGHT0);

	foreach (core::shared_ptr<game::Node>& node, _nodeList) {
		node->draw( (game::Node::EDrawState)_drawState );
	}

	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);
}

void Scene::setDrawState(EDrawState ds) {
	_drawState = ds;
}

void Scene::draw() {
	if (_drawState == EDS_FADE) {
		Sequence::draw();
	} else {
		_draw();
	}
}

core::shared_ptr<Sequence> Scene::_getNextSequence() {
	return core::shared_ptr<Sequence>();
}
