#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::addDrawable(std::shared_ptr<DrawableObject> drawable)
{
    drawables.push_back(drawable);
    printf("Drawable added to scene");
}

void Scene::render() const
{
    for (const auto& drawable : drawables) {
        drawable->render();
    }
}