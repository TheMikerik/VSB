#include "Core/Skybox.h"
#include "../models/cubebox.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Skybox::Skybox(const std::vector<std::string>& faces) {
    std::vector<float> cubeVertices(std::begin(skycube), std::end(skycube));
    skyboxModel = std::make_shared<SkyboxModel>(cubeVertices);

    cubemapTexture = std::make_shared<Texture>(faces, true);

    skyboxShader = std::make_shared<ShaderProgram>(
        "shaders/cubebox/vertex_cubebox.glsl",
        "shaders/cubebox/fragment_cubebox.glsl"
    );

    skyboxShader->use();
    glUniform1i(glGetUniformLocation(skyboxShader->getProgramID(), "UISky"), 0);
    glUseProgram(0);
}

Skybox::~Skybox() {
}

void Skybox::render(const glm::mat4& view, const glm::mat4& projection) {
    glDepthFunc(GL_LEQUAL);

    glDisable(GL_CULL_FACE);

    skyboxShader->use();

    glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view));

    GLuint viewLoc = glGetUniformLocation(skyboxShader->getProgramID(), "viewMatrix");
    GLuint projLoc = glGetUniformLocation(skyboxShader->getProgramID(), "projectionMatrix");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewNoTranslation));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLuint scaleLoc = glGetUniformLocation(skyboxShader->getProgramID(), "scale");
    glUniform1f(scaleLoc, 50.0f);

    cubemapTexture->bind(0);

    skyboxModel->bind();
    glDrawArrays(GL_TRIANGLES, 0, skyboxModel->getVertexCount());
    skyboxModel->unbind();

    glUseProgram(0);

    glEnable(GL_CULL_FACE);

    glDepthFunc(GL_LESS);
}