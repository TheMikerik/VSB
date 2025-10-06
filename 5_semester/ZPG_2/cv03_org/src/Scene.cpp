#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::addDrawable(DrawableObject drawable) {
    drawables.push_back(drawable);
}

const std::vector<DrawableObject> &Scene::getDrawables() {
    return drawables;
}

void Scene::render() const {
    for (const auto& drawable : drawables) {
        drawable.render();
    }
}