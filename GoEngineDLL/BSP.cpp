#include "BSP.h"
#include "Primitive.h"

vector<Primitive*> BSP::partitionPlanes;
vector<Node*> BSP::nodesToDraw;

void BSP::DrawBSPTree(Node* parentNode, Vector3 cameraPosition) {
    if (!parentNode->Is3DNode()) {
        for (Node* child : parentNode->GetChildrens()) {
            DrawBSPTree(child, cameraPosition);
        }
        return;
    }
    Node3D* node = (Node3D*)parentNode;
    int countIn = 0;
    for (Primitive* primitive : partitionPlanes) {
        Plane partitionPlane = primitive->GetPlane();
        Plane::Halfspace cameraRet = partitionPlane.ClassifyPoint2(cameraPosition);
        BSPRelation nodeRet = BSP::GetRelation(partitionPlane, node->GetGlobalBBox());
        switch (cameraRet) {
        case Plane::NEGATIVE:
            if (nodeRet != BSPRelation::FRONT) {
                countIn++;
            }
            break;
        case Plane::ON_PLANE:
            countIn++;
            break;
        case Plane::POSITIVE:
            if (nodeRet != BSPRelation::BACK) {
                countIn++;
            }
            break;
        }
    }
    if (countIn == partitionPlanes.size()) {
        node->SetBSPEnabled(true);
        for (Node* childNode : node->GetChildrens()) {
            DrawBSPTree(childNode, cameraPosition);
        }
    }
    else {
        node->SetBSPEnabled(IsBSPMesh(node->GetName()));
    }
}

void BSP::AddPartitionPlane(Primitive* primitive) {
    partitionPlanes.push_back(primitive);
}

void BSP::RemovePartitionPlane(Primitive* primitive) {
    vector<Primitive*>::iterator it;
    for (it = partitionPlanes.begin(); it != partitionPlanes.end(); it++) {
        Primitive* prim = *it;
        if (prim == primitive) {
            partitionPlanes.erase(it);
            return;
        }
    }
}


bool BSP::HasPartitionPlanes() {
    return !partitionPlanes.empty();
}

bool BSP::IsBSPMesh(const string& name) {
    return name.find("BSPPlane", 0) >= 0 && name.find("BSPPlane", 0) <= 254;
}

BSPRelation BSP::GetRelation(Plane plane, const BoundingBox& bbox) {
    int front = 0, back = 0, coincident = 0;
    for (size_t i = 0; i < bbox.corners.size(); i++) {
        Plane::Halfspace result = plane.ClassifyPoint2(bbox.corners[i]);
        switch (result) {
        case Plane::NEGATIVE:
            back++;
            break;
        case Plane::ON_PLANE:
            coincident++;
            break;
        case Plane::POSITIVE:
            front++;
            break;
        default:
            break;
        }
    }
    BSPRelation relation = BSPRelation::COPLANAR;
    if (front != 0 && back != 0) {
        relation = BSPRelation::SPLIT;
    }
    else if (front == bbox.corners.size() && back == 0) {
        relation = BSPRelation::FRONT;
    }
    else if (back == bbox.corners.size() && front == 0) {
        relation = BSPRelation::BACK;
    }
    else if (coincident == bbox.corners.size()) {
        relation = BSPRelation::COPLANAR;
    }
    return relation;
}