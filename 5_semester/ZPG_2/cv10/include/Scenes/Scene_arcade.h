#ifndef SCENE_ARCADE_H
#define SCENE_ARCADE_H

#include "Scene.h"
#include "Graphics/Camera.h"
#include "Graphics/Spotlight.h"
#include "Core/Transformation/PathFollowOperation.h"
#include <memory>
#include <vector>
#include <map>

struct MovingObject {
    std::shared_ptr<DrawableObject> drawable;
    std::shared_ptr<PathFollowOperation> pathOp;
    float pathSpeed;
    int value;
};

class Scene_arcade : public Scene {
public:
    Scene_arcade(Camera& cam);
    void render(float dt) override;
    void toggleFlashlight();
    void deleteSelected() override;
    int getScore() const { return score; }

private:
    Camera& camera;
    std::shared_ptr<Spotlight> spotlight;
    std::vector<std::shared_ptr<ShaderProgram>> shaders;
    std::vector<MovingObject> movingObjects;
    std::map<std::shared_ptr<DrawableObject>, float> objectLifetimes;
    bool flashlightEnabled;
    int score;

    std::shared_ptr<Model> treeModel;
    std::shared_ptr<Model> shrekModel;
    std::shared_ptr<Model> toiledModel;

    std::shared_ptr<Texture> shrekTexture;
    std::shared_ptr<Texture> toiledTexture;

    float timeSinceLastSpawn;
    const float spawnInterval = 0.5f;
    const int maxObjects = 8;
    const float objectMaxLifetime = 20; 

    float getRandom(float min, float max);
    void spawnObject();
    void removeObject(std::shared_ptr<DrawableObject> object);
    int selectObjectType();
    std::vector<glm::vec3> generateRandomPath();
};

#endif