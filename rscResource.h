#pragma once

namespace fs {
	class IFileReader;
}

namespace rsc {
class Resource
{
protected:
	bool _isLoaded;
	virtual void _load(core::shared_ptr<fs::IFileReader>) = 0;
public:
	Resource();
	virtual ~Resource();

	void load(core::shared_ptr<fs::IFileReader>);
	bool isLoaded() const;
};

}
