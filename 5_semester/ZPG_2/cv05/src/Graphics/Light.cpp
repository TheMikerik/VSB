#include "Graphics/Light.h"
#include <algorithm>

Light::Light(const glm::vec3& position, const glm::vec3& color)
    : position(position), color(color)
{}

glm::vec3 Light::getPosition() const {
    return position;
}

glm::vec3 Light::getColor() const {
    return color;
}

void Light::setPosition(const glm::vec3& pos) {
    position = pos;
    notifyObservers();
}

void Light::setColor(const glm::vec3& col) {
    color = col;
    notifyObservers();
}

void Light::registerObserver(ILightObserver* observer) {
    observers.push_back(observer);
}

void Light::removeObserver(ILightObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Light::notifyObservers() {
    for(auto& observer : observers) {
        observer->onLightUpdate(position, color);
    }
}