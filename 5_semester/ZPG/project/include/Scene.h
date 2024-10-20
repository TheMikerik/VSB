#ifndef SCENE_H
#define SCENE_H

#include "DrawableObject.h"
#include <vector>
#include <memory>


class Scene {
public:
    Scene();
    ~Scene();

    void addDrawable(std::shared_ptr<DrawableObject> drawable);
    void render() const;

private:
    std::vector<std::shared_ptr<DrawableObject>> drawables;
};

#endif // SCENE_H