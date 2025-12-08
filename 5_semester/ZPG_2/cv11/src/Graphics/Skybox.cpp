#include "Graphics/Skybox.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Skybox::Skybox(const std::vector<std::string>& faces)
    : view(glm::mat4(1.0f)), projection(glm::mat4(1.0f))
{
    model = std::make_shared<Model>("skybox.obj");
    
    cubemapTexture = std::make_shared<Texture>(faces);
    
    shader = std::make_shared<ShaderProgram>(
        "./shaders/skybox_vertex.glsl",
        "./shaders/skybox_fragment.glsl"
    );
    
    shader->use();
    glUniform1i(glGetUniformLocation(shader->getProgramID(), "skybox"), 0);
    glUseProgram(0);
    
    std::cout << "Skybox initialized successfully" << std::endl;
}

void Skybox::render() const
{
    glDepthFunc(GL_LEQUAL);
    
    shader->use();
    
    GLint viewLoc = glGetUniformLocation(shader->getProgramID(), "view");
    GLint projLoc = glGetUniformLocation(shader->getProgramID(), "projection");
    
    if (viewLoc != -1) {
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    }
    if (projLoc != -1) {
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    }
    
    cubemapTexture->bind(0);
    
    model->bind();
    glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
    model->unbind();
    
    glUseProgram(0);
    
    glDepthFunc(GL_LESS);
}

void Skybox::onCameraUpdate(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    view = viewMatrix;
    projection = projectionMatrix;
}