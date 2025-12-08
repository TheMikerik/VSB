// PathFollowOperation.h
#pragma once

#include "Interfaces/ITransformationOperation.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PathFollowOperation : public ITransformationOperation {
private:
    std::vector<glm::vec3> waypoints;
    float progress;
    
public:
    PathFollowOperation(const std::vector<glm::vec3>& points) 
        : waypoints(points), progress(0.0f) {}
    
    void setProgress(float t) {
        progress = glm::clamp(t, 0.0f, 1.0f);
    }
    
    float getProgress() const {
        return progress;
    }
    
    void apply(glm::mat4& modelMatrix) const override {
        if (waypoints.size() < 2) return;
        
        glm::vec3 position = interpolate(progress);
        modelMatrix = glm::translate(modelMatrix, position);
    }
    
private:
    glm::vec3 interpolate(float t) const {
        if (waypoints.size() == 0) return glm::vec3(0.0f);
        if (waypoints.size() == 1) return waypoints[0];
        
        float totalLength = waypoints.size() - 1;
        float scaledT = t * totalLength;
        
        int segment = static_cast<int>(scaledT);
        if (segment >= waypoints.size() - 1) {
            return waypoints.back();
        }
        
        float localT = scaledT - segment;
        
        return glm::mix(waypoints[segment], waypoints[segment + 1], localT);
    }
};