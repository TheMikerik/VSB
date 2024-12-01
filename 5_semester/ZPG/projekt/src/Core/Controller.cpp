#include "Core/Controller.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "Core/Transformation.h"
#include "Core/Transformation/TranslateOperation.h"
#include "Core/Transformation/RotateOperation.h"
#include "Core/Transformation/ScaleOperation.h"

static Controller* controllerInstance = nullptr;

void Controller::errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

void Controller::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Controller::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (controllerInstance) {
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
            if (controllerInstance->firstMouse) {
                controllerInstance->lastX = static_cast<float>(xpos);
                controllerInstance->lastY = static_cast<float>(ypos);
                controllerInstance->firstMouse = false;
            }

            float xoffset = static_cast<float>(xpos) - controllerInstance->lastX;
            float yoffset = controllerInstance->lastY - static_cast<float>(ypos);

            controllerInstance->lastX = static_cast<float>(xpos);
            controllerInstance->lastY = static_cast<float>(ypos);

            controllerInstance->camera.ProcessMouseMovement(xoffset, yoffset);
        }
    }
}

void Controller::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (controllerInstance) {
        controllerInstance->camera.ProcessMouseScroll(static_cast<float>(yoffset));
    }
}

void Controller::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (controllerInstance && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        
        float x = (2.0f * xpos) / width - 1.0f;
        float y = 1.0f - (2.0f * ypos) / height;
        
        glm::vec4 rayClip = glm::vec4(x, y, -1.0f, 1.0f);
        glm::mat4 invProj = glm::inverse(controllerInstance->camera.getProjectionMatrix());
        glm::mat4 invView = glm::inverse(controllerInstance->camera.GetViewMatrix());
        
        glm::vec4 rayEye = invProj * rayClip;
        rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
        
        glm::vec4 rayWorld = invView * rayEye;
        glm::vec3 rayDir = glm::normalize(glm::vec3(rayWorld));
        
        controllerInstance->handleRayIntersection(controllerInstance->camera.Position, rayDir);
    }
}

