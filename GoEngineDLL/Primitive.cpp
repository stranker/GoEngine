#include "Primitive.h"

void Primitive::CreateBBox(float* data, size_t data_size) {
    vector<Vector3> dataPos;
    for (size_t i = 0; i < data_size; i++) {
        dataPos.push_back(Vector3(data[i * 3 + 0], data[i * 3 + 1], data[i * 3 + 2]));
    }
    CreateBBox(dataPos);
}

void Primitive::SetMaterial(SpatialMaterial* _spatialMaterial) {
	spatialMaterial = _spatialMaterial;
}

void Primitive::Draw() {
	Node3D::Draw();
}

//Plane Primitive::GetPlane() {
//    float d = globalTransform->GetFoward().Dot(globalTransform->GetPosition());
//    return Plane(globalTransform->GetFoward(), d);
//}

void Primitive::ShowUI() {
    Node3D::ShowUI();
    UILayer::ShowMaterial(spatialMaterial);
}

void Primitive::SetAsPartitionPlane(bool value) {
    isPartitionPlane = value;
    isBspPlane = true;
    if (isPartitionPlane) {
        BSP::AddPartitionPlane(this);
    }
    else {
        BSP::RemovePartitionPlane(this);
    }
}

void Primitive::CreateBBox(vector<Vector3> posData) {
    Vector3 minVtx = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);
    Vector3 maxVtx = Vector3(FLT_MIN, FLT_MIN, FLT_MIN);
    for (size_t i = 0; i < posData.size(); i++) {
        minVtx.x = min(minVtx.x, posData[i].x);    // Find smallest x value in model
        minVtx.y = min(minVtx.y, posData[i].y);    // Find smallest y value in model
        minVtx.z = min(minVtx.z, posData[i].z);    // Find smallest z value in model

        //Get the largest vertex 
        maxVtx.x = max(maxVtx.x, posData[i].x);    // Find largest x value in model
        maxVtx.y = max(maxVtx.y, posData[i].y);    // Find largest y value in model
        maxVtx.z = max(maxVtx.z, posData[i].z);    // Find largest z value in model
    }
    boundingBox = BoundingBox(minVtx, maxVtx);
    globalBoundingBox = boundingBox;
}

void Primitive::CreateBBox(vector<Vector3> posData, float radius) {
    Vector3 boundingBoxMin = Vector3().One() * -radius;
    Vector3 boundingBoxMax = Vector3().One() * radius;
    boundingBox = BoundingBox(boundingBoxMin, boundingBoxMax);
    globalBoundingBox = boundingBox;
}

Primitive::Primitive() {
    defaultMaterial = ResourceManager::LoadSpatialMaterial("Shaders/SpatialMaterial.vs", "Shaders/SpatialMaterial.fs", "defaultMaterial");
    spatialMaterial = ResourceManager::LoadSpatialMaterial("Shaders/SpatialMaterial.vs", "Shaders/SpatialMaterial.fs", "spatialMaterial");
    spatialMaterial->AddMat4("model", globalTransform->GetTransform());
}
