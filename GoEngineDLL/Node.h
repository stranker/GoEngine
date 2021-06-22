#pragma once
#include "ResourceManager.h"
#include "NodeManager.h"

class ENGINEDLL_API Node{
protected:
	string name;
	unsigned int nodeID = 0;
	vector<Node*> childrens;
	Node* parent = nullptr;
	void SetDefaultName(const string& _name);
	void GetNode(const string& nodeName, vector<Node*>& res);
	string className;
public:
	void SetName(const string& _name);
	string GetName() const;
	vector<Node*> GetChildrens();
	void AddChildren(Node* child);
	void RemoveChildren(Node* child);
	Node* GetNode(const string& nodeName);
	Node* GetParent() const;
	Node* GetChild(int childIndex) const;
	void PrintTree();
	void SetParent(Node* _parent);
	unsigned int GetNodeID() const;
	virtual void Ready();
	virtual void Draw();
	virtual void Update(float deltaTime);
	virtual void Destroy();
	virtual void ShowUI();
	virtual void HideUI();
	string GetClass() const;
	Node();
	Node(const string& _name);
	virtual ~Node();
};
