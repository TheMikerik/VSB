#include "Scene1.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Transformation/Transformation.h"
#include <vector>
#include <memory>

Scene1::Scene1() {
    createTriangle();
}

void Scene1::createTriangle() {
    std::vector<float> triangleVertices = {
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    auto triangleModel = std::make_shared<Model>(triangleVertices);

    auto shaderProgram = std::make_shared<ShaderProgram>(
        "shaders/vertex_shader.glsl", 
        "shaders/fragment_shader.glsl"
    );

    Transformation transformation;

    DrawableObject triangle(triangleModel, shaderProgram, transformation);

    addDrawable(triangle);
}