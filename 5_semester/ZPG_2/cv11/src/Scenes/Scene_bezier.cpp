#include "Scenes/Scene_bezier.h"
#include "../include/Core/Transformation/BezierCurveOperation.h"
#include "Core/Model.h"
#include "Graphics/Camera.h"
#include "Core/Texture.h"
#include "Shaders/ShaderProgram.h"
#include "Graphics/Spotlight.h"
#include "../models/tree.h"
#include "../models/platform.h"
#include "../include/Core/Transformation/TranslateOperation.h"
#include "../include/Core/Transformation/RotateOperation.h"
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <cstdlib>

Scene_bezier::Scene_bezier(Camera& camera) : camera(camera),
    spotlight(std::make_shared<Spotlight>(glm::vec3(5.0f, 4.0f, 5.0f), glm::vec3(1.0f, 0.0f, 1.0f))), 
    flashlightEnabled(false) {
    
    auto shader_texture = std::make_shared<ShaderProgram>(
        "./shaders/texture_shaders/vertex_shader.glsl",
        "./shaders/texture_shaders/fragment_shader.glsl"
    );
    auto shader_lighting = std::make_shared<ShaderProgram>("./shaders/v_l.glsl", "./shaders/f_l.glsl");
    
    shaders = {shader_texture, shader_lighting};
    
    for (auto& shader : shaders) {
        camera.registerObserver(shader.get());
    }
    
    shader_texture->use();
    glUniform1i(glGetUniformLocation(shader_texture->getProgramID(), "texture_diffuse1"), 0);
    glUniform1i(glGetUniformLocation(shader_texture->getProgramID(), "hasTexture"), 1);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialAmbient"), 0.2f, 0.2f, 0.2f);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialDiffuse"), 0.7f, 0.7f, 0.7f);
    glUniform3f(glGetUniformLocation(shader_texture->getProgramID(), "materialSpecular"), 0.4f, 0.4f, 0.4f);
    glUniform1f(glGetUniformLocation(shader_texture->getProgramID(), "materialShininess"), 16.0f);
    glUseProgram(0);
    
    camera.notifyObservers();

    controlPoints = {
        glm::vec3(-7.0f, 0.0f, 5.0f),
        glm::vec3( 1.0f, 0.0f, 3.0f),
        glm::vec3(-2.0f, 0.0f, -6.0f),
        glm::vec3( 3.0f, 0.0f, -7.0f)
    };
    
    bezierOp = std::make_shared<BezierCurveOperation>(controlPoints);
    
    auto shrekModel = std::make_shared<Model>("shrek.obj");
    auto shrekTexture = std::make_shared<Texture>("./models/shrek.png");
    shrekDrawable = std::make_shared<DrawableObject>(shrekModel, shader_texture);
    
    Transformation shrekTrans;
    shrekTrans.addOperation(bezierOp);
    shrekTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(2.0f)));
    
    shrekDrawable->setTransformation(shrekTrans);
    shrekDrawable->addTexture(shrekTexture, 0, "texture_diffuse1");
    
    addDrawable(shrekDrawable);

    std::vector<float> platformVertices(std::begin(platform), std::end(platform));
    auto platformModel = std::make_shared<Model>(platformVertices);
    
    Transformation platformTrans;
    platformTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(2.0f, 1.0f, 2.0f)));
    
    auto platformDrawable = std::make_shared<DrawableObject>(platformModel, shader_lighting, platformTrans);
    addDrawable(platformDrawable);

    std::vector<float> treeVertices(std::begin(tree), std::end(tree));
    auto treeModel = std::make_shared<Model>(treeVertices);

    for (int i = 0; i < 10; ++i) {
        auto treeDrawable = std::make_shared<DrawableObject>(treeModel, shader_lighting);

        Transformation treeTrans;
        treeTrans.addOperation(std::make_shared<TranslateOperation>(
            glm::vec3(getRandom(-15.0f, 15.0f), 0.0f, getRandom(-15.0f, 15.0f))));
        treeTrans.addOperation(std::make_shared<ScaleOperation>(
            glm::vec3(getRandom(0.2f, 1.2f))));
        treeTrans.addOperation(std::make_shared<RotateOperation>(
            getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

        treeDrawable->setTransformation(treeTrans);
        treeDrawables.push_back(treeDrawable);
        addDrawable(treeDrawable);
    }
}

void Scene_bezier::render(float dt) {
    static float time = 0.0f;
    time += dt * 0.3f;
    
    float progress = (sin(time) + 1.0f) * 0.5f;
    bezierOp->setProgress(progress);

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

void Scene_bezier::toggleFlashlight() {
    flashlightEnabled = !flashlightEnabled;
}

void Scene_bezier::addControlPoint(const glm::vec3& point) {
    controlPoints.push_back(point);
    bezierOp = std::make_shared<BezierCurveOperation>(controlPoints);

    if (shrekDrawable) {
        Transformation newTrans;
        newTrans.addOperation(bezierOp);
        newTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(0.3f)));
        shrekDrawable->setTransformation(newTrans);
    }
}

float Scene_bezier::getRandom(float min, float max) {
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}