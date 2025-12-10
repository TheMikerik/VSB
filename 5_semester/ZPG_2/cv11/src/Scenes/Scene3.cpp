// Scene3.cpp
#include "../include/Scenes/Scene3.h"
#include "../models/sphere.h"

#include "../include/Core/Transformation/ScaleOperation.h"
#include "../include/Core/Transformation/TranslateOperation.h"

#include "Core/Texture.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Scene3::Scene3(Camera& cam) : camera(cam) {

    this->addLight( Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)) );

    auto shader_const = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    auto shader_phong = std::make_shared<ShaderProgram>("./shaders/light_shaders/vertex_shader_with_lights.glsl", "./shaders/light_shaders/fragment_phong.glsl");
    auto shader_lambert = std::make_shared<ShaderProgram>("./shaders/light_shaders/vertex_shader_with_lights.glsl", "./shaders/light_shaders/fragment_lambert.glsl");
    auto shader_blinn = std::make_shared<ShaderProgram>("./shaders/light_shaders/vertex_shader_with_lights.glsl", "./shaders/light_shaders/fragment_blinn.glsl");

    auto shader_texture = std::make_shared<ShaderProgram>(
        "./shaders/texture_shaders/vertex_shader.glsl",
        "./shaders/texture_shaders/fragment_shader.glsl"
    );

    shaders = {shader_phong, shader_const, shader_lambert, shader_blinn, shader_texture};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
        for(auto& light : this->lights) {
            light.registerObserver(shader.get());
        }
    }

    for(auto& shader : shaders) {
        shader->use();
        glUniform1i(glGetUniformLocation(shader->getProgramID(), "numLights"), lights.size());
        glUseProgram(0);
    }

    for (size_t i = 0; i < this->lights.size(); ++i) {
        for(auto& shader : shaders) {
            shader->onLightUpdate(i, lights[i].getPosition(), lights[i].getColor());
        }
        lights[i].notifyObservers(i);
    }

    shader_texture->use();
    glUniform1i(glGetUniformLocation(shader_texture->getProgramID(), "texture_diffuse1"), 0);
    glUniform1i(glGetUniformLocation(shader_texture->getProgramID(), "hasTexture"), 1);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialAmbient"), 0.3f, 0.3f, 0.3f);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialDiffuse"), 0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialSpecular"), 0.5f, 0.5f, 0.5f);
    glUniform1f(glGetUniformLocation(shader_texture->getProgramID(), "materialShininess"), 32.0f);
    glUseProgram(0);
    
    camera.notifyObservers();

    auto planetModel = std::make_shared<Model>("planet.obj");
    auto planetTexture = std::make_shared<Texture>("./models/earth.jpeg");
    auto planetDrawable = std::make_shared<DrawableObject>(planetModel, shader_texture);
    planetDrawable->addTexture(planetTexture, 0, "texture_diffuse1");
    Transformation planetTrans;
    planetTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(3.0f)));
    planetTrans.addOperation(std::make_shared<TranslateOperation>(glm::vec3(2.0f, 2.0f, 0.0f)));
    planetDrawable->setTransformation(planetTrans);

    addDrawable(planetDrawable);


    std::vector<float> sphereVertices(std::begin(sphere), std::end(sphere));
    auto sphereModel = std::make_shared<Model>(sphereVertices);

    std::vector<glm::vec3> spherePositions = {
        glm::vec3(-2.0f,  2.0f,  0.0f),
        glm::vec3( 2.0f, -2.0f,  0.0f),
        glm::vec3(-2.0f, -2.0f,  0.0f),
    };

    for(const auto& pos : spherePositions) {
        auto sphereDrawable = std::make_shared<DrawableObject>(sphereModel, shaders[currentShader]);

        Transformation sphereTrans;

        auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(3.0f));
        sphereTrans.addOperation(scaleOp);

        auto translateOp = std::make_shared<TranslateOperation>(pos);
        sphereTrans.addOperation(translateOp);

        sphereDrawable->setTransformation(sphereTrans);

        addDrawable(sphereDrawable);
    }
}

void Scene3::switchShader() {
    if (shaders.empty()) {
        std::cerr << "No shaders available to switch." << std::endl;
        return;
    }

    currentShader = (currentShader + 1) % shaders.size();
    std::cout << "CURRENT_SHADER::" << currentShader << std::endl;

    for(auto& drawable : drawables) {
        drawable->setShader(shaders[currentShader]);
    }

    shaders[currentShader]->use();
    camera.notifyObservers();
    for(auto& light : this->lights) {
        light.notifyObservers(1);
    }
}

void Scene3::addLight(const Light& light) {
    lights.push_back(light);
}

const std::vector<Light>& Scene3::getLights() const {
    return lights;
}