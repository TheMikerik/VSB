// Scene5.cpp
#include "Scenes/Scene5.h"
#include "Graphics/Light.h"
#include "Core/Texture.h"

#include "../models/tree.h"
#include "../models/plain.h"
#include "../models/sphere.h"

#include "../include/Core/Transformation/ScaleOperation.h"
#include "../include/Core/Transformation/TranslateOperation.h"
#include "../include/Core/Transformation/RotateOperation.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

void Scene5::spawnObjectAtPosition(const glm::vec3& worldPos) {
    auto shader = shaders[3];
    
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));
    auto treeModel = std::make_shared<Model>(treeVertices);
    
    auto treeDrawable = std::make_shared<DrawableObject>(treeModel, shader);
    
    Transformation treeTrans;
    treeTrans.addOperation(std::make_shared<TranslateOperation>(worldPos));
    treeTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(2.0f)));
    treeDrawable->setTransformation(treeTrans);
    
    addDrawable(treeDrawable);
    
    std::cout << "Spawned tree at world position: (" 
              << worldPos.x << ", " << worldPos.y << ", " << worldPos.z << ")" << std::endl;
}

Scene5::Scene5(Camera& cam) : camera(cam) {
    std::srand(static_cast<unsigned int>(std::time(0)));

    for (int i = 0; i < 15; ++i) {
        glm::vec3 position = glm::vec3(
            static_cast<float>(rand() % 30 - 15),
            static_cast<float>(rand() % 10 + 1),
            static_cast<float>(rand() % 30 - 15)
        );
        glm::vec3 color = glm::vec3(1.0f);
        this->addLight(Light(position, color));
    }

    auto shader_texture = std::make_shared<ShaderProgram>(
        "./shaders/texture_shaders/vertex_shader.glsl",
        "./shaders/texture_shaders/fragment_shader.glsl"
    );
    auto shader_const = std::make_shared<ShaderProgram>(
        "./shaders/vertex_shader.glsl",
        "./shaders/fragment_constant.glsl"
    );
    auto shader_phong = std::make_shared<ShaderProgram>(
        "./shaders/light_shaders/vertex_shader_with_lights.glsl",
        "./shaders/light_shaders/depth_fragment_phong.glsl"
    );
    auto shader_lambert = std::make_shared<ShaderProgram>(
        "./shaders/light_shaders/vertex_shader_with_lights.glsl",
        "./shaders/light_shaders/depth_fragment_lambert.glsl"
    );
    auto shader_blinn = std::make_shared<ShaderProgram>(
        "./shaders/light_shaders/vertex_shader_with_lights.glsl",
        "./shaders/light_shaders/depth_fragment_blinn.glsl"
    );

    shaders = {shader_texture, shader_const, shader_phong, shader_lambert, shader_blinn};

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
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialAmbient"), 0.2f, 0.2f, 0.2f);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialDiffuse"), 0.7f, 0.7f, 0.7f);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialSpecular"), 0.4f, 0.4f, 0.4f);
    glUniform1f(glGetUniformLocation(shader_texture->getProgramID(), "materialShininess"), 16.0f);
    glUseProgram(0);

    for (size_t i = 0; i < lights.size(); ++i) {
        for (auto& shader : shaders) {
            shader->onLightUpdate(static_cast<int>(i), lights[i].getPosition(), lights[i].getColor());
        }
        lights[i].notifyObservers(static_cast<int>(i));
    }

    camera.notifyObservers();

    std::vector<float> plainVertices(std::begin(plain), std::end(plain));
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));

    auto plainModel = std::make_shared<Model>(plainVertices, true);
    auto treeModel = std::make_shared<Model>(treeVertices);

    auto grassTexture = std::make_shared<Texture>("./images/grass.png");

    Transformation groundTrans;
    groundTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(15.0f)));

    auto groundDrawable = std::make_shared<DrawableObject>(plainModel, shader_texture, groundTrans);
    groundDrawable->addTexture(grassTexture, 0, "texture_diffuse1");
    addDrawable(groundDrawable);

    auto formula1Model = std::make_shared<Model>("formula1.obj");
        auto formula1Drawable = std::make_shared<DrawableObject>(formula1Model, shader_blinn);

    Transformation formula1Trans;
    formula1Trans.addOperation(std::make_shared<TranslateOperation>(glm::vec3(1.0f, 0.5f, 0.0f)));
    formula1Trans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(0.05f)));
    formula1Trans.addOperation(std::make_shared<RotateOperation>(90.0f, glm::vec3(0.0f, 1.0f, 0.0f)));

    formula1Drawable->setTransformation(formula1Trans);
    addDrawable(formula1Drawable);



    auto shrekModel   = std::make_shared<Model>("shrek.obj");
    auto shrekTexture = std::make_shared<Texture>("./models/shrek.png");
    auto shrekDrawable = std::make_shared<DrawableObject>(shrekModel, shader_texture);

    Transformation shrekTrans;
    shrekTrans.addOperation(std::make_shared<TranslateOperation>(glm::vec3(-3.0f, 0.0f, 0.0f)));
    shrekTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(0.5f)));
    shrekTrans.addOperation(std::make_shared<RotateOperation>(180.0f, glm::vec3(0.0f, 1.0f, 0.0f)));

    shrekDrawable->setTransformation(shrekTrans);
    shrekDrawable->addTexture(shrekTexture, 0, "texture_diffuse1");
    addDrawable(shrekDrawable);

    auto toiledModel   = std::make_shared<Model>("toiled.obj");
    auto toiledTexture = std::make_shared<Texture>("./models/toiled.jpg");
    auto toiledDrawable = std::make_shared<DrawableObject>(toiledModel, shader_texture);

    Transformation toiledTrans;
    toiledTrans.addOperation(std::make_shared<TranslateOperation>(glm::vec3(0.0f, 0.0f, 0.0f)));
    toiledTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(0.5f)));
    toiledTrans.addOperation(std::make_shared<RotateOperation>(180.0f, glm::vec3(0.0f, 1.0f, 0.0f)));

    toiledDrawable->setTransformation(toiledTrans);
    toiledDrawable->addTexture(toiledTexture, 0, "texture_diffuse1");
    addDrawable(toiledDrawable);

    auto fionaModel   = std::make_shared<Model>("fiona.obj");
    auto fionaTexture = std::make_shared<Texture>("./models/fiona.png");
    auto fionaDrawable = std::make_shared<DrawableObject>(fionaModel, shader_texture);

    Transformation fionaTrans;
    fionaTrans.addOperation(std::make_shared<TranslateOperation>(glm::vec3(3.0f, 0.0f, 0.0f)));
    fionaTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(0.5f)));
    fionaTrans.addOperation(std::make_shared<RotateOperation>(180.0f, glm::vec3(0.0f, 1.0f, 0.0f)));

    fionaDrawable->setTransformation(fionaTrans);
    fionaDrawable->addTexture(fionaTexture, 0, "texture_diffuse1");
    addDrawable(fionaDrawable);

    
    for (int i = 0; i < 100; ++i) {
        int shaderIndex = rand() % 3;
        std::shared_ptr<ShaderProgram> selectedShader;
        switch (shaderIndex) {
            case 0: selectedShader = shader_phong; break;
            case 1: selectedShader = shader_lambert; break;
            case 2: selectedShader = shader_blinn; break;
        }

        auto treeDrawable = std::make_shared<DrawableObject>(treeModel, selectedShader);

        Transformation treeTrans;
        treeTrans.addOperation(std::make_shared<TranslateOperation>(
            glm::vec3(getRandom(-15.0f, 15.0f), 0.0f, getRandom(-15.0f, 15.0f))
        ));
        treeTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(getRandom(0.2f, 0.8f))));
        treeTrans.addOperation(std::make_shared<RotateOperation>(getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

        treeDrawable->setTransformation(treeTrans);

        if (i % 6 == 0) {
            treeDrawables.push_back(treeDrawable);
        }
        addDrawable(treeDrawable);
    }

    for (auto& firefly : this->getLights()) {
        std::vector<float> sphereVertices(std::begin(sphere), std::end(sphere));
        auto sphereModel = std::make_shared<Model>(sphereVertices);
        auto lightShader = shader_const;

        auto lightDrawable = std::make_shared<DrawableObject>(sphereModel, lightShader);
        Transformation lightTrans;
        lightTrans.addOperation(std::make_shared<TranslateOperation>(firefly.getPosition()));
        lightTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(0.2f)));
        lightDrawable->setTransformation(lightTrans);

        glm::vec3 initialDirection(
            getRandom(-1.0f, 1.0f),
            getRandom(-1.0f, 1.0f),
            getRandom(-1.0f, 1.0f)
        );
        lightDrawablesWithDirection.emplace_back(lightDrawable, glm::normalize(initialDirection));

        addDrawable(lightDrawable);
    }
}

