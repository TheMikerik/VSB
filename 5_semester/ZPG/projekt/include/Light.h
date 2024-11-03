#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "ILightObserver.h"

class Light {
public:
    Light(const glm::vec3& position = glm::vec3(0.0f),
          const glm::vec3& color = glm::vec3(1.0f));

    // Getters
    glm::vec3 getPosition() const;
    glm::vec3 getColor() const;

    // Setters
    void setPosition(const glm::vec3& position);
    void setColor(const glm::vec3& color);

    // Observer management
    void registerObserver(ILightObserver* observer);
    void removeObserver(ILightObserver* observer);
    void notifyObservers();

private:
    glm::vec3 position;
    glm::vec3 color;
    std::vector<ILightObserver*> observers;
};