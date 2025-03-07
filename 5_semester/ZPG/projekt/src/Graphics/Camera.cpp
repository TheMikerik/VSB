#include "Graphics/Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVITY),
        Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(Zoom), 1450.0f / 900.0f, 0.1f, 100.0f);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;

    notifyObservers();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    if(constrainPitch)
    {
        if(Pitch > 89.0f)
            Pitch = 89.0f;
        if(Pitch < -89.0f)
            Pitch = -89.0f;
    }

    updateCameraVectors();
    notifyObservers();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 210.0f)
        Zoom = 210.0f;

    notifyObservers();
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));  
    Up    = glm::normalize(glm::cross(Right, Front));
}

void Camera::registerObserver(ICameraObserver* observer)
{
    observers.push_back(observer);
}

void Camera::removeObserver(ICameraObserver* observer)
{
    observers.erase(
        std::remove(observers.begin(), observers.end(), observer),
        observers.end()
    );
}

void Camera::notifyObservers()
{
    glm::mat4 view = GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(Zoom), 1450.0f / 900.0f, 0.1f, 100.0f);

    for(auto& observer : observers)
    {
        observer->onCameraUpdate(view, projection);
    }
}

glm::vec3 Camera::getPosition() const {
    return Position;
}

glm::vec3 Camera::getFront() const {
    return Front;
}