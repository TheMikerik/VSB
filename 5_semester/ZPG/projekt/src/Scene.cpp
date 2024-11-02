// Scene.cpp
#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::addDrawable(std::shared_ptr<DrawableObject> drawable) {
    drawables.push_back(drawable);
}

const std::vector<std::shared_ptr<DrawableObject>>& Scene::getDrawables() const {
    return drawables;
}

void Scene::render() const {
    for (const auto& drawable : drawables) {
        drawable->render();
    }
}