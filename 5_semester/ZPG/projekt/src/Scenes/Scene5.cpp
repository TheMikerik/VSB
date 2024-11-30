// Scene5.cpp
#include "Scenes/Scene5.h"
#include "Graphics/Light.h"

#include "../models/tree.h"
#include "../models/plain_texture.h"
#include "../models/sphere.h"

#include "../include/Core/Texture.h"
#include "../include/Core/Transformation/ScaleOperation.h"
#include "../include/Core/Transformation/TranslateOperation.h"
#include "../include/Core/Transformation/RotateOperation.h"
#include "../include/Core/Material.h"
#include "../include/Core/MaterialManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

Scene5::Scene5(Camera& cam) : camera(cam) { // Update this line
    std::srand(static_cast<unsigned int>(std::time(0)));
    auto materialManager = MaterialManager::getInstance();

    for (int i = 0; i < 15; ++i) {
        glm::vec3 position = glm::vec3(
            static_cast<float>(rand() % 30 - 15),
            static_cast<float>(rand() % 10 + 1),
            static_cast<float>(rand() % 30 - 15)
        );
        glm::vec3 color = glm::vec3(1.0f);
        this->addLight(Light(position, color));
    }

    auto shader_platform = std::make_shared<ShaderProgram>("./shaders/texture_shaders/vertex_shader.glsl", "./shaders/texture_shaders/fragment_shader.glsl");
    auto shader_const = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_constant.glsl");

    auto shader_phong = std::make_shared<ShaderProgram>("./shaders/light_shaders/vertex_shader_with_lights.glsl", "./shaders/light_shaders/depth_fragment_phong.glsl");
    auto shader_lambert = std::make_shared<ShaderProgram>("./shaders/light_shaders/vertex_shader_with_lights.glsl", "./shaders/light_shaders/depth_fragment_lambert.glsl");
    auto shader_blinn = std::make_shared<ShaderProgram>("./shaders/light_shaders/vertex_shader_with_lights.glsl", "./shaders/light_shaders/depth_fragment_blinn.glsl");

    shaders = {shader_platform, shader_const, shader_phong, shader_lambert, shader_blinn};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
        for(auto& light : this->lights) {
            light.registerObserver(shader.get());
        }
    }

    for(auto& shader : shaders) {
        shader->use();
        glUniform1i(glGetUniformLocation(shader->getProgramID(), "numLights"), lights.size());
    }

    for (size_t i = 0; i < this->lights.size(); ++i) {
        for(auto& shader : shaders) {
            shader->onLightUpdate(i, lights[i].getPosition(), lights[i].getColor());
        }
        lights[i].notifyObservers(i);
    }
    
    camera.notifyObservers();

    std::shared_ptr<Texture> grassTexture = std::make_shared<Texture>("./images/grass.png", false);

    std::vector<float> plainTextureVertices(std::begin(plain_texture), std::end(plain_texture));
    auto platformModel = std::make_shared<Model>(plainTextureVertices, true);

    // Create the DrawableObject with texture
    auto platformDrawable = std::make_shared<DrawableObject>(platformModel, shader_platform, 
                                                             Transformation(), 
                                                             *materialManager.getMaterial("platform"),
                                                             grassTexture);

    Transformation platformTrans;
    auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(15.0f, 1.0f, 15.0f));
    platformTrans.addOperation(scaleOp);
    platformDrawable->setTransformation(platformTrans);

    addDrawable(platformDrawable);

    std::vector<float> treeVertices(std::begin(tree), std::end(tree));
    auto treeModel = std::make_shared<Model>(treeVertices);

    for (int i = 0; i < 100; ++i) {
        int shaderIndex = rand() % 3;
        std::shared_ptr<ShaderProgram> selectedShader;
        std::shared_ptr<Material> treeMaterial; 
        switch(shaderIndex) {
            case 0: 
                selectedShader = shader_phong; 
                treeMaterial = materialManager.getMaterial("tree");
                break;
            case 1: 
                selectedShader = shader_lambert;
                treeMaterial = materialManager.getMaterial("tree-blueish");
                break;
            case 2: 
                selectedShader = shader_blinn;
                treeMaterial = materialManager.getMaterial("tree-brownish");
                break;
        }

        auto treeDrawable = std::make_shared<DrawableObject>(treeModel, selectedShader);

        Transformation treeTrans;

        auto translateOp = std::make_shared<TranslateOperation>(
            glm::vec3(getRandom(-15.0f, 15.0f), 0.0f, getRandom(-15.0f, 15.0f)));
        treeTrans.addOperation(translateOp);

        auto scaleOpTree = std::make_shared<ScaleOperation>(
            glm::vec3(getRandom(0.2f, 0.8f)));
        treeTrans.addOperation(scaleOpTree);

        // Initial rotation, just to set a base value
        auto rotateOp = std::make_shared<RotateOperation>(
            getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        treeTrans.addOperation(rotateOp);

        treeDrawable->setTransformation(treeTrans);
        if(treeMaterial) {
            treeDrawable->setMaterial(*treeMaterial);
        }

        if (i % 6 == 0){
            treeDrawables.push_back(treeDrawable);
        }

        addDrawable(treeDrawable);
    }

    for(auto& firefly : this->getLights()) {
        std::vector<float> sphereVertices(std::begin(sphere), std::end(sphere));
        auto sphereModel = std::make_shared<Model>(sphereVertices);
        auto lightShader = shader_const;

        auto lightDrawable = std::make_shared<DrawableObject>(sphereModel, lightShader);
        Transformation lightTrans;

        auto translateOp = std::make_shared<TranslateOperation>(firefly.getPosition());
        lightTrans.addOperation(translateOp);
        auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(0.2f));
        lightTrans.addOperation(scaleOp);

        lightDrawable->setTransformation(lightTrans);

        glm::vec3 initialDirection(getRandom(-1.0f, 1.0f), getRandom(-1.0f, 1.0f), getRandom(-1.0f, 1.0f));
        lightDrawablesWithDirection.emplace_back(lightDrawable, glm::normalize(initialDirection));

        auto lightMaterial = materialManager.getMaterial("light");
        lightDrawable->setMaterial(*lightMaterial);

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
    for (auto& treeDrawable : treeDrawables) {
        auto trans = treeDrawable->getTransformation();
        auto rotateOp = std::make_shared<RotateOperation>(dt * 50, glm::vec3(0.0f, 1.0f, 0.0f));
        trans.addOperation(rotateOp);
        treeDrawable->setTransformation(trans);
    }

    for (size_t i = 0; i < lightDrawablesWithDirection.size(); ++i) {
        auto& item = lightDrawablesWithDirection[i];
        glm::vec3 newPosition = lights[i].getPosition() + item.direction * dt * 4.0f;
        
        // Check boundaries before updating position
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
        
        // Update position
        lights[i].setPosition(newPosition);
        lights[i].notifyObservers(i);
        
        Transformation trans;
        trans.addOperation(std::make_shared<TranslateOperation>(newPosition));
        trans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(0.2f)));
        item.drawable->setTransformation(trans);
    }
    Scene::render(dt);
}