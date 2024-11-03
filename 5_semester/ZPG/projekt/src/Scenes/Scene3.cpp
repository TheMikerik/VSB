// Scene3.cpp
#include "../include/Scenes/Scene3.h"
#include "../models/sphere.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Scene3::Scene3(Camera& cam, Light& light) : camera(cam), pointLight(light) {
    auto shader_pl = std::make_shared<ShaderProgram>("./shaders/vertex_shader_pl.glsl", "./shaders/fragment_shader_pl.glsl");

    shaders = {shader_pl};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
        pointLight.registerObserver(shader.get());
    }

    pointLight.notifyObservers();
    camera.notifyObservers();

    std::vector<float> sphereVertices(std::begin(sphere), std::end(sphere));
    auto sphereModel = std::make_shared<Model>(sphereVertices);

    std::vector<glm::vec3> spherePositions = {
        glm::vec3( 2.0f,  2.0f,  0.0f),
        glm::vec3(-2.0f,  2.0f,  0.0f),
        glm::vec3( 2.0f, -2.0f,  0.0f),
        glm::vec3(-2.0f, -2.0f,  0.0f)
    };

    for(const auto& pos : spherePositions) {
        auto sphereDrawable = std::make_shared<DrawableObject>(sphereModel, shader_pl);

        Transformation sphereTrans;
        sphereTrans.scale(glm::vec3(3.0f));
        sphereTrans.translate(pos);

        sphereDrawable->setTransformation(sphereTrans);

        addDrawable(sphereDrawable);
    }
}