// Core/Model3D.h
#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Core/Model3DModel.h"
#include "Core/Texture.h"
#include "Shaders/ShaderProgram.h"
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

class Model3D {
public:
    // Constructors
    Model3D(const std::string& path,
            const std::shared_ptr<ShaderProgram>& externalShader = nullptr);
    ~Model3D();

    // Render the model
    void render(const glm::mat4& view, const glm::mat4& projection, const glm::mat4& modelMatrix);

private:
    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    std::shared_ptr<Model3DModel> processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);

    std::vector<std::shared_ptr<Model3DModel>> meshes;
    std::string directory;
    std::shared_ptr<ShaderProgram> shader;
};