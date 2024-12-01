#include "Core/MaterialManager.h"

MaterialManager& MaterialManager::getInstance() {
    static MaterialManager instance;
    return instance;
}

MaterialManager::MaterialManager() {
    initializeMaterials();
}

void MaterialManager::initializeMaterials() {
    addMaterial("blue", std::make_shared<Material>(
        glm::vec3(0.12f, 0.15f, 0.4f),
        glm::vec3(0.25f, 0.3f, 0.65f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        32.0f
    ));
    
    addMaterial("platform", std::make_shared<Material>(
        glm::vec3(0.6, 0.36, 0.12),
        glm::vec3(0.75f, 0.5f, 0.25f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        16.0f  
    ));

    addMaterial("house", std::make_shared<Material>(
        glm::vec3(0.4, 0.4, 0.4),
        glm::vec3(0.75f, 0.75f, 0.75f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        16.0f  
    ));

    addMaterial("login", std::make_shared<Material>(
        glm::vec3(0.5, 0.0, 0.5),
        glm::vec3(1.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 0.5f, 1.0f),
        32.0f  
    ));

    addMaterial("wolf", std::make_shared<Material>(
        glm::vec3(0.2f, 0.25f, 0.3f),
        glm::vec3(0.3f, 0.4f, 0.5f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        16.0f                       
    ));

    addMaterial("tree", std::make_shared<Material>(
        glm::vec3(0.12f, 0.4f, 0.12f),
        glm::vec3(0.25f, 0.65f, 0.25),
        glm::vec3(1.0f, 1.0f, 1.0f),
        32.0f
    ));

    addMaterial("tree-blueish", std::make_shared<Material>(
        glm::vec3(0.15f, 0.3f, 0.25f),
        glm::vec3(0.3f, 0.5f, 0.35f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        32.0f 
    ));

    addMaterial("tree-brownish", std::make_shared<Material>(
        glm::vec3(0.25f, 0.3f, 0.15f),
        glm::vec3(0.4f, 0.5f, 0.3f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        32.0f 
    ));

    addMaterial("light", std::make_shared<Material>(
        glm::vec3(0.1f, 0.1f, 0.1f),  
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        16.0f
    ));
}

std::shared_ptr<Material> MaterialManager::getMaterial(const std::string& name) {
    auto it = materials.find(name);
    if (it != materials.end()) {
        return it->second;
    }
    return nullptr;
}

void MaterialManager::addMaterial(const std::string& name, std::shared_ptr<Material> material) {
    materials[name] = material;
}