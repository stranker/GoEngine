#pragma once
#include "Utils.h"

class Node;
class Primitive;

enum BSPRelation {
	FRONT    = 0,
	BACK     = 1,
	SPLIT    = 2,
	COPLANAR = 3
};


class ENGINEDLL_API BSP {
public:
	static vector<Primitive*> partitionPlanes;
	static vector<Node*> nodesToDraw;
	static void DrawBSPTree(Node* parentNode, Vector3 cameraPosition);
	static void AddPartitionPlane(Primitive* primitive);
	static void RemovePartitionPlane(Primitive* primitive);
	static bool HasPartitionPlanes();
	static bool IsBSPMesh(const string& name);
	static BSPRelation GetRelation(Plane plane, const BoundingBox& bbox);
};