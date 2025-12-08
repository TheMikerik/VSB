// Scene_arcade.cpp
#include "Scenes/Scene_arcade.h"
#include "Graphics/Light.h"
#include "Graphics/Spotlight.h"
#include "../models/tree.h"
#include "../models/platform.h"
#include "../include/Core/Transformation/ScaleOperation.h"
#include "../include/Core/Transformation/RotateOperation.h"
#include "Core/Texture.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include <cstdlib>
#include <iostream>

Scene_arcade::Scene_arcade(Camera& cam) : camera(cam),
    spotlight(std::make_shared<Spotlight>(glm::vec3(5.0f, 4.0f, 5.0f), glm::vec3(1.0f, 0.0f, 1.0f))), 
    flashlightEnabled(false),
    score(0),
    timeSinceLastSpawn(0.0f) {
    
    auto shader_platform = std::make_shared<ShaderProgram>("./shaders/v_l.glsl", "./shaders/f_l.glsl");
    auto shader_objects = std::make_shared<ShaderProgram>("./shaders/v_l.glsl", "./shaders/f_l.glsl");
    auto shader_texture = std::make_shared<ShaderProgram>(
        "./shaders/texture_shaders/vertex_shader.glsl",
        "./shaders/texture_shaders/fragment_shader.glsl"
    );

    shaders = {shader_platform, shader_objects, shader_texture};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
    }
    
    camera.notifyObservers();

    shader_texture->use();
    glUniform1i(glGetUniformLocation(shader_texture->getProgramID(), "texture_diffuse1"), 0);
    glUniform1i(glGetUniformLocation(shader_texture->getProgramID(), "hasTexture"), 1);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialAmbient"), 0.2f, 0.2f, 0.2f);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialDiffuse"), 0.7f, 0.7f, 0.7f);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialSpecular"), 0.4f, 0.4f, 0.4f);
    glUniform1f(glGetUniformLocation(shader_texture->getProgramID(), "materialShininess"), 16.0f);
    glUseProgram(0);

    std::vector<float> platformVertices(std::begin(platform), std::end(platform));
    auto platformModel = std::make_shared<Model>(platformVertices);

    Transformation platformTrans;
    auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(1.0f, 1.0f, 1.0f));
    platformTrans.addOperation(scaleOp);

    auto platformDrawable = std::make_shared<DrawableObject>(platformModel, shader_platform, platformTrans);
    addDrawable(platformDrawable);

    std::vector<float> treeVertices(std::begin(tree), std::end(tree));
    treeModel = std::make_shared<Model>(treeVertices);
    
    shrekModel = std::make_shared<Model>("shrek.obj");
    toiledModel = std::make_shared<Model>("toiled.obj");
    
    shrekTexture = std::make_shared<Texture>("./models/shrek.png");
    toiledTexture = std::make_shared<Texture>("./models/toiled.jpg");
}

void Scene_arcade::toggleFlashlight() {
    flashlightEnabled = !flashlightEnabled;
}

std::vector<glm::vec3> Scene_arcade::generateRandomPath() {
    std::vector<glm::vec3> path;
    int numPoints = 3 + rand() % 3;
    
    for (int i = 0; i < numPoints; ++i) {
        glm::vec3 point(
            getRandom(-15.0f, 15.0f),
            getRandom(0.0f, 3.0f),
            getRandom(-15.0f, 15.0f)
        );
        path.push_back(point);
    }
    
    return path;
}

void Scene_arcade::removeObject(std::shared_ptr<DrawableObject> object) {
    auto it = std::find_if(movingObjects.begin(), movingObjects.end(),
        [&object](const MovingObject& mo) { return mo.drawable == object; });
    
    if (it != movingObjects.end()) {
        movingObjects.erase(it);
    }
    
    objectLifetimes.erase(object);
    
    auto drawIt = std::find(drawables.begin(), drawables.end(), object);
    if (drawIt != drawables.end()) {
        drawables.erase(drawIt);
        
        for (size_t i = 0; i < drawables.size(); ++i) {
            drawables[i]->setID(static_cast<GLuint>(i + 1));
        }
    }
}

