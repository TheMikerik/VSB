// Scene2.cpp
#include "../include/Scenes/Scene2.h"
#include "../models/triangle.h"
#include "../models/tree.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Scene2::Scene2(Camera& cam) : camera(cam) {
    // Initialize shaders
    auto shader_uni = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    auto shader_red = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_red.glsl");

    shaders = {shader_uni, shader_red};

    // Register shaders as camera observers
    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
    }

    camera.notifyObservers();

    // Load models
    std::vector<float> triangleVertices(std::begin(triangle), std::end(triangle));
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));

    auto triangleModel = std::make_shared<Model>(triangleVertices);
    auto treeModel = std::make_shared<Model>(treeVertices);

    // Create triangle drawable
    auto triangleDrawable = std::make_shared<DrawableObject>(triangleModel, shader_red);
    addDrawable(triangleDrawable);

    // Create a single tree instance
    auto treeDrawable = std::make_shared<DrawableObject>(treeModel, shader_red);

    Transformation treeTrans;
    treeTrans.translate(glm::vec3(0.0f, -0.9f, 1.0f));
    treeTrans.scale(glm::vec3(0.2f));
    treeDrawable->setTransformation(treeTrans);

    addDrawable(treeDrawable);
}