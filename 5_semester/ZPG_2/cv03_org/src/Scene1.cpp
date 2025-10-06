#include "Scene1.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Transformation.h"
#include "../models/triangle.h"
#include <vector>
#include <memory>

Scene1::Scene1() {
    createTriangle();
}

void Scene1::createTriangle() {
    std::vector<float> triangleVertices(std::begin(triangle), std::end(triangle));
    
    auto triangleModel = std::make_shared<Model>(triangleVertices);

    auto shaderProgram = std::make_shared<ShaderProgram>(
        "shaders/vertex_shader.glsl", 
        "shaders/fragment_shader.glsl"
    );

    DrawableObject triangle(triangleModel, shaderProgram);
    
    addDrawable(triangle);
}