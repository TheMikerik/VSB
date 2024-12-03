#pragma once

#include <memory>
#include "Core/Model3D.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Transformation.h"
#include "Core/Material.h"
#include "Core/Texture.h"

class Drawable3DObject {
public:
    Drawable3DObject(std::shared_ptr<Model3D> model,
                     std::shared_ptr<ShaderProgram> shaderProgram,
                     const Transformation& transformation = Transformation(),
                     const Material& material = Material(),
                     std::shared_ptr<Texture> texture = nullptr);

    Drawable3DObject(std::shared_ptr<Model3D> model,
                     std::shared_ptr<ShaderProgram> shaderProgram,
                     const Transformation& transformation = Transformation(),
                     std::shared_ptr<Texture> texture = nullptr);

    void render(const glm::mat4& view, const glm::mat4& projection) const;

    void setShader(std::shared_ptr<ShaderProgram> shd);
    void setTransformation(const Transformation& trans);
    Transformation& getTransformation();

    void setMaterial(const Material& mat);
    const Material& getMaterial() const;

    void setTexture(std::shared_ptr<Texture> tex);
    std::shared_ptr<Texture> getTexture() const;

private:
    std::shared_ptr<Model3D> model;
    std::shared_ptr<ShaderProgram> shaderProgram;
    Transformation transformation;
    Material material;
    std::shared_ptr<Texture> texture; 
};