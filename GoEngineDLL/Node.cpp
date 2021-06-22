#include "Node.h"
#include "Renderer.h"

void Node::SetDefaultName(const string& _name) {
	name = _name + to_string(nodeID);
}

void Node::GetNode(const string& nodeName, vector<Node*>& res) {
	for (Node* child : childrens){
		if (child->GetName() == nodeName){
			res.push_back(child);
		}
		if (!res.empty()){
			return;
		}
		child->GetNode(nodeName, res);
	}
}

void Node::SetName(const string& _name) {
	name = _name;
}

string Node::GetName() const {
	return name;
}

vector<Node*> Node::GetChildrens() {
	return childrens;
}

void Node::AddChildren(Node* child) {
	if (child->parent) {
		Node* p = (Node*)child->parent;
		p->RemoveChildren(child);
	}
	childrens.push_back(child);
	child->SetParent(this);
}

void Node::RemoveChildren(Node* _child) {
	for (size_t i = 0; i < childrens.size(); i++) {
		if (childrens[i]->GetNodeID() == _child->GetNodeID()) {
			childrens.erase(childrens.begin() + i);
			return;
		}
	}
}

Node* Node::GetNode(const string& nodeName) {
	vector<Node*> vecNode;
	GetNode(nodeName, vecNode);
	Node* current = nullptr;
	if (!vecNode.empty()){
		current = vecNode.at(0);
	}
	return current;
}

Node* Node::GetParent() const {
	return parent;
}

Node* Node::GetChild(int childIndex) const {
	if (childIndex < 0 || childIndex > childrens.size()){
		return nullptr;
	}
	return childrens[childIndex];
}

void Node::PrintTree() {
	cout << name << endl;
	for (Node* child : childrens) {
		child->PrintTree();
	}
}

void Node::SetParent(Node* _parent) {
	parent = _parent;
}

bool Node::IsUILocked() const {
	return uiLocked;
}

unsigned int Node::GetNodeID() const {
	return nodeID;
}

void Node::Ready() {
	for (Node* child : childrens) {
		child->Ready();
	}
}

void Node::Draw() {
	for (Node* child : childrens) {
		child->Draw();
	}
}

void Node::Update(float deltaTime) {
	for (Node* child : childrens) {
		child->Update(deltaTime);
	}
}

void Node::Destroy() {
	for (Node* child : childrens) {
		child->Destroy();
	}
	delete this;
}

void Node::ShowUI() {
	UILayer::ShowNodeInfo(this);
}

void Node::HideUI() {
}

string Node::GetClass() const {
	return className;
}

Node::Node() {
	nodeID = NodeManager::CreateNode(this);
	className = "Node";
}

Node::Node(const string& _name) {
	name = _name;
}

Node::~Node() {
	NodeManager::RemoveNode(this);
}