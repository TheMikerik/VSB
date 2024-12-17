#include "Scenes/Scene8.h"
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

Scene8::Scene8(Camera& cam) 
    : camera(cam)
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    auto materialManager = MaterialManager::getInstance();

    glm::vec3 position = glm::vec3( 0.0f,  0.0f,  0.0f);
    glm::vec3 color = glm::vec3(1.0f);
    this->addLight(Light(position, color));

    auto shader_texture = std::make_shared<ShaderProgram>(
        "./shaders/texture_shaders/vertex_shader.glsl",
        "./shaders/texture_shaders/fragment_shader.glsl"
    );

    shaders = {shader_texture};

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







    std::vector<glm::vec3> spherePositions = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3(-5.0f,  5.0f,  0.0f),
        glm::vec3( 6.0f, -6.0f,  0.0f),
    };

    for (int i = 0; i < 3; ++i) {
        auto planetModel = std::make_shared<Object>("models/assimp/planet/planet.obj");
        
        if (i == 0) {

          auto planetDrawable = std::make_shared<Drawable3DObject>(
              planetModel, 
              shader_texture, 
              Transformation(), 
              *materialManager.getMaterial("sun"),
              std::make_shared<Texture>("models/assimp/planet/sun.png")
          );

          auto& trans = planetDrawable->getTransformation();

          auto translateOp = std::make_shared<TranslateOperation>(glm::vec3( 0.0f,  0.0f,  0.0f));
          trans.addOperation(translateOp);

          auto scaleOp = std::make_shared<ScaleOperation>(
              glm::vec3(3.0f)
          );
          trans.addOperation(scaleOp);

          planetsDrawables.push_back(planetDrawable);


        } else if (i == 1){

          auto planetDrawable = std::make_shared<Drawable3DObject>(
              planetModel, 
              shader_texture, 
              Transformation(), 
              *materialManager.getMaterial("earth"),
              std::make_shared<Texture>("models/assimp/planet/earth.png")
          );

          auto& trans = planetDrawable->getTransformation();

          auto translateOp = std::make_shared<TranslateOperation>(glm::vec3(2.5f,  0.0f,  2.5f));
          trans.addOperation(translateOp);

          auto scaleOp = std::make_shared<ScaleOperation>(
              glm::vec3(1.0f)
          );
          trans.addOperation(scaleOp);

          planetsDrawables.push_back(planetDrawable);



        } else {

          auto planetDrawable = std::make_shared<Drawable3DObject>(
              planetModel, 
              shader_texture, 
              Transformation(), 
              *materialManager.getMaterial("moon"),
              std::make_shared<Texture>("models/assimp/planet/moon.png")
          );

          auto& trans = planetDrawable->getTransformation();

          auto translateOp = std::make_shared<TranslateOperation>(glm::vec3( 0.0f, 0.0f,  0.0f));
          trans.addOperation(translateOp);

          auto scaleOp = std::make_shared<ScaleOperation>(
              glm::vec3(0.5f)
          );
          trans.addOperation(scaleOp);

          planetsDrawables.push_back(planetDrawable);

        }
    }







}

float Scene8::getRandom(float min, float max) {
    return min + static_cast<float>(std::rand()) / 
                (static_cast<float>(RAND_MAX / (max - min)));
}

void Scene8::addLight(const Light& light) {
    lights.push_back(light);
}

const std::vector<Light>& Scene8::getLights() const {
    return lights;
}

void Scene8::render(float dt) {
  glm::mat4 view = camera.GetViewMatrix();
  glm::mat4 projection = camera.getProjectionMatrix();
  
  for( int i = 0; i < 3; i++ ) {
    auto& planet = planetsDrawables[i];

    if (i == 0) {
      auto trans = planet->getTransformation();
      auto rotateOp = std::make_shared<RotateOperation>(dt * 50, glm::vec3(1.0f, 1.0f, 0.0f));
      trans.addOperation(rotateOp);
      planet->setTransformation(trans);

      planet->render(view, projection);
    } else if (i == 1) {
      auto trans = planet->getTransformation();

      float radius = 1.0f;
      float angle = dt ;
      auto translateOp = std::make_shared<TranslateOperation>(glm::vec3(
        radius * cos(angle), 
        0.0f, 
        radius * sin(angle)
      ));
      trans.addOperation(translateOp);

      auto rotateOp = std::make_shared<RotateOperation>(dt * 200, glm::vec3(0.0f, 1.0f, 0.0f));
      trans.addOperation(rotateOp);

      planet->setTransformation(trans);
      planet->render(view, projection);
    } else {
      auto trans = planet->getTransformation();

      float radius = 0.5f;
      float angle = dt ;
      auto translateOp = std::make_shared<TranslateOperation>(glm::vec3(
        radius * cos(angle), 
        0.0f, 
        radius * sin(angle)
      ));
      trans.addOperation(translateOp);

      auto rotateOp = std::make_shared<RotateOperation>(dt * 200, glm::vec3(0.0f, 1.0f, 0.0f));
      trans.addOperation(rotateOp);
      planet->setTransformation(trans);

      planet->render(view, projection);
    }
  }
}