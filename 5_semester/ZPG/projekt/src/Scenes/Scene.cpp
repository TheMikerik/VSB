// Scene.cpp
#include "Scenes/Scene.h"

Scene::Scene() : backgroundColor(0.0f, 0.0f, 0.0f, 1.0f), currentShader(0) {}

Scene::~Scene() {}

void Scene::addDrawable(std::shared_ptr<DrawableObject> drawable) {
    drawables.push_back(drawable);
}

void Scene::addLight(const Light& light) {
    lights.push_back(light);
}

const std::vector<Light>& Scene::getLights() const {
    return lights;
}

const std::vector<std::shared_ptr<DrawableObject>>& Scene::getDrawables() const {
    return drawables;
}

void Scene::render() const {
    for (const auto& drawable : drawables) {
        drawable->render();
    }
}

void Scene::setBackgroundColor(const glm::vec4& color) {
    backgroundColor = color;
}

const glm::vec4& Scene::getBackgroundColor() const {
    return backgroundColor;
}

void Scene::switchShader() {
}