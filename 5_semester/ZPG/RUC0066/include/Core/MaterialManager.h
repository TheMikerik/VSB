#pragma once

#include <map>
#include <memory>
#include <string>
#include "Material.h"

class MaterialManager {
public:
    static MaterialManager& getInstance();

    std::shared_ptr<Material> getMaterial(const std::string& name);

    void addMaterial(const std::string& name, std::shared_ptr<Material> material);

private:
    MaterialManager();
    void initializeMaterials();

    std::map<std::string, std::shared_ptr<Material>> materials;
};