float Scene5::getRandom(float min, float max) {
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void Scene5::addLight(const Light& light) {
    lights.push_back(light);
}

const std::vector<Light>& Scene5::getLights() const {
    return lights;
}

void Scene5::render(float dt) {
    for (size_t i = 0; i < lightDrawablesWithDirection.size(); ++i) {
        auto& item = lightDrawablesWithDirection[i];
        glm::vec3 newPosition = lights[i].getPosition() + item.direction * dt * 4.0f;

        if (newPosition.x >= 15.0f || newPosition.x <= -15.0f) {
            item.direction.x *= -1.0f;
            newPosition.x = glm::clamp(newPosition.x, -15.0f, 15.0f);
        }
        if (newPosition.y >= 10.0f || newPosition.y <= 1.0f) {
            item.direction.y *= -1.0f;
            newPosition.y = glm::clamp(newPosition.y, 1.0f, 10.0f);
        }
        if (newPosition.z >= 15.0f || newPosition.z <= -15.0f) {
            item.direction.z *= -1.0f;
            newPosition.z = glm::clamp(newPosition.z, -15.0f, 15.0f);
        }

        lights[i].setPosition(newPosition);
        lights[i].notifyObservers(static_cast<int>(i));

        Transformation trans;
        trans.addOperation(std::make_shared<TranslateOperation>(newPosition));
        trans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(0.2f)));
        item.drawable->setTransformation(trans);
    }
    Scene::render(dt);
}