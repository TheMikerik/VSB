#include "Scenes/Scene6.h"
#include "Graphics/Light.h"
#include "Graphics/Spotlight.h"    
#include "../models/tree.h"
#include "../models/platform.h"
#include "../models/plain_texture.h" // Add this include
#include "../include/Core/Material.h"
#include "../include/Core/MaterialManager.h"
#include "../include/Core/Texture.h" // Add this include
#include "../include/Core/Transformation/ScaleOperation.h"
#include "../include/Core/Transformation/TranslateOperation.h"
#include "../include/Core/Transformation/RotateOperation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <iostream>

Scene6::Scene6(Camera& cam) 
    : camera(cam), 
      spotlight(std::make_shared<Spotlight>(glm::vec3(5.0f, 4.0f, 5.0f), glm::vec3(1.0f, 0.0f, 1.0f)))
{
    auto materialManager = MaterialManager::getInstance();

    auto shader_platform = std::make_shared<ShaderProgram>("./shaders/texture_shaders/v_f_l.glsl", "./shaders/texture_shaders/fragment_shader_flashlight.glsl"); 
    auto shader_sl = std::make_shared<ShaderProgram>("./shaders/v_l.glsl", "./shaders/f.glsl");

    shaders = {shader_platform, shader_sl};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
    }

    camera.notifyObservers();

    std::vector<float> plainTextureVertices(std::begin(plain_texture), std::end(plain_texture));
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));

    auto platformModel = std::make_shared<Model>(plainTextureVertices, true);
    auto treeModel = std::make_shared<Model>(treeVertices);

    std::shared_ptr<Texture> grassTexture = std::make_shared<Texture>("./images/grass.png", false);

    auto platformDrawable = std::make_shared<DrawableObject>(platformModel, shader_platform, 
                                                             Transformation(), 
                                                             *materialManager.getMaterial("platform"),
                                                             grassTexture);

    Transformation platformTrans;
    auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(5.0f, 1.0f, 5.0f));
    platformTrans.addOperation(scaleOp);
    platformDrawable->setTransformation(platformTrans);

    addDrawable(platformDrawable);

    for (int i = 0; i < 300; ++i) {
        auto treeDrawable = std::make_shared<DrawableObject>(treeModel, shader_sl);

        Transformation treeTrans;

        auto translateOp = std::make_shared<TranslateOperation>(
            glm::vec3(getRandom(-75.0f, 75.0f), 0.0f, getRandom(-75.0f, 75.0f)));
        treeTrans.addOperation(translateOp);

        auto scaleOp = std::make_shared<ScaleOperation>(
            glm::vec3(getRandom(0.2f, 1.2f)));
        treeTrans.addOperation(scaleOp);

        auto rotateOp = std::make_shared<RotateOperation>(
            getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        treeTrans.addOperation(rotateOp);

        treeDrawable->setTransformation(treeTrans);
        auto treeMaterial = materialManager.getMaterial("tree");
        treeDrawable->setMaterial(*treeMaterial);

        if (i % 6 == 0){
            treeDrawables.push_back(treeDrawable);
        }

        addDrawable(treeDrawable);
    }
}

void Scene6::render(float dt) {
    for (auto& treeDrawable : treeDrawables) {
        auto trans = treeDrawable->getTransformation();
        auto rotateOp = std::make_shared<RotateOperation>(dt * 50, glm::vec3(0.0f, 1.0f, 0.0f));
        trans.addOperation(rotateOp);
        treeDrawable->setTransformation(trans);

        treeDrawable->render();
    }

    glm::vec3 spotlightPos = camera.getPosition();
    glm::vec3 spotlightDir = glm::normalize(camera.getFront());
    spotlight->update(spotlightPos, spotlightDir);

    for (auto& shader : shaders) {
        spotlight->applyToShader(shader);
    }

    Scene::render(dt);
}

float Scene6::getRandom(float min, float max) {
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}