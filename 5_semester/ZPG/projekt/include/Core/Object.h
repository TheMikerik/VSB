#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Core/ObjectModel.h"
#include "Core/Texture.h"
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>


class Object {
public:
    explicit Object(const std::string& path);
    ~Object();

    void loadModel(const std::string& path);

    void render(const std::shared_ptr<ShaderProgram>& shader, 
                const glm::mat4& view, 
                const glm::mat4& projection, 
                const glm::mat4& modelMatrix) const;

private:
    std::shared_ptr<ObjectModel> processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, 
                                                               aiTextureType type, 
                                                               const std::string& typeName);

    std::vector<std::shared_ptr<ObjectModel>> meshes;
    std::string directory;
};