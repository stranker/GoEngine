#include "ModelImporter.h"
#include "Mesh.h"
#include "SpatialMaterial.h"

MeshData::MeshData(vector<Vector3> _position_data, vector<Vector3> _normal_data, vector<Vector2> _texCoord_data, vector<unsigned int> _indices, vector<TextureData> _textures) {
    position_data = _position_data;
    normal_data = _normal_data;
    texCoord_data = _texCoord_data;
    indices = _indices;
    textures = _textures;
}

void MeshData::Draw(unsigned int vao, SpatialMaterial& material, Renderer::Primitive primitive) {
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].name;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        material.SetTextureProperty(name + number, textures[i].textureId, i);
    }
    Renderer::GetSingleton()->Draw(vao, primitive, indices.size(), true);
    material.ResetTextureActive();
}


void ModelImporter::ProcessObject(Mesh& meshInstance, string const& path) {
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
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
    vector<TextureData> textures;

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
    vector<TextureData> diffuseMaps = LoadMaterialTextures(meshInstance, material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<TextureData> specularMaps = LoadMaterialTextures(meshInstance, material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    vector<TextureData> normalMaps = LoadMaterialTextures(meshInstance, material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    vector<TextureData> heightMaps = LoadMaterialTextures(meshInstance, material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    meshInstance.AddMesh(MeshData(position_data, normal_data, texCoord_data, indices, textures));
}

vector<TextureData> ModelImporter::LoadMaterialTextures(Mesh& meshInstance, aiMaterial* mat, aiTextureType type, string typeName) {
    vector<TextureData> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        string filePath = meshInstance.GetDirectory() + "/" + string(str.C_Str());
        bool skip = false;
        for (unsigned int j = 0; j < meshInstance.GetTexturesLoaded().size(); j++)
        {
            if (std::strcmp(meshInstance.GetTexturesLoaded()[j].path.c_str(), filePath.c_str()) == 0)
            {
                textures.push_back(meshInstance.GetTexturesLoaded()[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if texture hasn't been loaded already, load it
            TextureData texture = TextureImporter::LoadTexture(filePath.c_str());
            if (texture.isValid){
                texture.name = typeName;
                textures.push_back(texture);
                meshInstance.AddTexture(texture); // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
    }
    return textures;
}

Mesh ModelImporter::LoadModel(string const& path) {
    Mesh meshInstance;
    ProcessObject(meshInstance, path);
    meshInstance.SetupMesh();
    return meshInstance;
}
