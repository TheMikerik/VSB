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


class Model3D {
public:
    explicit Model3D(const std::string& path);
    ~Model3D();

    void loadModel(const std::string& path);

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