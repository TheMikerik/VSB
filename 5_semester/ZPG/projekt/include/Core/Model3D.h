// Core/Model3D.h
#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Core/Model3DModel.h"
#include "Core/Texture.h"
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

class ShaderProgram; // Forward declaration to avoid circular dependencies

class Model3D {
public:
    // Constructors
    explicit Model3D(const std::string& path);
    ~Model3D();

    // Load the model and process it
    void loadModel(const std::string& path);

    // Render the model with a given shader and transformation matrices
    void render(const std::shared_ptr<ShaderProgram>& shader, 
                const glm::mat4& view, 
                const glm::mat4& projection, 
                const glm::mat4& modelMatrix) const;

private:
    void processNode(aiNode* node, const aiScene* scene);
    std::shared_ptr<Model3DModel> processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, 
                                                               aiTextureType type, 
                                                               const std::string& typeName);

    std::vector<std::shared_ptr<Model3DModel>> meshes;
    std::string directory;
};