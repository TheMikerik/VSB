#pragma once

#include "DrawableObject.h"
#include <vector>
#include <memory>

class Scene {
public:
    Scene();
    ~Scene();

    void addDrawable(std::shared_ptr<DrawableObject> drawable);
    const std::vector<std::shared_ptr<DrawableObject>>& getDrawables();
    void render() const;

private:
    std::vector<std::shared_ptr<DrawableObject>> drawables;
};