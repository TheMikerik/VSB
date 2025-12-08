// Scene.cpp
#include "Scenes/Scene.h"
#include "../models/tree.h"
#include "Core/Model.h"
#include "Shaders/ShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../include/Core/Transformation/ScaleOperation.h"
#include "../include/Core/Transformation/TranslateOperation.h"
#include <iostream>

Scene::Scene() : backgroundColor(0.0f, 0.0f, 0.0f, 1.0f), currentShader(0), 
                 selectedObjectIndex(-1) {} 

Scene::~Scene() {}

void Scene::addDrawable(std::shared_ptr<DrawableObject> drawable) {
    drawable->setID(static_cast<GLuint>(drawables.size() + 1));
    drawables.push_back(drawable);
}

const std::vector<std::shared_ptr<DrawableObject>>& Scene::getDrawables() const {
    return drawables;
}

void Scene::render(float dt) {
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    for (const auto& drawable : drawables) {
        glStencilFunc(GL_ALWAYS, drawable->getID(), 0xFF);
        drawable->render();
    }
    
    glDisable(GL_STENCIL_TEST);
}

void Scene::selectObject(GLuint objectID) {
    deselectAll();
    
    if (objectID > 0 && objectID <= drawables.size()) {
        drawables[objectID - 1]->setSelected(true);
        selectedObjectIndex = objectID - 1;
        std::cout << "Selected object ID: " << objectID << std::endl;
    }
}

void Scene::deselectAll() {
    for (auto& drawable : drawables) {
        drawable->setSelected(false);
    }
    selectedObjectIndex = -1;
}


void Scene::deleteSelected() {
    if (selectedObjectIndex >= 0 && selectedObjectIndex < static_cast<int>(drawables.size())) {
        std::cout << "Deleting object at index: " << selectedObjectIndex + 1 << std::endl;
        drawables.erase(drawables.begin() + selectedObjectIndex);
        
        for (size_t i = 0; i < drawables.size(); ++i) {
            drawables[i]->setID(static_cast<GLuint>(i + 1));
        }
        
        selectedObjectIndex = -1;
    }
}

void Scene::spawnObjectAtPosition(const glm::vec3& worldPos) {
    static std::shared_ptr<ShaderProgram> spawnShader = nullptr;
    if (!spawnShader) {
        spawnShader = std::make_shared<ShaderProgram>(
            "./shaders/vertex_shader.glsl",
            "./shaders/fragment_constant.glsl"
        );
    }
    
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));
    auto treeModel = std::make_shared<Model>(treeVertices);

    auto treeDrawable = std::make_shared<DrawableObject>(treeModel, spawnShader);
    
    Transformation treeTrans;
    treeTrans.addOperation(std::make_shared<TranslateOperation>(worldPos));
    treeTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(2.0f)));
    treeDrawable->setTransformation(treeTrans);
    addDrawable(treeDrawable);
    
    std::cout << "Spawned tree at world position: (" 
              << worldPos.x << ", " << worldPos.y << ", " << worldPos.z << ")" << std::endl;
}

int Scene::getSelectedIndex() const {
    return selectedObjectIndex;
}

void Scene::setBackgroundColor(const glm::vec4& color) {
    backgroundColor = color;
}

const glm::vec4& Scene::getBackgroundColor() const {
    return backgroundColor;
}

void Scene::switchShader() {
}