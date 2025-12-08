#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Interfaces/ICameraObserver.h"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  60.0f;

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float AspectRatio;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3 up       = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw          = YAW,
            float pitch        = PITCH);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

    void registerObserver(ICameraObserver* observer);
    void removeObserver(ICameraObserver* observer);
    void notifyObservers();

    glm::vec3 getPosition() const;

    glm::vec3 getFront() const;

private:
    void updateCameraVectors();

    std::vector<ICameraObserver*> observers;
};