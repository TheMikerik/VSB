// Core/Model3D.cpp
#include "Core/Model3D.h"
#include "Shaders/ShaderProgram.h" // Include ShaderProgram for forward declaration
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>
#include <stb_image.h>

Model3D::Model3D(const std::string& path) {
    loadModel(path);
}

Model3D::~Model3D() {
    // Resources are managed by smart pointers
}

void Model3D::loadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, 
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" 
                  << importer.GetErrorString() 
                  << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model3D::processNode(aiNode* node, const aiScene* scene) {
    // Process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    // Then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

std::shared_ptr<Model3DModel> Model3D::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    // Process vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        // Positions
        vertex.Position = glm::vec3(mesh->mVertices[i].x, 
                                    mesh->mVertices[i].y, 
                                    mesh->mVertices[i].z);
        // Normals
        if (mesh->HasNormals())
            vertex.Normal = glm::vec3(mesh->mNormals[i].x, 
                                      mesh->mNormals[i].y, 
                                      mesh->mNormals[i].z);
        else
            vertex.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
        // Texture Coordinates
        if (mesh->mTextureCoords[0]) {
            vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, 
                                         mesh->mTextureCoords[0][i].y);
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // Ensure the face is a triangle
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Process material
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // Diffuse maps
        std::vector<std::shared_ptr<Texture>> diffuseMaps = 
            loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        // Specular maps
        std::vector<std::shared_ptr<Texture>> specularMaps = 
            loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        // Normal maps
        std::vector<std::shared_ptr<Texture>> normalMaps = 
            loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        // Height maps
        std::vector<std::shared_ptr<Texture>> heightMaps = 
            loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    }

    return std::make_shared<Model3DModel>(vertices, indices, textures);
}

std::vector<std::shared_ptr<Texture>> Model3D::loadMaterialTextures(aiMaterial* mat, 
                                                                   aiTextureType type, 
                                                                   const std::string& typeName) {
    std::vector<std::shared_ptr<Texture>> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string filename = std::string(str.C_Str());
        filename = directory + "/" + filename;
        textures.push_back(std::make_shared<Texture>(filename));
    }
    return textures;
}

void Model3D::render(const std::shared_ptr<ShaderProgram>& shader, 
                     const glm::mat4& view, 
                     const glm::mat4& projection, 
                     const glm::mat4& modelMatrix) const 
{
    if (!shader) {
        std::cerr << "Shader program not provided for Model3D." << std::endl;
        return;
    }

    shader->use();

    // Set transformation matrices
    shader->setMat4("viewMatrix", view);
    shader->setMat4("projectionMatrix", projection);
    shader->setMat4("modelMatrix", modelMatrix);

    // Render each mesh
    for (const auto& mesh : meshes) {
        mesh->render(shader);
    }

    glUseProgram(0);
}