Controller::Controller(GLFWwindow* win, Camera& cam, std::vector<std::shared_ptr<Scene>>& scns)
    : window(win), camera(cam), scenes(scns),
      selectedDrawableIndex(0), rotationEnabled(false),
      lastX(400.0f), lastY(300.0f), firstMouse(true)
{
    controllerInstance = this;

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void Controller::handleInput(float deltaTimeInput, int& currentSceneIndex) {
    currentSceneIndex = this->currentSceneIndex;
    processKeyboardInput(deltaTimeInput);
    processTransformationInput();
}

void Controller::switchScene(int index){
    if (index >=0 && index < static_cast<int>(scenes.size())) {
        currentSceneIndex = index;
        selectedDrawableIndex = 0;
        std::cout << "Scene: " << currentSceneIndex + 1 << std::endl;
    } else {
        std::cerr << "Invalid scene index: " << index << std::endl;
    }
}

void Controller::handleRayIntersection(const glm::vec3& rayOrigin, const glm::vec3& rayDir) {
    float closestDist = std::numeric_limits<float>::max();
    int closestIndex = -1;
    
    auto& currentScene = scenes[currentSceneIndex];
    auto& drawables = currentScene->getDrawables();
    
    for (size_t i = 0; i < drawables.size(); i++) {
        glm::vec3 objectPos = drawables[i]->getPosition();
        auto selectedDrawable = drawables[selectedDrawableIndex];
        float radius = 1.0f;
        
        glm::vec3 L = objectPos - rayOrigin;
        float tca = glm::dot(L, rayDir);
        if (tca < 0) continue;
        
        float d2 = glm::dot(L, L) - tca * tca;
        float radius2 = radius * radius;
        if (d2 > radius2) continue;
        
        float thc = sqrt(radius2 - d2);
        float t0 = tca - thc;
        
        if (t0 < closestDist) {
            closestDist = t0;
            closestIndex = i;
        }
    }
    
    if (closestIndex != -1) {
        selectedDrawableIndex = closestIndex;
        std::cout << "Selected object " << closestIndex << std::endl;
    }
}

void Controller::processKeyboardInput(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime * 3);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime * 3);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime * 3);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime * 3);


    static bool sceneKeyPressedLastFrame[5] = {false, false, false, false, false};

    bool sceneKey1PressedThisFrame = glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS;
    bool sceneKey2PressedThisFrame = glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS;
    bool sceneKey3PressedThisFrame = glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS;
    bool sceneKey4PressedThisFrame = glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS;
    bool sceneKey5PressedThisFrame = glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS;

    if (sceneKey1PressedThisFrame && !sceneKeyPressedLastFrame[0]) switchScene(0);
    if (sceneKey2PressedThisFrame && !sceneKeyPressedLastFrame[1]) switchScene(1);
    if (sceneKey3PressedThisFrame && !sceneKeyPressedLastFrame[2]) switchScene(2);
    if (sceneKey4PressedThisFrame && !sceneKeyPressedLastFrame[3]) switchScene(3);
    if (sceneKey5PressedThisFrame && !sceneKeyPressedLastFrame[4]) switchScene(4);

    sceneKeyPressedLastFrame[0] = sceneKey1PressedThisFrame;
    sceneKeyPressedLastFrame[1] = sceneKey2PressedThisFrame;
    sceneKeyPressedLastFrame[2] = sceneKey3PressedThisFrame;
    sceneKeyPressedLastFrame[3] = sceneKey4PressedThisFrame;
    sceneKeyPressedLastFrame[4] = sceneKey5PressedThisFrame;



    static bool spacePressedLastFrame = false;
    bool spacePressedThisFrame = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;

    if (spacePressedThisFrame && !spacePressedLastFrame) {
        if (currentSceneIndex >= 0 && currentSceneIndex < static_cast<int>(scenes.size())) {
            scenes[currentSceneIndex]->switchShader();
        }
    }

    static bool cPressedLastFrame = false;
    bool lPressedThisFrame = glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS;
    
    if (lPressedThisFrame && !cPressedLastFrame) {
        bool cursorEnabled = glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL;
        glfwSetInputMode(window, GLFW_CURSOR, cursorEnabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        firstMouse = true;
    }

    cPressedLastFrame = lPressedThisFrame;
    spacePressedLastFrame = spacePressedThisFrame;
}

