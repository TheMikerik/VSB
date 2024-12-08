#include "Scenes/Scene.h"

Scene::Scene() : backgroundColor(0.3f, 0.3f, 0.3f, 1.0f), currentShader(0) {}

Scene::~Scene() {}

void Scene::addDrawable(std::shared_ptr<DrawableObject> drawable) {
    drawables.push_back(drawable);
}

const std::vector<std::shared_ptr<DrawableObject>>& Scene::getDrawables() const {
    return drawables;
}

void Scene::render(float dt) {
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