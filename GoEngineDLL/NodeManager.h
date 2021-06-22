#pragma once
#include "Utils.h"

class Node;

class ENGINEDLL_API NodeManager {
private:
	static vector<Node*> nodes;
public:
	static unsigned int CreateNode(Node* node);
	static void RemoveNode(Node* node);
	static void Clear();
};