void Scene_arcade::deleteSelected() {
    if (selectedObjectIndex >= 0 && selectedObjectIndex < static_cast<int>(drawables.size())) {
        auto deletedDrawable = drawables[selectedObjectIndex];
        
        auto it = std::find_if(movingObjects.begin(), movingObjects.end(),
            [&deletedDrawable](const MovingObject& mo) { return mo.drawable == deletedDrawable; });
        
        if (it != movingObjects.end()) {
            score += it->value;
            std::cout << "+" << it->value << " points! Total score: " << score << std::endl;
            
            movingObjects.erase(it);
            objectLifetimes.erase(deletedDrawable);
        }
    }
    
    Scene::deleteSelected();
}

int Scene_arcade::selectObjectType() {
    int random = rand() % 100;
    
    if (random < 50) {
        return 0;
    } else if (random < 85) {
        return 1;
    } else {
        return 2;
    }
}

void Scene_arcade::spawnObject() {
    if (movingObjects.size() >= maxObjects) {
        return;
    }

    int objectType = selectObjectType();
    std::shared_ptr<DrawableObject> objectDrawable;
    int objectValue = 0;
    std::shared_ptr<ShaderProgram> selectedShader;

    auto path = generateRandomPath();
    auto pathOp = std::make_shared<PathFollowOperation>(path);

    if (objectType == 0) {
        objectValue = 1;
        selectedShader = shaders[1];
        objectDrawable = std::make_shared<DrawableObject>(treeModel, selectedShader);
    } 
    else if (objectType == 1) {
        objectValue = 5;
        selectedShader = shaders[2];
        objectDrawable = std::make_shared<DrawableObject>(shrekModel, selectedShader);
        objectDrawable->addTexture(shrekTexture, 0, "texture_diffuse1");
    } 
    else {
        objectValue = 10;
        selectedShader = shaders[2];
        objectDrawable = std::make_shared<DrawableObject>(toiledModel, selectedShader);
        objectDrawable->addTexture(toiledTexture, 0, "texture_diffuse1");
    }

    Transformation objectTrans;
    objectTrans.addOperation(pathOp);
    objectTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(getRandom(1.0f, 2.0f))));
    objectTrans.addOperation(std::make_shared<RotateOperation>(getRandom(0.0f, 360.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    objectDrawable->setTransformation(objectTrans);
    
    MovingObject mo;
    mo.drawable = objectDrawable;
    mo.pathOp = pathOp;
    mo.pathSpeed = getRandom(0.05f, 0.15f);
    mo.value = objectValue;
    
    movingObjects.push_back(mo);
    objectLifetimes[objectDrawable] = 0.0f;
    addDrawable(objectDrawable);
}

void Scene_arcade::render(float dt) {
    timeSinceLastSpawn += dt;
    if (timeSinceLastSpawn >= spawnInterval) {
        spawnObject();
        timeSinceLastSpawn = 0.0f;
    }

    std::vector<std::shared_ptr<DrawableObject>> objectsToRemove;
    
    for (auto& mo : movingObjects) {
        objectLifetimes[mo.drawable] += dt;
        
        float currentProgress = mo.pathOp->getProgress();
        currentProgress += dt * mo.pathSpeed;
        
        if (currentProgress >= 1.0f) {
            currentProgress = 0.0f;
        }
        
        mo.pathOp->setProgress(currentProgress);
        
        if (objectLifetimes[mo.drawable] >= objectMaxLifetime) {
            objectsToRemove.push_back(mo.drawable);
        }
    }
    
    for (auto& object : objectsToRemove) {
        removeObject(object);
    }

    if (flashlightEnabled) {
        glm::vec3 spotlightPos = camera.getPosition();
        glm::vec3 spotlightDir = glm::normalize(camera.getFront());
        spotlight->update(spotlightPos, spotlightDir);

        for (auto& shader : shaders) {
            spotlight->applyToShader(shader);
        }
    } else {
        spotlight->update(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        for (auto& shader : shaders) {
            spotlight->applyToShader(shader);
        }
    }

    Scene::render(dt);
}

float Scene_arcade::getRandom(float min, float max) {
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}