// Scene5.cpp
#include "Scenes/Scene5.h"
#include "Graphics/Light.h"

#include "../models/bushes.h"
#include "../models/tree.h"
#include "../models/platform.h"
#include "../models/gift.h"
#include "../models/sphere.h"
#include "../models/suzi_flat.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

Scene5::Scene5(Camera& cam, Light& pl) : camera(cam), pointLight(pl) {
    std::srand(static_cast<unsigned int>(std::time(0)));

    // setBackgroundColor(glm::vec4(0.59f, 0.76f, 0.92f, 1.0f));

    auto shader_uni = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    camera.registerObserver(shader_uni.get());
    pointLight.registerObserver(shader_uni.get());

    auto shader_pl = std::make_shared<ShaderProgram>("./shaders/vertex_shader_pl.glsl", "./shaders/fragment_shader_pl.glsl");
    auto shader_phong = std::make_shared<ShaderProgram>("./shaders/phong/vertex_phong.glsl", "./shaders/phong/fragment_phong.glsl");
    auto shader_lambert = std::make_shared<ShaderProgram>("./shaders/lambert/vertex_lambert.glsl", "./shaders/lambert/fragment_lambert.glsl");
    auto shader_blinn = std::make_shared<ShaderProgram>("./shaders/blinn/vertex_blinn.glsl", "./shaders/blinn/fragment_blinn.glsl");

    shaders = {shader_pl, shader_phong, shader_lambert, shader_blinn};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
        pointLight.registerObserver(shader.get());
    }

    pointLight.notifyObservers();
    camera.notifyObservers();

    // std::vector<float> bushesVertices(std::begin(bushes), std::end(bushes));
    // std::vector<float> treeVertices(std::begin(tree), std::end(tree));
    std::vector<float> platformVertices(std::begin(platform), std::end(platform));
    // std::vector<float> giftVertices(std::begin(gift), std::end(gift));
    std::vector<float> sphereVertices(std::begin(sphere), std::end(sphere));
    // std::vector<float> suziVertices(std::begin(suziFlat), std::end(suziFlat));

    // auto bushesModel = std::make_shared<Model>(bushesVertices);
    // auto treeModel = std::make_shared<Model>(treeVertices);
    auto platformModel = std::make_shared<Model>(platformVertices);
    // auto giftModel = std::make_shared<Model>(giftVertices);
    auto sphereModel = std::make_shared<Model>(sphereVertices);
    // auto suziModel = std::make_shared<Model>(suziVertices);

    // Platform
    auto platformDrawable = std::make_shared<DrawableObject>(platformModel, shader_uni);
    addDrawable(platformDrawable);

    // // Bushes
    // for (int i = 0; i < 100; ++i) {
    //     auto randomShader = shaders[i % shaders.size()];
    //     auto bushesDrawable = std::make_shared<DrawableObject>(bushesModel, randomShader);

    //     Transformation bushesTrans;
    //     bushesTrans.translate(glm::vec3(
    //         getRandom(-15.0f, 15.0f),
    //         0.0f,
    //         getRandom(-15.0f, 15.0f)
    //     ));
    //     bushesTrans.rotate(getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //     bushesTrans.scale(glm::vec3(getRandom(1.0f, 3.0f)));
    //     bushesDrawable->setTransformation(bushesTrans);

    //     addDrawable(bushesDrawable);
    // }

    // // Trees
    // for (int i = 0; i < 100; ++i) {
    //     auto randomShader = shaders[i % shaders.size()];
    //     auto treeDrawable = std::make_shared<DrawableObject>(treeModel, randomShader);

    //     Transformation treeTrans;
    //     treeTrans.translate(glm::vec3(
    //         getRandom(-15.0f, 15.0f),
    //         0.0f,
    //         getRandom(-15.0f, 15.0f)
    //     ));
    //     treeTrans.rotate(getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //     treeTrans.scale(glm::vec3(getRandom(0.2f, 0.8f)));
    //     treeDrawable->setTransformation(treeTrans);

    //     addDrawable(treeDrawable);
    // }

    // // Gifts
    // for (int i = 0; i < 100; ++i) {
    //     auto randomShader = shaders[i % shaders.size()];
    //     auto giftDrawable = std::make_shared<DrawableObject>(giftModel, randomShader);

    //     Transformation giftTrans;
    //     giftTrans.translate(glm::vec3(
    //         getRandom(-15.0f, 15.0f),
    //         0.0f,
    //         getRandom(-15.0f, 15.0f)
    //     ));
    //     giftTrans.rotate(getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //     giftTrans.scale(glm::vec3(getRandom(0.2f, 1.8f)));
    //     giftDrawable->setTransformation(giftTrans);

    //     addDrawable(giftDrawable);
    // }

    // Spheres
    for (int i = 0; i < 100; ++i) {
        auto randomShader = shaders[i % shaders.size()];
        auto sphereDrawable = std::make_shared<DrawableObject>(sphereModel, randomShader);

        Transformation sphereTrans;
        sphereTrans.translate(glm::vec3(
            getRandom(-15.0f, 15.0f),
            getRandom(1.0f, 3.0f),
            getRandom(-15.0f, 15.0f)
        ));
        sphereTrans.rotate(getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        sphereTrans.scale(glm::vec3(getRandom(0.2f, 0.8f)));
        sphereDrawable->setTransformation(sphereTrans);

        addDrawable(sphereDrawable);
    }

    // Suzis
    // for (int i = 0; i < 20; ++i) {
    //     auto randomShader = shaders[i % shaders.size()];
    //     auto suziDrawable = std::make_shared<DrawableObject>(suziModel, randomShader);

    //     Transformation suziTrans;
    //     suziTrans.translate(glm::vec3(
    //         getRandom(-15.0f, 15.0f),
    //         getRandom(5.0f, 35.0f),
    //         getRandom(-15.0f, 15.0f)
    //     ));
    //     suziTrans.rotate(getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //     suziTrans.scale(glm::vec3(getRandom(0.2f, 2.0f)));
    //     suziDrawable->setTransformation(suziTrans);

    //     addDrawable(suziDrawable);
    // }
}

float Scene5::getRandom(float min, float max) {
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}