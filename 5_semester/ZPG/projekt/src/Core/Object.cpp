#include "Core/Object.h"
#include "Shaders/ShaderProgram.h" 
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>
#include <stb_image.h>

Object::Object(const std::string& path) {
    loadModel(path);
}

Object::~Object() {
    
}

void Object::loadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, 
        aiProcess_Triangulate);

    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];
        meshes.push_back(processMesh(mesh, scene));
    }
}

std::shared_ptr<ObjectModel> Object::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        
        vertex.Position = glm::vec3(mesh->mVertices[i].x, 
                                    mesh->mVertices[i].y, 
                                    mesh->mVertices[i].z);
        
        if (mesh->HasNormals())
            vertex.Normal = glm::vec3(mesh->mNormals[i].x, 
                                      mesh->mNormals[i].y, 
                                      mesh->mNormals[i].z);
        else
            vertex.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
        
        if (mesh->mTextureCoords[0]) {
            vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, 
                                         mesh->mTextureCoords[0][i].y);
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    return std::make_shared<ObjectModel>(vertices, indices, textures);
}

std::vector<std::shared_ptr<Texture>> Object::loadMaterialTextures(aiMaterial* mat, 
                                                                   aiTextureType type, 
                                                                   const std::string& typeName) {
    std::vector<std::shared_ptr<Texture>> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string filename = std::string(str.C_Str());
        textures.push_back(std::make_shared<Texture>(filename));
    }
    return textures;
}

void Object::render(const std::shared_ptr<ShaderProgram>& shader, 
                     const glm::mat4& view, 
                     const glm::mat4& projection, 
                     const glm::mat4& modelMatrix) const 
{
    if (!shader) {
        std::cerr << "Shader program not provided for Object." << std::endl;
        return;
    }

    shader->use();

    shader->setMat4("viewMatrix", view);
    shader->setMat4("projectionMatrix", projection);
    shader->setMat4("modelMatrix", modelMatrix);

    for (const auto& mesh : meshes) {
        mesh->render(shader);
    }

    glUseProgram(0);
}