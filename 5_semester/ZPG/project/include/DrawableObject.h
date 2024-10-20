// DrawableObject.h
#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include <memory>
#include <glm/glm.hpp>

class DrawableObject {
public:
    DrawableObject(std::shared_ptr<Model> model,
                std::shared_ptr<ShaderProgram> shaderProgram,
                const Transformation& transformation = Transformation());

    void render() const;

    void setTransformation(const Transformation& trans);
    Transformation& getTransformation();

private:
    std::shared_ptr<Model> model;
    std::shared_ptr<ShaderProgram> shaderProgram;
    Transformation transformation;
};

#endif // DRAWABLEOBJECT_H