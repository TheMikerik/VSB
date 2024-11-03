// Scene3.cpp
#include "../include/Scenes/Scene3.h"
#include "../models/sphere.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Scene3::Scene3(Camera& cam, Light& light) : camera(cam), pointLight(light) {
    auto shader_uni = std::make_shared<ShaderProgram>("./shaders/vertex_shader_pl.glsl", "./shaders/fragment_shader_pl.glsl");

    shaders = {shader_uni};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
        pointLight.registerObserver(shader.get());
    }

    pointLight.notifyObservers();
    camera.notifyObservers();

    // Original sphere has 6 floats per vertex (position:3 + color:3)
    // We will create a new array with normals: 9 floats per vertex (position:3 + color:3 + normal:3)
    std::vector<float> sphereVerticesWithNormals;

    for (size_t i = 0; i < sizeof(sphere)/sizeof(float); i += 6) {
        // Extract position
        float x = sphere[i];
        float y = sphere[i + 1];
        float z = sphere[i + 2];
        
        // Extract color
        float r = sphere[i + 3];
        float g = sphere[i + 4];
        float b = sphere[i + 5];
        
        // Calculate normal (normalized position vector)
        glm::vec3 pos(x, y, z);
        glm::vec3 normal = glm::normalize(pos);
        
        // Append position
        sphereVerticesWithNormals.push_back(x);
        sphereVerticesWithNormals.push_back(y);
        sphereVerticesWithNormals.push_back(z);
        
        // Append color
        sphereVerticesWithNormals.push_back(r);
        sphereVerticesWithNormals.push_back(g);
        sphereVerticesWithNormals.push_back(b);
        
        // Append normal
        sphereVerticesWithNormals.push_back(normal.x);
        sphereVerticesWithNormals.push_back(normal.y);
        sphereVerticesWithNormals.push_back(normal.z);
    }

    // Initialize the sphere model with vertices that include normals
    auto sphereModel = std::make_shared<Model>(sphereVerticesWithNormals);

    std::vector<glm::vec3> spherePositions = {
        glm::vec3( 2.0f,  2.0f,  0.0f),
        glm::vec3(-2.0f,  2.0f,  0.0f),
        glm::vec3( 2.0f, -2.0f,  0.0f),
        glm::vec3(-2.0f, -2.0f,  0.0f)
    };

    for(const auto& pos : spherePositions) {
        auto sphereDrawable = std::make_shared<DrawableObject>(sphereModel, shader_uni);

        Transformation sphereTrans;
        sphereTrans.scale(glm::vec3(3.0f));
        sphereTrans.translate(pos);

        sphereDrawable->setTransformation(sphereTrans);

        addDrawable(sphereDrawable);
    }
}