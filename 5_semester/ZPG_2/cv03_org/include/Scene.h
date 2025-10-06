#pragma once

#include "DrawableObject.h"
#include <vector>



class Scene {
public:
    Scene();
    ~Scene();

    void addDrawable(DrawableObject drawable);
    const std::vector<DrawableObject>& getDrawables();
    void render() const;

private:
    std::vector<DrawableObject> drawables;
};