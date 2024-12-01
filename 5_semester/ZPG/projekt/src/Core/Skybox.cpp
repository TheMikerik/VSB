// Core/Skybox.cpp
#include "Core/Skybox.h"
#include "../models/cubebox.h"  // Ensure this path is correct
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Skybox::Skybox(const std::vector<std::string>& faces) {
    // Initialize the cube model using your skycube data
    std::vector<float> cubeVertices(std::begin(skycube), std::end(skycube));
    skyboxModel = std::make_shared<SkyboxModel>(cubeVertices);

    // Load cubemap textures
    cubemapTexture = std::make_shared<Texture>(faces, true);

    // Initialize the shader program for the Skybox
    skyboxShader = std::make_shared<ShaderProgram>(
        "shaders/cubebox/vertex_cubebox.glsl",
        "shaders/cubebox/fragment_cubebox.glsl"
    );

    // Set the sampler to texture unit 0
    skyboxShader->use();
    glUniform1i(glGetUniformLocation(skyboxShader->getProgramID(), "UISky"), 0);
    glUseProgram(0); // Ensure the shader program is unbound
}

Skybox::~Skybox() {
    // Resources are managed by smart pointers
}

void Skybox::render(const glm::mat4& view, const glm::mat4& projection) {
    // Change depth function so skybox is rendered behind other objects
    glDepthFunc(GL_LEQUAL);

    // Disable face culling (optional)
    glDisable(GL_CULL_FACE);

    skyboxShader->use();

    // Remove translation from the view matrix
    glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view));

    // Set shader uniforms
    GLuint viewLoc = glGetUniformLocation(skyboxShader->getProgramID(), "viewMatrix");
    GLuint projLoc = glGetUniformLocation(skyboxShader->getProgramID(), "projectionMatrix");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewNoTranslation));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Scale uniform
    GLuint scaleLoc = glGetUniformLocation(skyboxShader->getProgramID(), "scale");
    glUniform1f(scaleLoc, 50.0f); // Set scale factor to 15

    // Bind the cubemap texture
    cubemapTexture->bind(0);

    // Render the cube
    skyboxModel->bind();
    glDrawArrays(GL_TRIANGLES, 0, skyboxModel->getVertexCount());
    skyboxModel->unbind();

    glUseProgram(0);

    // Re-enable face culling
    glEnable(GL_CULL_FACE);

    // Restore depth function
    glDepthFunc(GL_LESS);
}