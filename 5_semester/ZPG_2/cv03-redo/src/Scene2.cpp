#include "Scene.h"
#include "DrawableObject.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include <memory>
#include <vector>
#include <iterator>

#include "../models/bushes.h"
#include "../models/gift.h"
#include "../models/tree.h"

Scene* createScene2() {
    Scene* scene = new Scene();

    std::vector<float> bushVertices(std::begin(bushes), std::end(bushes));
    std::vector<float> giftVertices(std::begin(gift), std::end(gift));
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));

    auto bush = std::make_shared<Model>(bushVertices);
    auto gift = std::make_shared<Model>(giftVertices);
    auto tree = std::make_shared<Model>(treeVertices);

    auto shader = std::make_shared<ShaderProgram>("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    DrawableObject bushDr(bush, shader);
    DrawableObject giftDr(gift, shader);
    DrawableObject treeDr(tree, shader);

    for (int i = 0; i < 10; i++) {
        Transformation bushTrans;
        bushTrans.translate(glm::vec3(static_cast<float>(std::rand() % 200 - 100) / 100.0f, 
                                        static_cast<float>(std::rand() % 200 - 100) / 100.0f, 
                                        static_cast<float>(std::rand() % 200 - 100) / 100.0f));
        bushTrans.rotate(static_cast<float>(std::rand() % 360), glm::vec3(std::rand() % 2, std::rand() % 2, std::rand() % 2));
        bushTrans.scale(glm::vec3(static_cast<float>(std::rand() % 50) / 100.0f));
        bushDr.setTransformation(bushTrans);
        scene->addDrawable(bushDr);
        scene->addDrawable(giftDr);
        scene->addDrawable(treeDr);
    }

    return scene;
}