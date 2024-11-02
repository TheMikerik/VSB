// Scene.h
#pragma once

#include "DrawableObject.h"
#include <vector>
#include <memory>

class Scene {
public:
    Scene();
    virtual ~Scene();

    virtual void addDrawable(std::shared_ptr<DrawableObject> drawable);
    virtual const std::vector<std::shared_ptr<DrawableObject>>& getDrawables() const;
    virtual void render() const;

protected:
    std::vector<std::shared_ptr<DrawableObject>> drawables;
};