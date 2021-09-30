#pragma once
#include "Exports.h"
#include "Utils.h"
#include "TimeApi.h"

class ENGINEDLL_API Resource  {
protected:
	unsigned int resourceID = 0;
	string name;
	string path;
	void SetDefaultName(const string& _name);
public:
	void SetID(unsigned int id) { resourceID = id;};
	unsigned int GetID() const { return resourceID; };
	void SetName(string const& _name) { name = _name; };
	string GetName() const { return name; };
	string GetPath() const { return path; };
	Resource() { SetDefaultName("Resource"); };
	virtual ~Resource() {};
};