void Controller::processTransformationInput() {
    if (scenes.empty()) return;

    auto& currentScene = scenes[currentSceneIndex];
    if (!currentScene) return;

    auto& drawables = currentScene->getDrawables();
    if (drawables.empty()) return;

    if (selectedDrawableIndex >= drawables.size())
        selectedDrawableIndex = 0;

    auto selectedDrawable = drawables[selectedDrawableIndex];

    float translationStep = 0.05f;
    float rotationStep = 5.0f;
    float scaleStep = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        Transformation trans = selectedDrawable->getTransformation();
        if (!rotationEnabled){
            auto translateOp = std::make_shared<TranslateOperation>(glm::vec3(translationStep, 0.0f, 0.0f));
            trans.addOperation(translateOp);
            std::cout << "Translated +X" << std::endl;
        } else {
            auto rotateOp = std::make_shared<RotateOperation>(rotationStep, glm::vec3(1.0f, 0.0f, 0.0f));
            trans.addOperation(rotateOp);
            std::cout << "Rotated +X" << std::endl;
        }
        selectedDrawable->setTransformation(trans);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        Transformation trans = selectedDrawable->getTransformation();
        if (!rotationEnabled){
            auto translateOp = std::make_shared<TranslateOperation>(glm::vec3(-translationStep, 0.0f, 0.0f));
            trans.addOperation(translateOp);
            std::cout << "Translated -X" << std::endl;
        } else {
            auto rotateOp = std::make_shared<RotateOperation>(-rotationStep, glm::vec3(1.0f, 0.0f, 0.0f));
            trans.addOperation(rotateOp);
            std::cout << "Rotated -X" << std::endl;
        }
        selectedDrawable->setTransformation(trans);
    }

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        Transformation trans = selectedDrawable->getTransformation();
        if (!rotationEnabled) {
            auto translateOp = std::make_shared<TranslateOperation>(glm::vec3(0.0f, translationStep, 0.0f));
            trans.addOperation(translateOp);
            std::cout << "Translated +Y" << std::endl;
        } else {
            auto rotateOp = std::make_shared<RotateOperation>(rotationStep, glm::vec3(0.0f, 1.0f, 0.0f));
            trans.addOperation(rotateOp);
            std::cout << "Rotated +Y" << std::endl;
        }
        selectedDrawable->setTransformation(trans);
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        Transformation trans = selectedDrawable->getTransformation();
        if (!rotationEnabled) {
            auto translateOp = std::make_shared<TranslateOperation>(glm::vec3(0.0f, -translationStep, 0.0f));
            trans.addOperation(translateOp);
            std::cout << "Translated -Y" << std::endl;
        } else {
            auto rotateOp = std::make_shared<RotateOperation>(-rotationStep, glm::vec3(0.0f, 1.0f, 0.0f));
            trans.addOperation(rotateOp);
            std::cout << "Rotated -Y" << std::endl;
        }
        selectedDrawable->setTransformation(trans);
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        Transformation trans = selectedDrawable->getTransformation();
        if (!rotationEnabled) {
            auto translateOp = std::make_shared<TranslateOperation>(glm::vec3(0.0f, 0.0f, translationStep));
            trans.addOperation(translateOp);
            std::cout << "Translated +Z" << std::endl;
        } else {
            auto rotateOp = std::make_shared<RotateOperation>(rotationStep, glm::vec3(0.0f, 0.0f, 1.0f));
            trans.addOperation(rotateOp);
            std::cout << "Rotated +Z" << std::endl;
        }
        selectedDrawable->setTransformation(trans);
    }

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        Transformation trans = selectedDrawable->getTransformation();
        if (!rotationEnabled) {
            auto translateOp = std::make_shared<TranslateOperation>(glm::vec3(0.0f, 0.0f, -translationStep));
            trans.addOperation(translateOp);
            std::cout << "Translated -Z" << std::endl;
        } else {
            auto rotateOp = std::make_shared<RotateOperation>(-rotationStep, glm::vec3(0.0f, 0.0f, 1.0f));
            trans.addOperation(rotateOp);
            std::cout << "Rotated -Z" << std::endl;
        }
        selectedDrawable->setTransformation(trans);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        Transformation trans = selectedDrawable->getTransformation();
        auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(1.0f + scaleStep));
        trans.addOperation(scaleOp);
        selectedDrawable->setTransformation(trans);
        std::cout << "Scaled Up" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        Transformation trans = selectedDrawable->getTransformation();
        auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(1.0f - scaleStep));
        trans.addOperation(scaleOp);
        selectedDrawable->setTransformation(trans);
        std::cout << "Scaled Down" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        rotationEnabled = !rotationEnabled;
        std::cout << "Rotation: " << (rotationEnabled ? "Enabled" : "Disabled") << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        selectedDrawableIndex = (selectedDrawableIndex + 1) % drawables.size();
        std::cout << "Switched to Drawable Index: " << selectedDrawableIndex << std::endl;
    }
}

void Controller::setSelectedDrawable(size_t index) {
    if (index < scenes.size()) {
        selectedDrawableIndex = index;
    }
}

void Controller::setRotationEnabled(bool enabled) {
    rotationEnabled = enabled;
}

bool Controller::isRotationEnabled() const {
    return rotationEnabled;
}