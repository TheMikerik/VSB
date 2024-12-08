#include "Scenes/Scene7.h"
#include "Graphics/Light.h"
#include "Graphics/Spotlight.h"

#include "../models/tree.h"
#include "../models/plain_texture.h"
#include "../models/sphere.h"

#include "../include/Core/Texture.h"
#include "../include/Core/Transformation/ScaleOperation.h"
#include "../include/Core/Transformation/TranslateOperation.h"
#include "../include/Core/Transformation/RotateOperation.h"
#include "../include/Core/Material.h"
#include "../include/Core/MaterialManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

Scene7::Scene7(Camera& cam) 
    : camera(cam),
    spotlight(std::make_shared<Spotlight>(glm::vec3(5.0f, 4.0f, 5.0f), glm::vec3(1.0f, 0.0f, 1.0f)))
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    auto materialManager = MaterialManager::getInstance();

    for (int i = 0; i < 15; ++i) {
        glm::vec3 position = glm::vec3(
            static_cast<float>(rand() % 30 - 15),
            static_cast<float>(rand() % 4 + 1),
            static_cast<float>(rand() % 30 - 15)
        );
        glm::vec3 color = glm::vec3(1.0f);
        this->addLight(Light(position, color));
    }

    auto shader_texture = std::make_shared<ShaderProgram>(
        "./shaders/texture_shaders/vertex_shader.glsl",
        "./shaders/texture_shaders/fragment_shader.glsl"
    );

    auto shader_phong = std::make_shared<ShaderProgram>(
        "./shaders/light_shaders/vertex_shader_with_lights.glsl",
        "./shaders/light_shaders/depth_fragment_phong.glsl"
    );
    auto shader_lambert = std::make_shared<ShaderProgram>(
        "./shaders/light_shaders/vertex_shader_with_lights.glsl",
        "./shaders/light_shaders/depth_fragment_lambert.glsl"
    );
    auto shader_blinn = std::make_shared<ShaderProgram>(
        "./shaders/light_shaders/vertex_shader_with_lights.glsl",
        "./shaders/light_shaders/depth_fragment_blinn.glsl"
    );

    shaders = {shader_texture, shader_phong, shader_lambert, shader_blinn};

    for (auto& shader : shaders) {
        camera.registerObserver(shader.get());
        for (auto& light : this->lights) {
            light.registerObserver(shader.get());
        }
    }

    for (auto& shader : shaders) {
        shader->use();
        glUniform1i(glGetUniformLocation(shader->getProgramID(), "numLights"), (lights.size()));
    }

    for (size_t i = 0; i < this->lights.size(); ++i) {
        for (auto& shader : shaders) {
            shader->onLightUpdate(i, lights[i].getPosition(), lights[i].getColor());
        }
        lights[i].notifyObservers(i);
    }

    camera.notifyObservers();

    std::shared_ptr<Texture> grassTexture = 
        std::make_shared<Texture>("./images/grass.png");

    std::vector<float> plainTextureVertices(std::begin(plain_texture), std::end(plain_texture));
    auto platformModel = std::make_shared<Model>(plainTextureVertices, true);

    auto platformDrawable = std::make_shared<DrawableObject>(
        platformModel, 
        shader_texture, 
        Transformation(), 
        *materialManager.getMaterial("platform"),
        grassTexture
    );

    Transformation platformTrans;
    auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(15.0f, 1.0f, 15.0f));
    platformTrans.addOperation(scaleOp);
    platformDrawable->setTransformation(platformTrans);

    addDrawable(platformDrawable);

    std::vector<float> treeVertices(std::begin(tree), std::end(tree));
    auto treeModel = std::make_shared<Model>(treeVertices);

    for (int i = 0; i < 20; ++i) {
        int shaderIndex = rand() % 3;
        std::shared_ptr<ShaderProgram> selectedShader;
        std::shared_ptr<Material> treeMaterial; 
        switch(shaderIndex) {
            case 0: 
                selectedShader = shader_phong; 
                treeMaterial = materialManager.getMaterial("tree");
                break;
            case 1: 
                selectedShader = shader_lambert;
                treeMaterial = materialManager.getMaterial("tree-blueish");
                break;
            case 2: 
                selectedShader = shader_blinn;
                treeMaterial = materialManager.getMaterial("tree-brownish");
                break;
        }

        auto treeDrawable = std::make_shared<DrawableObject>(treeModel, selectedShader);

        Transformation treeTrans;

        auto translateOp = std::make_shared<TranslateOperation>(
            glm::vec3(getRandom(-15.0f, 15.0f), 0.0f, getRandom(-15.0f, 15.0f))
        );
        treeTrans.addOperation(translateOp);

        auto scaleOpTree = std::make_shared<ScaleOperation>(
            glm::vec3(getRandom(0.2f, 0.8f))
        );
        treeTrans.addOperation(scaleOpTree);

        treeDrawable->setTransformation(treeTrans);
        if (treeMaterial) {
            treeDrawable->setMaterial(*treeMaterial);
        }

        addDrawable(treeDrawable);
    }

    for (int i = 0; i < 10; ++i) {
        auto zombieModel = std::make_shared<Object>("models/assimp/zombie/zombie.obj");
        
        auto zombieDrawable = std::make_shared<Drawable3DObject>(
            zombieModel, 
            shader_texture, 
            Transformation(), 
            std::make_shared<Texture>("models/assimp/zombie/zombie.png")
        );

        auto& trans = zombieDrawable->getTransformation();
        auto translateOp = std::make_shared<TranslateOperation>(
            glm::vec3(getRandom(-15.0f, 15.0f), 0.0f, getRandom(-15.0f, 15.0f))
        );
        trans.addOperation(translateOp);

        auto scaleOp = std::make_shared<ScaleOperation>(
            glm::vec3(1.0f)
        );
        trans.addOperation(scaleOp);

        auto rotateOp = std::make_shared<RotateOperation>(
            glm::radians(getRandom(0.0f, 360.0f)), 
            glm::vec3(1.0f, 0.0f, 1.0f)
        );
        trans.addOperation(rotateOp);

        drawable3DObjects.push_back(zombieDrawable);
    }

    for (int i = 0; i < 3; ++i) {
        auto houseModel = std::make_shared<Object>("models/assimp/house/house.obj");
        
        auto houseDrawable = std::make_shared<Drawable3DObject>(
            houseModel, 
            shader_texture, 
            Transformation(), 
            *materialManager.getMaterial("house"),
            std::make_shared<Texture>("models/assimp/house/house.png")
        );

        auto& trans = houseDrawable->getTransformation();
        auto translateOp = std::make_shared<TranslateOperation>(
            glm::vec3(getRandom(-11.0f, 11.0f), 0.0f, getRandom(-11.0f, 11.0f))
        );
        trans.addOperation(translateOp);

        auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(0.3f));
        trans.addOperation(scaleOp);

        auto rotateOp = std::make_shared<RotateOperation>(
            glm::radians(getRandom(0.0f, 360.0f)), 
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        trans.addOperation(rotateOp);

        drawable3DObjects.push_back(houseDrawable);
    }

    for (int i = 0; i < 10; ++i) {
        auto wolfModel = std::make_shared<Object>("models/assimp/wolf/wolf.obj");
        
        auto wolfDrawable = std::make_shared<Drawable3DObject>(
            wolfModel, 
            shader_phong, 
            Transformation(), 
            *materialManager.getMaterial("wolf"),
            nullptr
        );

        auto& trans = wolfDrawable->getTransformation();

        auto translateOp = std::make_shared<TranslateOperation>(
            glm::vec3(getRandom(-15.0f, 15.0f), 0.0f, getRandom(-15.0f, 15.0f))
        );
        trans.addOperation(translateOp);

        auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(1.4f));
        trans.addOperation(scaleOp);

        auto rotateOp = std::make_shared<RotateOperation>(
            glm::radians(getRandom(0.0f, 360.0f)),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        trans.addOperation(rotateOp);

        drawable3DObjects.push_back(wolfDrawable);
    }

    auto loginModel = std::make_shared<Object>("models/assimp/login/login.obj");

    auto loginDrawable = std::make_shared<Drawable3DObject>(
        loginModel, 
        shader_lambert, 
        Transformation(), 
        *materialManager.getMaterial("login"),
        nullptr
    );

    auto& loginTrans = loginDrawable->getTransformation();
    loginTrans.addOperation(std::make_shared<TranslateOperation>(glm::vec3(0.0f, 10.0f, -15.0f)));
    loginTrans.addOperation(std::make_shared<ScaleOperation>(glm::vec3(0.2f))); 

    drawable3DObjects.push_back(loginDrawable);
}

float Scene7::getRandom(float min, float max) {
    return min + static_cast<float>(std::rand()) / 
                (static_cast<float>(RAND_MAX / (max - min)));
}

void Scene7::addLight(const Light& light) {
    lights.push_back(light);
}

const std::vector<Light>& Scene7::getLights() const {
    return lights;
}

void Scene7::render(float dt) {
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();

    for (const auto& drawable3D : drawable3DObjects) {
        drawable3D->render(view, projection);
    }

    glm::vec3 spotlightPos = camera.getPosition();
    glm::vec3 spotlightDir = glm::normalize(camera.getFront());
    spotlight->update(spotlightPos, spotlightDir);

    for (auto& shader : shaders) {
        spotlight->applyToShader(shader);
    }

    Scene::render(dt);
}