#pragma once
#include "Exports.h"
#include "Utils.h"

class ENGINEDLL_API Resource  {
protected:
	unsigned int resourceID;
	string name;
private:
	unsigned int GetID() const;
	string const& GetName();
public:
	Resource() {};
	virtual ~Resource() {};
};
