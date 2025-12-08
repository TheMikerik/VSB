#pragma once

#include "Interfaces/ITransformationOperation.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class BezierCurveOperation : public ITransformationOperation {
private:
    std::vector<glm::vec3> controlPoints;
    float progress;
    
public:
    BezierCurveOperation(const std::vector<glm::vec3>& points) 
        : controlPoints(points), progress(0.0f) {}
    
    void setProgress(float t) {
        progress = glm::clamp(t, 0.0f, 1.0f);
    }
    
    float getProgress() const {
        return progress;
    }
    
    void apply(glm::mat4& modelMatrix) const override {
        if (controlPoints.size() < 4) return;
        
        glm::vec3 position = calculatePosition(progress);
        glm::vec3 tangent = calculateTecna(progress);
        
        modelMatrix = glm::translate(modelMatrix, position);
        
        if (glm::length(tangent) > 0.0001f) {
            glm::vec3 forward = glm::normalize(tangent);
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::vec3 right = glm::normalize(glm::cross(up, forward));
            up = glm::normalize(glm::cross(forward, right));
            
            glm::mat4 rotationMatrix = glm::mat4(1.0f);
            rotationMatrix[0] = glm::vec4(right, 0.0f);
            rotationMatrix[1] = glm::vec4(up, 0.0f);
            rotationMatrix[2] = glm::vec4(forward, 0.0f);
            
            modelMatrix = modelMatrix * rotationMatrix;
        }
    }
    
private:
    glm::vec3 calculatePosition(float t) const {
        int numSegments = controlPoints.size() - 3;
        if (numSegments <= 0) return controlPoints[0];
        
        float segmentT = t * numSegments;
        int segmentIndex = static_cast<int>(segmentT);
        if (segmentIndex >= numSegments) {
            segmentIndex = numSegments - 1;
            segmentT = 1.0f;
        } else {
            segmentT = segmentT - segmentIndex;
        }
        
        glm::vec3 p0 = controlPoints[segmentIndex];
        glm::vec3 p1 = controlPoints[segmentIndex + 1];
        glm::vec3 p2 = controlPoints[segmentIndex + 2];
        glm::vec3 p3 = controlPoints[segmentIndex + 3];
        
        float u = 1.0f - segmentT;
        float t2 = segmentT * segmentT;
        float u2 = u * u;
        float u3 = u2 * u;
        float t3 = t2 * segmentT;
        
        // B(t) = (1-t)^3*P0 + 3*(1-t)^2*t*P1 + 3*(1-t)*t^2*P2 + t^3*P3
        return u3 * p0 + 3.0f * u2 * segmentT * p1 + 3.0f * u * t2 * p2 + t3 * p3;
    }
    
    glm::vec3 calculateTecna(float t) const {
        int numSegments = controlPoints.size() - 3;
        if (numSegments <= 0) return glm::vec3(1.0f, 0.0f, 0.0f);
        
        float segmentT = t * numSegments;
        int segmentIndex = static_cast<int>(segmentT);
        if (segmentIndex >= numSegments) {
            segmentIndex = numSegments - 1;
            segmentT = 1.0f;
        } else {
            segmentT = segmentT - segmentIndex;
        }
        
        glm::vec3 p0 = controlPoints[segmentIndex];
        glm::vec3 p1 = controlPoints[segmentIndex + 1];
        glm::vec3 p2 = controlPoints[segmentIndex + 2];
        glm::vec3 p3 = controlPoints[segmentIndex + 3];
        
        float u = 1.0f - segmentT;
        float t2 = segmentT * segmentT;
        float u2 = u * u;
        
        // B'(t) = 3*(1-t)^2*(P1-P0) + 6*(1-t)*t*(P2-P1) + 3*t^2*(P3-P2)
        return 3.0f * u2 * (p1 - p0) + 6.0f * u * segmentT * (p2 - p1) + 3.0f * t2 * (p3 - p2);
    }
};