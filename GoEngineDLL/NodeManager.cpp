#include "NodeManager.h"
#include "Node.h"

vector<Node*> NodeManager::nodes;

unsigned int NodeManager::CreateNode(Node* node) {
	nodes.push_back(node);
	Profiler::totalObjects++;
	return nodes.size();
}

void NodeManager::RemoveNode(Node* node) {
	for (size_t i = 0; i < nodes.size(); i++){
		if (nodes[i]->GetNodeID() == node->GetNodeID()){
			nodes.erase(nodes.begin() + i);
			Profiler::totalObjects--;
			return;
		}
	}
}

void NodeManager::Clear() {
	nodes.clear();
}
