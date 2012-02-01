#include "gameScene.h"

#include "gamePlayer.h"
#include "gameSubordinate.h"

#include "Random.h"

using namespace game;

Scene::Scene(core::shared_ptr<rsc::IManager> rm, float length)
	: _light(true),
	_drawState(EDS_SOLID),
	_count(0.0f),
	_countLimit(length)
{
	_fadein(2.0f);

	_light.setAmbientColor(Color(0xFFFFFFFF));
	_light.setDiffuseColor(Color(0xFFFFFFFF));
	_light.setSpecularColor(Color(0xFFFFFFFF));

	_camera.setFar(500.0f);
	_camera.setFov(Angle2d::PI / 6.0f);

	_player = core::make_shared<Player>(rm);
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

	_onUpdate(t);
}

void Scene::_draw() {
	if (_drawState == EDS_FADE) return;

	if (_drawState == EDS_SOLID) {
		_setupCamera();
	}
	_camera.setMatrix();

	glMatrixMode(GL_MODELVIEW);

	// _light.setPosition(_camera.getPosition());
	_light.setSpotDirection(_camera.getLookAt() - _camera.getPosition());

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

void Scene::setNextSequence(core::shared_ptr<Sequence> seq) {
	_nextSequence = seq;
}

core::shared_ptr<Sequence> Scene::_getNextSequence() {
	return _nextSequence;
}
