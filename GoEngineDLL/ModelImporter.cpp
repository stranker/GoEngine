#include "ModelImporter.h"
#include "MeshInstance.h"
#include "SpatialMaterial.h"

MeshData::MeshData(vector<Vector3> _position_data, vector<Vector3> _normal_data, vector<Vector2> _texCoord_data, vector<unsigned int> _indices, vector<Texture> _textures, ADSSpatialMaterial _adsMaterial){
    position_data = _position_data;
    normal_data = _normal_data;
    texCoord_data = _texCoord_data;
    indices = _indices;
    textures = _textures;
    adsMaterial = _adsMaterial;
    CreateVertexArrayID();
    BindVertexArray();
    CreateVertexData(&position_data[0], position_data.size() * sizeof(Vector3), 3, Renderer::ARRAY_BUFFER, 0);
    if (!normal_data.empty()){
        CreateVertexData(&normal_data[0], normal_data.size() * sizeof(Vector3), 3, Renderer::ARRAY_BUFFER, 1);
    }
    if (!texCoord_data.empty()){
        CreateVertexData(&texCoord_data[0], texCoord_data.size() * sizeof(Vector2), 2, Renderer::ARRAY_BUFFER, 2);
    }
    CreateVertexData(&indices[0], indices.size() * sizeof(unsigned int), 1, Renderer::ELEMENT_BUFFER, -1);
    BindVertexObjects();
}

void MeshData::Draw(Transform& transform, Renderer::Primitive primitive) {
    BindVertexArray();
    if (&adsMaterial){
        adsMaterial.Use();
        // Vertex properties
        adsMaterial.SetMat4("model", transform.GetTransform());
        adsMaterial.SetMat4("view", Renderer::GetSingleton()->GetCamera()->GetView());
        adsMaterial.SetMat4("projection", Renderer::GetSingleton()->GetCamera()->GetProjection());
        for (unsigned int i = 0; i < textures.size(); i++) {
            string name = textures[i].GetName();
            adsMaterial.SetBool("material.hasTexture", true);
            adsMaterial.SetTexture("material." + name, textures[i].GetTextureID(), i);
        }
    }
    Renderer::GetSingleton()->Draw(primitive, indices.size(), true);
    adsMaterial.ResetTextureActive();
}

void MeshData::Destroy() {
    Renderer::GetSingleton()->DestroyVertexData(GetVectorVertexData());
}


void ModelImporter::ProcessScene(Mesh& meshInstance, string const& path) {
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs );
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){ // if is Not Zero
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    // retrieve the directory path of the filepath
    string directory = path.substr(0, path.find_last_of('/'));
    meshInstance.SetDirectory(directory);
    // process ASSIMP's root node recursively
    ProcessNode(meshInstance, scene->mRootNode, scene);
}

void ModelImporter::ProcessNode(Mesh& meshInstance, aiNode* node, const aiScene* scene) {
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(meshInstance, mesh, scene);
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(meshInstance, node->mChildren[i], scene);
    }
}

void ModelImporter::ProcessMesh(Mesh& meshInstance, aiMesh* mesh, const aiScene* scene) {
    // data to fill
    vector<Vector3> position_data;
    vector<Vector3> normal_data;
    vector<Vector2> texCoord_data;
    vector<unsigned int> indices;
    vector<Texture> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        position_data.push_back(Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
        if (mesh->HasNormals()) {
            normal_data.push_back(Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
        }
        if (mesh->mTextureCoords[0]) {
            texCoord_data.push_back(Vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
        }
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN
    // 1. diffuse maps
    vector<Texture> diffuseMaps = LoadMaterialTextures(meshInstance, material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<Texture> specularMaps = LoadMaterialTextures(meshInstance, material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    vector<Texture> normalMaps = LoadMaterialTextures(meshInstance, material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    vector<Texture> heightMaps = LoadMaterialTextures(meshInstance, material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    // ADS Material

    ADSSpatialMaterial adsMaterial = ResourceManager::LoadADSSpatialMaterial(
        "Shaders/SpatialMaterial.vs","Shaders/ADSSpatialMaterial.fs",string(material->GetName().C_Str()));
    aiColor3D color(1.0f, 1.0f, 1.0f);
    float shininess;
    if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, color)){
        adsMaterial.SetAmbient(Vector3(color.r, color.g, color.b));
    }
    if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, color)) {
        adsMaterial.SetSpecular(Vector3(color.r, color.g, color.b));
    }
    if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, color)) {
        adsMaterial.SetDiffuse(Vector3(color.r, color.g, color.b));
    }
    if (aiReturn_SUCCESS == material->Get(AI_MATKEY_SHININESS, shininess)) {
        adsMaterial.SetShininess(shininess);
    }
    // return a mesh object created from the extracted mesh data
    meshInstance.AddMesh(MeshData(position_data, normal_data, texCoord_data, indices, textures, adsMaterial));
}

vector<Texture> ModelImporter::LoadMaterialTextures(Mesh& meshInstance, aiMaterial* mat, aiTextureType type, string typeName) {
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        string filePath = meshInstance.GetDirectory() + "/" + string(str.C_Str());
        bool skip = false;
        for (unsigned int j = 0; j < meshInstance.GetTexturesLoaded().size(); j++)
        {
            if (std::strcmp(meshInstance.GetTexturesLoaded()[j].GetPath().c_str(), filePath.c_str()) == 0)
            {
                textures.push_back(meshInstance.GetTexturesLoaded()[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if texture hasn't been loaded already, load it
            Texture texture = ResourceManager::LoadTexture(filePath, filePath);
            if (texture.IsValid()){
                texture.SetName(typeName);
                textures.push_back(texture);
                meshInstance.AddTexture(texture); // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
    }
    return textures;
}

Mesh ModelImporter::LoadModel(string const& path) {
    Mesh mesh;
    ProcessScene(mesh, path);
    return mesh;
}
