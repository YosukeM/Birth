#pragma once

namespace rsc {
	class Mesh;
	class Texture;

	class IResourceManager {
	public:
		IResourceManager() {}
		virtual ~IResourceManager() {}
		virtual core::shared_ptr<Mesh> getMesh(const core::string& id) = 0;
		virtual core::shared_ptr<Texture> getTexture(const core::string& id) = 0;
	};
}
