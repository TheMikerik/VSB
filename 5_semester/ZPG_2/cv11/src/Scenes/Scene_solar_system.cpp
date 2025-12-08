// Scene_solar_system.cpp
#include "Scenes/Scene_solar_system.h"
#include "Graphics/Light.h"
#include "Core/Texture.h"
#include "../models/sphere.h"
#include "../include/Core/Transformation/RotateOperation.h"
#include "../include/Core/Transformation/ScaleOperation.h"
#include "../include/Core/Transformation/TranslateOperation.h"
#include "../include/Core/Transformation/DynamicRotationOperation.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

Scene_solar_system::Scene_solar_system(Camera& cam) : camera(cam) {
    
    planets.reserve(10);
    this->addLight(Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(20.0f, 20.0f, 20.0f)));

    auto shader_texture = std::make_shared<ShaderProgram>(
        "./shaders/texture_shaders/vertex_shader.glsl",
        "./shaders/texture_shaders/fragment_shader.glsl"
    );

    auto shader_const = std::make_shared<ShaderProgram>(
        "./shaders/vertex_shader.glsl",
        "./shaders/fragment_constant.glsl"
    );

    shaders = {shader_texture, shader_const};

    for (auto& shader : shaders) {
        camera.registerObserver(shader.get());
        for (auto& light : this->lights) {
            light.registerObserver(shader.get());
        }
    }

    for (auto& shader : shaders) {
        shader->use();
        glUniform1i(glGetUniformLocation(shader->getProgramID(), "numLights"), static_cast<int>(lights.size()));
        glUseProgram(0);
    }

    shader_texture->use();
    glUniform1i(glGetUniformLocation(shader_texture->getProgramID(), "texture_diffuse1"), 0);
    glUniform1i(glGetUniformLocation(shader_texture->getProgramID(), "hasTexture"), 1);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialAmbient"), 0.3f, 0.3f, 0.3f);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialDiffuse"), 0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialSpecular"), 0.5f, 0.5f, 0.5f);
    glUniform1f(glGetUniformLocation(shader_texture->getProgramID(), "materialShininess"), 32.0f);
    glUseProgram(0);

    for (size_t i = 0; i < lights.size(); ++i) {
        for (auto& shader : shaders) {
            shader->onLightUpdate(static_cast<int>(i), lights[i].getPosition(), lights[i].getColor());
        }
        lights[i].notifyObservers(static_cast<int>(i));
    }

    camera.notifyObservers();

    auto planetModel = std::make_shared<Model>("planet.obj");
    
    auto sunTexture = std::make_shared<Texture>("./models/sun.jpeg");
    auto sunDrawable = std::make_shared<DrawableObject>(planetModel, shader_texture);

    Transformation sunTrans;
    sunTrans.addOperation(std::make_shared<TranslateOperation>(glm::vec3(0.0f, 0.0f, 0.0f)));
    sunTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(3.0f)));

    sunDrawable->setTransformation(sunTrans);
    sunDrawable->addTexture(sunTexture, 0, "texture_diffuse1");

    shader_texture->use();
    glUniform1i(glGetUniformLocation(shader_texture->getProgramID(), "isEmissive"), 1);
    glUseProgram(0);

    addDrawable(sunDrawable);

    shader_texture->use();
    glUniform1i(glGetUniformLocation(shader_texture->getProgramID(), "isEmissive"), 0);
    glUseProgram(0);

    auto mercuryTexture = std::make_shared<Texture>("./models/mercur.jpeg");
    auto mercuryDrawable = std::make_shared<DrawableObject>(planetModel, shader_texture);
    mercuryDrawable->addTexture(mercuryTexture, 0, "texture_diffuse1");
    addDrawable(mercuryDrawable);
    planets.emplace_back(mercuryDrawable, 7.0f, 1.2f, 1.0f, 1.0f, 43.0f);

    auto earthTexture = std::make_shared<Texture>("./models/earth.jpeg");
    auto earthDrawable = std::make_shared<DrawableObject>(planetModel, shader_texture);
    earthDrawable->addTexture(earthTexture, 0, "texture_diffuse1");
    addDrawable(earthDrawable);
    planets.emplace_back(earthDrawable, 12.0f, 0.5f, 2.0f, 1.5f, 30.0f);
    earthIndex = planets.size() - 1;
    Planet& earth = planets[earthIndex];

    auto moonTexture = std::make_shared<Texture>("./models/moon.jpeg");
    auto moonDrawable = std::make_shared<DrawableObject>(planetModel, shader_texture);
    moonDrawable->addTexture(moonTexture, 0, "texture_diffuse1");
    addDrawable(moonDrawable);
    planets.emplace_back(moonDrawable, 12.0f, 1.0f, 0.8f, 0.5f, 10.0f);
    moonIndex = planets.size() - 1;
    // Melo by to byt udelane tak, ze se bere transformace zeme a ne jeji pozice
    moonDynamicRotation = std::make_shared<DynamicRotationOperation>(&planets[earthIndex].worldPosition, 4.0f, 2.0f);

    auto marsTexture = std::make_shared<Texture>("./models/mars.jpeg");
    auto marsDrawable = std::make_shared<DrawableObject>(planetModel, shader_texture);
    marsDrawable->addTexture(marsTexture, 0, "texture_diffuse1");
    addDrawable(marsDrawable);
    planets.emplace_back(marsDrawable, 16.0f, 0.3f, 1.5f, 1.0f, 20.0f);

    auto loginModel = std::make_shared<Model>("login.obj");
    auto loginTexture = std::make_shared<Texture>("./models/login.jpeg");
    auto loginDrawable = std::make_shared<DrawableObject>(loginModel, shader_texture);
    loginDrawable->addTexture(loginTexture, 0, "texture_diffuse1");
    addDrawable(loginDrawable);
    planets.emplace_back(loginDrawable, 20.0f, 0.3f, 0.1f, 1.0f, 20.0f);
}

void Scene_solar_system::render(float dt) {
    for (size_t i = 0; i < planets.size(); ++i) {
        auto& planet = planets[i];
        
        if (i == moonIndex) {
            moonDynamicRotation->updatePosition(dt);
            planet.worldPosition = moonDynamicRotation->getWorldPosition();
        } else {
            planet.position += planet.speed * dt;
            float x = planet.distanceFromSun * std::cos(planet.position);
            float z = planet.distanceFromSun * std::sin(planet.position);
            planet.worldPosition = glm::vec3(x, 0.0f, z);
        }

        planet.selfRotationAngle += planet.selfRotationSpeed * dt;
        
        Transformation trans;
        trans.addOperation(std::make_shared<TranslateOperation>(planet.worldPosition));
        trans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(planet.scale)));
        trans.addOperation(std::make_shared<RotateOperation>(
            glm::degrees(planet.selfRotationAngle), 
            glm::vec3(0.0f, 1.0f, 0.0f)
        ));
        planet.drawable->setTransformation(trans);
    }
    
    Scene::render(dt);
}

void Scene_solar_system::addLight(const Light& light) {
    lights.push_back(light);
}

const std::vector<Light>& Scene_solar_system::getLights() const {
    return lights;
}