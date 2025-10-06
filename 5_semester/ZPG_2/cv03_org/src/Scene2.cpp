#include "Scene2.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Transformation.h"
#include "../models/sphere.h"
#include <vector>
#include <memory>

Scene2::Scene2() {
    createSpheres();
}

void Scene2::createSpheres() {
    std::vector<float> sphereVertices(std::begin(sphere), std::end(sphere));
    auto sphereModel = std::make_shared<Model>(sphereVertices);

    auto shaderProgram = std::make_shared<ShaderProgram>(
        "shaders/vertex_shader.glsl", 
        "shaders/fragment_shader.glsl"
    );

    Transformation transform1;
    transform1.translate(glm::vec3(2.0f, 0.0f, 0.0f));
    transform1.scale(glm::vec3(0.5f, 0.5f, 0.5f));
    DrawableObject sphere1(sphereModel, shaderProgram, transform1);
    addDrawable(sphere1);

    Transformation transform2;
    transform2.translate(glm::vec3(-2.0f, 0.0f, 0.0f));
    transform2.scale(glm::vec3(0.5f, 0.5f, 0.5f));
    DrawableObject sphere2(sphereModel, shaderProgram, transform2);
    addDrawable(sphere2);

    Transformation transform3;
    transform3.translate(glm::vec3(0.0f, 2.0f, 0.0f));
    transform3.scale(glm::vec3(0.5f, 0.5f, 0.5f));
    DrawableObject sphere3(sphereModel, shaderProgram, transform3);
    addDrawable(sphere3);

    Transformation transform4;
    transform4.translate(glm::vec3(0.0f, -2.0f, 0.0f));
    transform4.scale(glm::vec3(0.5f, 0.5f, 0.5f));
    DrawableObject sphere4(sphereModel, shaderProgram, transform4);
    addDrawable(sphere4);
}