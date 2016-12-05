//
//  Scene.hpp
//  locus
//
//  Created by Marián Hlaváč on 11/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <string>
#include <list>

#include "Object.hpp"
#include "Camera.hpp"
#include "Material.hpp"

#include "Child.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"

using namespace std;

class Scene : public Child {
public:
    Scene(string name);
    void attachCamera(Camera* camera);
    Camera* getAttachedCamera();
    void addMaterial(Material* material);
    void addDirectionalLight(DirectionalLight* light);
    void addPointLight(PointLight* light);
    void addSpotLight(SpotLight* light);
    void updateMaterials();
    void draw();
    static Scene* fromFile(const string & filename);
private:
    Camera* camera;
    list<DirectionalLight*> directionalLights;
    list<PointLight*> pointLights;
    list<SpotLight*> spotLights;
    list<Material*> materials;
};

#endif /* Scene_hpp */
