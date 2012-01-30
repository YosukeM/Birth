#pragma once

#include "rscIManager.h"
#include "IFileFactory.h"

namespace rsc {
class SyncManager : public IManager
{
	typedef core::unordered_map<core::string, core::shared_ptr<Mesh> > MeshMapType;
	MeshMapType _meshMap;
	typedef core::unordered_map<core::string, core::shared_ptr<Texture> > TexMapType;
	TexMapType _texMap;
	typedef core::unordered_map<core::string, core::shared_ptr<Shader> > ShaderMapType;
	ShaderMapType _shaderMap;
	typedef core::unordered_map<core::string, core::shared_ptr<Program> > ProgramMapType;
	ProgramMapType _programMap;

	core::string _basePath;

	core::scoped_ptr<fs::IFileFactory> _fileFactory;
public:
	SyncManager();

	void setBasePath(const core::string&);

	core::shared_ptr<Mesh> getMesh(const core::string& id);
	core::shared_ptr<Texture> getTexture(const core::string& id);
	core::shared_ptr<Shader> getShader(const core::string& id);

	core::shared_ptr<Program> getProgram(const core::string& id);
};

}
