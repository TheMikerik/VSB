// Scene.h
#pragma once

#include <glm/glm.hpp>
#include "Graphics/DrawableObject.h"
#include <vector>
#include <memory>

class Scene {
public:
    Scene();
    virtual ~Scene();

    virtual void render() const;
    virtual void addDrawable(std::shared_ptr<DrawableObject> drawable);
    virtual const std::vector<std::shared_ptr<DrawableObject>>& getDrawables() const;
    void setBackgroundColor(const glm::vec4& color);
    const glm::vec4& getBackgroundColor() const;
    virtual void switchShader();

protected:
    std::vector<std::shared_ptr<DrawableObject>> drawables;
    glm::vec4 backgroundColor;
    int currentShader;
};