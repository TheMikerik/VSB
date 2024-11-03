// Scene3.cpp
#include "../include/Scenes/Scene3.h"
#include "../models/sphere.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Scene3::Scene3(Camera& cam, Light& light) : camera(cam), pointLight(light) {

    setBackgroundColor(glm::vec4(0.59f, 0.76f, 0.92f, 1.0f));
    auto shader_pl = std::make_shared<ShaderProgram>("./shaders/vertex_shader_pl.glsl", "./shaders/fragment_shader_pl.glsl");
    auto shader_const = std::make_shared<ShaderProgram>("./shaders/constant/vertex_constant.glsl", "./shaders/constant/fragment_constant.glsl");
    auto shader_phong = std::make_shared<ShaderProgram>("./shaders/phong/vertex_phong.glsl", "./shaders/phong/fragment_phong.glsl");
    auto shader_lambert = std::make_shared<ShaderProgram>("./shaders/lambert/vertex_lambert.glsl", "./shaders/lambert/fragment_lambert.glsl");

    shaders = {shader_lambert};

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
        auto sphereDrawable = std::make_shared<DrawableObject>(sphereModel, shader_lambert);

        Transformation sphereTrans;
        sphereTrans.scale(glm::vec3(3.0f));
        sphereTrans.translate(pos);

        sphereDrawable->setTransformation(sphereTrans);

        addDrawable(sphereDrawable);
    }
}