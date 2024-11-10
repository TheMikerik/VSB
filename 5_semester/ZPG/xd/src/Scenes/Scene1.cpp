// Scene1.cpp
#include "../include/Scenes/Scene1.h"
#include "../models/triangle.h"
#include "../models/tree.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Scene1::Scene1(Camera& cam) : camera(cam) {
    auto shader_red = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_red.glsl");

    shaders = {shader_red};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
    }

    camera.notifyObservers();

    std::vector<float> triangleVertices(std::begin(triangle), std::end(triangle));

    auto triangleModel = std::make_shared<Model>(triangleVertices);

    auto triangleDrawable = std::make_shared<DrawableObject>(triangleModel, shader_red);

    Transformation triangleTrans;
    triangleTrans.scale(glm::vec3(5.0f));
    triangleTrans.translate(glm::vec3(0.0f, 2.0f, 0.0f));
    triangleDrawable->setTransformation(triangleTrans);
    addDrawable(triangleDrawable);
}