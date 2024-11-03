#pragma once
#include <glm/glm.hpp>

class ILightObserver {
public:
    virtual ~ILightObserver() {}
    virtual void onLightUpdate(const glm::vec3& position, const glm::vec3& color) = 0;
};