#include "rscSyncManager.h"
#include "FileFactory.h"
#include "rscMesh.h"
#include "rscTexture.h"
#include "rscShader.h"
#include "rscProgram.h"

using namespace rsc;

SyncManager::SyncManager()
{
	_fileFactory.reset(new fs::FileFactory());
}

void SyncManager::setBasePath(const core::string& base_path) {
	_basePath = base_path;
}

core::shared_ptr<Mesh> SyncManager::getMesh(const core::string& id) {
	MeshMapType::iterator itr = _meshMap.find(id);
	if (itr == _meshMap.end()) {
		core::shared_ptr<Mesh> mesh = core::make_shared<Mesh>();
		_meshMap[id] = mesh;
		mesh->load(_fileFactory->createFileReader((_basePath + id).c_str()));
		return mesh;
	} else {
		return itr->second;
	}
}

core::shared_ptr<Texture> SyncManager::getTexture(const core::string& id) {
	TexMapType::iterator itr = _texMap.find(id);
	if (itr == _texMap.end()) {
		core::shared_ptr<Texture> texture = core::make_shared<Texture>();
		_texMap[id] = texture;
		texture->load(_fileFactory->createFileReader((_basePath + id).c_str()));
		return texture;
	} else {
		return itr->second;
	}
	return core::shared_ptr<Texture>();
}

core::shared_ptr<Shader> SyncManager::getShader(const core::string& id) {
	ShaderMapType::iterator itr = _shaderMap.find(id);
	rsc::Shader::EType type = Shader::EType::ET_FRAGMENT;
	if (id.find(".vert") != -1) {
		type = Shader::EType::ET_VERTEX;
	}
	if (itr == _shaderMap.end()) {
		core::shared_ptr<Shader> shader = core::make_shared<Shader>(type);
		_shaderMap[id] = shader;
		shader->load(_fileFactory->createFileReader((_basePath + id).c_str()));
		shader->compile();
		return shader;
	} else {
		return itr->second;
	}
}

core::shared_ptr<Program> SyncManager::getProgram(const core::string& id) {
	ProgramMapType::iterator itr = _programMap.find(id);
	if (itr == _programMap.end()) {
		core::shared_ptr<Program> program = core::make_shared<Program>();
		_programMap[id] = program;
		program->load(getShader(id + ".vert"), getShader(id + ".frag"));
		return program;
	} else {
		return itr->second;
	}
}