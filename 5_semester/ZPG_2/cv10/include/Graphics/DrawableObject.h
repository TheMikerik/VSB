#pragma once

#include <memory>
#include <vector>

#include "Core/Model.h"
#include "Shaders/ShaderProgram.h"
#include "Core/Transformation.h"
#include "Core/Texture.h"

class DrawableObject {
public:
    DrawableObject(std::shared_ptr<Model> model,
                    std::shared_ptr<ShaderProgram> shaderProgram,
                    const Transformation& transformation = Transformation());

    void render() const;
    void setTransformation(const Transformation& trans);
    Transformation& getTransformation();
    void setShader(std::shared_ptr<ShaderProgram> shd);
    glm::vec3 getPosition() const;

    void addTexture(const std::shared_ptr<Texture>& texture,
                    GLuint unit = 0,
                    const std::string& uniform = "texture_diffuse1");
    void clearTextures();

    void setID(GLuint id);
    GLuint getID() const;
    void setSelected(bool selected);
    bool isSelected() const;

private:
    std::shared_ptr<Model> model;
    std::shared_ptr<ShaderProgram> shaderProgram;
    Transformation transformation;

    GLuint objectID;
    bool selected;

    struct TextureBinding {
        std::shared_ptr<Texture> texture;
        GLuint unit;
        std::string uniformName;
    };
    std::vector<TextureBinding> textures;
};