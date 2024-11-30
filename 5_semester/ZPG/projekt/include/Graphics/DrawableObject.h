#pragma once

#include <memory>
#include "Core/Model.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Transformation.h"
#include "Core/Material.h"
#include "Core/Texture.h"

class DrawableObject {
public:
    DrawableObject(std::shared_ptr<Model> model,
                  std::shared_ptr<ShaderProgram> shaderProgram,
                  const Transformation& transformation = Transformation(),
                  const Material& material = Material(),
                  std::shared_ptr<Texture> texture = nullptr);

    void render() const;

    void setShader(std::shared_ptr<ShaderProgram> shd);
    void setTransformation(const Transformation& trans);
    Transformation& getTransformation();

    void setMaterial(const Material& mat);
    const Material& getMaterial() const;

    void setTexture(std::shared_ptr<Texture> tex);
    std::shared_ptr<Texture> getTexture() const;

    glm::vec3 getPosition() const;

private:
    std::shared_ptr<Model> model;
    std::shared_ptr<ShaderProgram> shaderProgram;
    Transformation transformation;
    Material material;
    std::shared_ptr<Texture> texture; // Texture member
};