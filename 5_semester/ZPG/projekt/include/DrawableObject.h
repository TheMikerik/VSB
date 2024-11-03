#pragma once

#include <memory>
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject {
public:
    DrawableObject(std::shared_ptr<Model> model,
                    std::shared_ptr<ShaderProgram> shaderProgram,
                    const Transformation& transformation = Transformation());

    void render() const;
    void setTransformation(const Transformation& trans);
    Transformation& getTransformation();
    void setShader(std::shared_ptr<ShaderProgram> shd);

private:
    std::shared_ptr<Model> model;
    std::shared_ptr<ShaderProgram> shaderProgram;
    Transformation transformation;
};