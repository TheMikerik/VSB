// OrbitalRotationOperation.h
#pragma once

#include "Interfaces/ITransformationOperation.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

class DynamicRotationOperation : public ITransformationOperation {
private:
    glm::vec3* parentPosition;
    float distanceFromParent;
    float speed;
    float position;
    
public:
    DynamicRotationOperation(glm::vec3* parent, float distanceFromParent, float speed) 
        : parentPosition(parent), distanceFromParent(distanceFromParent), speed(speed), position(0.0f) {}
    
    void updatePosition(float dt) {
        position += speed * dt;
    }
    
    float getPosition() const {
        return position;
    }
    
    glm::vec3 getWorldPosition() const {
        if (parentPosition == nullptr) {
            return glm::vec3(0.0f);
        }
        
        float x = distanceFromParent * std::cos(position);
        float z = distanceFromParent * std::sin(position);
        
        return *parentPosition + glm::vec3(x, 0.0f, z);
    }
    
    void apply(glm::mat4& modelMatrix) const override {
        if (parentPosition == nullptr) return;
        
        glm::vec3 position = getWorldPosition();
        modelMatrix = glm::translate(modelMatrix, position);
    }
};