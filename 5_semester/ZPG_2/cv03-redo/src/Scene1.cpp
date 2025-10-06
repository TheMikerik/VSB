#include "Scene.h"
#include "DrawableObject.h"
#include "Model.h"
#include "ShaderProgram.h"
#include <memory>
#include <vector>
#include <iterator>

#include "../models/triangle.h"

Scene* createScene1() {
    Scene* scene = new Scene();

    std::vector<float> vertices(std::begin(triangle), std::end(triangle));
    auto model = std::make_shared<Model>(vertices);
    auto shader = std::make_shared<ShaderProgram>("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    DrawableObject tri(model, shader);
    scene->addDrawable(tri);

    return scene;
}