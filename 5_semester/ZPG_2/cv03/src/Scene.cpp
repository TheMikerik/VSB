#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::addDrawable(std::shared_ptr<DrawableObject> drawable)
{
    drawables.push_back(drawable);
    printf("Drawable added to scene");
}

const std::vector<std::shared_ptr<DrawableObject>> &Scene::getDrawables()
{
    return drawables;
}

void Scene::render() const
{
    for (const auto& drawable : drawables) {
        drawable->render();
    }
}