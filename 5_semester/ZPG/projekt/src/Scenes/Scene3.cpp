// Scene3.cpp
#include "../include/Scenes/Scene3.h"
#include "../models/sphere.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Scene3::Scene3(Camera& cam) : camera(cam) {
    auto shader_uni = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");

    shaders = {shader_uni};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
    }

    camera.notifyObservers();

    std::vector<float> sphereVertices(std::begin(sphere), std::end(sphere));

    auto sphereModel = std::make_shared<Model>(sphereVertices);

    std::vector<glm::vec3> spherePositions = {
        glm::vec3( 2.0f,  0.0f,  0.0f),
        glm::vec3(-2.0f,  0.0f,  0.0f),
        glm::vec3( 0.0f,  2.0f,  0.0f),
        glm::vec3( 0.0f, -2.0f,  0.0f)
    };

    for(const auto& pos : spherePositions) {
        auto sphereDrawable = std::make_shared<DrawableObject>(sphereModel, shader_uni);

        Transformation sphereTrans;
        sphereTrans.scale(glm::vec3(3.0f));
        sphereTrans.translate(pos);

        sphereDrawable->setTransformation(sphereTrans);

        addDrawable(sphereDrawable);
    }
}