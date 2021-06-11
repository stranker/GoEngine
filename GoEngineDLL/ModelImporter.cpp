#include "ModelImporter.h"
#include "MeshInstance.h"
#include "SpatialMaterial.h"

string ModelImporter::tempOutDirectory;
vector<Texture*> ModelImporter::tempTextures;

Node3D* ModelImporter::ProcessScene(string const& path) {
    Node3D* rootNode = new Node3D("rootModel");
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs );
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){ // if is Not Zero
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return rootNode;
    }
    // retrieve the directory path of the filepath
    tempOutDirectory = path.substr(0, path.find_last_of('/'));
    // process ASSIMP's root node recursively
    ProcessNode(rootNode, scene->mRootNode, scene);
    tempOutDirectory.clear();
    return rootNode;
}

void ModelImporter::ProcessNode(Node3D* parentNode, aiNode* node, const aiScene* scene) {
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        MeshInstance* meshInstance = new MeshInstance();
        MeshData* meshData = new MeshData();
        *meshData = ProcessMesh(mesh, scene);
        meshInstance->SetName(mesh->mName.C_Str());
        meshInstance->SetMesh(meshData);
        cout << meshInstance->GetName() << endl;
        parentNode->AddChildren((Node*)meshInstance);
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        Node3D* childNode = new Node3D();
        childNode->SetName(node->mChildren[i]->mName.C_Str());
        cout << childNode->GetName() << endl;
        parentNode->AddChildren((Node*)childNode);
        ProcessNode(childNode, node->mChildren[i], scene);
    }
}

MeshData ModelImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    // data to fill
    MeshData meshData;
    meshData.SetName(mesh->mName.C_Str());
    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        meshData.position_data.push_back(Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
        if (mesh->HasNormals()) {
            meshData.normal_data.push_back(Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
        }
        if (mesh->mTextureCoords[0]) {
            meshData.texCoord_data.push_back(Vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
        }
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            meshData.indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    ADSSpatialMaterial* adsMaterial = ResourceManager::LoadADSSpatialMaterial(
        "Shaders/SpatialMaterial.vs", "Shaders/ADSSpatialMaterial.fs", string(material->GetName().C_Str()));

    aiColor3D color(1.0f, 1.0f, 1.0f);
    float shininess;
    if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, color)) {
        adsMaterial->SetAmbient(Vector3(color.r, color.g, color.b));
    }
    if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, color)) {
        adsMaterial->SetSpecular(Vector3(color.r, color.g, color.b));
    }
    if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, color)) {
        adsMaterial->SetDiffuse(Vector3(color.r, color.g, color.b));
    }
    if (aiReturn_SUCCESS == material->Get(AI_MATKEY_SHININESS, shininess)) {
        adsMaterial->SetShininess(shininess);
    }

    Texture* diffuseTexture = LoadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
    adsMaterial->SetDiffuseTexture(diffuseTexture);
    meshData.adsMaterial = adsMaterial;
    //textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    //// 2. specular maps
    //vector<Texture> specularMaps = LoadMaterialTextures(rootNode, material, aiTextureType_SPECULAR, "texture_specular");
    //textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    //// 3. normal maps
    //vector<Texture> normalMaps = LoadMaterialTextures(rootNode, material, aiTextureType_HEIGHT, "texture_normal");
    //textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    //// 4. height maps
    //vector<Texture> heightMaps = LoadMaterialTextures(rootNode, material, aiTextureType_AMBIENT, "texture_height");
    //textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    // return a mesh object created from the extracted mesh data
    return meshData;
}

Texture* ModelImporter::LoadMaterialTexture(aiMaterial* mat, aiTextureType type, string typeName) {
    aiString str;
    mat->GetTexture(type, 0, &str);
    string filePath = tempOutDirectory + "/" + string(str.C_Str());
    Texture* texture = ResourceManager::LoadTexture(filePath, str.C_Str());
    if (texture->IsValid()) {
        texture->SetName(typeName);
    }
    return texture;
}

Node3D* ModelImporter::LoadModel(string const& path) {
    Node3D* rootModel = ProcessScene(path);
    return rootModel;
}
