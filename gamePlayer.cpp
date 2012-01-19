#include "gamePlayer.h"

#include "IResourceManager.h"
#include "Mesh.h"
#include "oglShader.h"

#include "Angle2d.h"

using namespace game;

Player::TailGeom::TailGeom(float radius, float length, u32 spirit_r, u32 spirit_h)
	: _drawed(false), _radius(radius), _length(length), _radiusSpirit(spirit_r), _heightSpirit(spirit_h)
{
	_joints.resize(spirit_h, float3d(0.0f, 0.0f, 1.0f));

	for (u32 i = 0; i < spirit_r; ++i) {
		f32 theta = float(i) / float(spirit_r) * Angle2d::PI * 2.0f;
		_cos.push_back(std::cos(theta));
		_sin.push_back(std::sin(theta));
	}

	// push verts
	for (u32 j = 0; j < spirit_h; ++j) {
		f32 level = f32(j) / f32(spirit_h);
		f32 z = level * length;
		f32 r = _levelToRadius(level);
		for (u32 i = 0; i < spirit_r; ++i) {
			_verts.push_back(float3d(r * _cos[i], r * _sin[i], z));
		}
	}
	_verts.push_back(float3d(0.0f, 0.0f, length));

	// push indices
	for (u32 i = 0; i < spirit_h - 1; ++i) {
		for (u32 j = 0; j < spirit_r; ++j) {
			_indices.push_back(i * spirit_r + j);
			_indices.push_back(i * spirit_r + (j + 1) % spirit_r);
			_indices.push_back((i + 1) * spirit_r + j);
			
			_indices.push_back((i + 1) * spirit_r + j);
			_indices.push_back(i * spirit_r + (j + 1) % spirit_r);
			_indices.push_back((i + 1) * spirit_r + (j + 1) % spirit_r);
		}
	}

	u32 last_index = _verts.size() - 1;
	u32 offset = last_index - spirit_r;
	for (u32 i = 0; i < spirit_r; ++i) {
		_indices.push_back(offset + i);
		_indices.push_back(offset + (i + 1) % spirit_r);
		_indices.push_back(last_index);
	}

	// create norms
	_norms.resize(_verts.size());
	_updateNormals();
}

float Player::TailGeom::_levelToRadius(float level) const {
	return _radius * (level < 0.5f? 1.0f : 1.5f - level);
}

void Player::TailGeom::_updateNormals() {
	for (u32 i = 0; i < _indices.size(); i += 3) {
		u32 i0 = _indices[i];
		u32 i1 = _indices[i+1];
		u32 i2 = _indices[i+2];

		float3d n = (_verts[i1] - _verts[i0]).crossProduct(_verts[i2] - _verts[i0]);
		_norms[i0] += n;
		_norms[i1] += n;
		_norms[i2] += n;
	}

	foreach (float3d& norm, _norms) {
		norm.normalize();
	}
}

void Player::TailGeom::update(f32 t, const float3d& dir) {
	_drawed = false;

	// update joints
	for (u32 i = _joints.size() - 1; 0 < i; --i) {
		_joints[i] += 60.0f * (_joints[i - 1] - _joints[i]) * t;
		_joints[i].normalize();
	}
	_joints[0] = dir;

	// update verts
	float3d p;
	f32 part_len = _length / f32(_heightSpirit);
	for (u32 j = 0; j < _heightSpirit; ++j) {
		f32 level = f32(j) / f32(_heightSpirit);
		f32 r = _levelToRadius(level);
		for (u32 i = 0; i < _radiusSpirit; ++i) {
			_verts[i + _radiusSpirit * j] = p + float3d(r * _cos[i], r * _sin[i], 0.0f);
		}
		p += _joints[j] * part_len;
	}
	_verts[_verts.size() - 1] = p;
}

void Player::TailGeom::draw() {
	if (!_drawed) {
		//_updateNormals();
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, _verts.data());
	glNormalPointer(GL_FLOAT, 0, _norms.data());
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, _indices.data());
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	_drawed = true;
}

Player::Player(core::shared_ptr<rsc::IResourceManager> rm)
	:_tail(0.13f, 3.6f, 12, 20)
{
	_mesh = rm->getMesh("/Users/yosuke/Projects/Birth/data/spermatozoa.obj");

	_material.setAmbientColor(Color(0x111111FF));
	_material.setDiffuseColor(Color(0xFFFFFFFF));

	ogl::Shader vert_shader(ogl::Shader::ET_VERTEX);
	ogl::Shader frag_shader(ogl::Shader::ET_FRAGMENT);

	vert_shader.source(
		"void main(void) {"
		"	vec3 position = vec3(gl_ModelViewMatrix * gl_Vertex);"
		"	vec3 normal = gl_NormalMatrix * gl_Normal;"
		"	vec3 lightVec = gl_LightSource[0].position.xyz - position;"
		"	float dis = length(lightVec);"
		"	lightVec = normalize(lightVec);"
		"	float attenuation = 1.0 / (gl_LightSource[0].constantAttenuation +"
		"	gl_LightSource[0].linearAttenuation * dis +"
		"	gl_LightSource[0].quadraticAttenuation * dis * dis);"
		"	float diffuse = dot(lightVec, normal);"
		"	gl_FrontColor = gl_FrontLightProduct[0].ambient;"
		"	if (diffuse > 0.0) {"
		"		diffuse = pow(clamp(1.0 - diffuse, 0.0, 1.0), 2);"
		"		gl_FrontColor += gl_FrontLightProduct[0].diffuse * diffuse * attenuation;"
		"	}"
		"	gl_Position = gl_ProjectionMatrix * vec4(position, 1.0);"
		"}"
	);
	frag_shader.source(
		"void main(void) {"
		"	gl_FragColor = gl_Color;"
		"}"
	);

	vert_shader.compile();
	frag_shader.compile();
	_program.attach(vert_shader);
	_program.attach(frag_shader);
	_program.link();
}

float3d Player::getPosition() const {
	return _position;
}

void Player::update(float t) {
	_theta += Angle2d::PI * 5.5f * t;
	float3d dir = float3d(0.0f, 0.2f * _theta.sin(), 1.0f);
	dir.normalize();
	_tail.update(t, dir);
}

void Player::render() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_NORMALIZE);

	_material.bind();
	_program.use();
	_mesh->draw();
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 2.1f);
		_tail.draw();
	glPopMatrix();
	_program.unuse();
	_material.unbind();

	glDisable(GL_CULL_FACE); 
	glDisable(GL_NORMALIZE);
}