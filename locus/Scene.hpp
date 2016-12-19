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
#include <json/json.h>

using namespace std;

//! Scene graph class
class Scene : public Child {
public:
    Scene(string name);
    void attachCamera(Camera* camera);
    Camera* getAttachedCamera();
    void addMaterial(Material* material);
    void addDirectionalLight(DirectionalLight* light);
    void addPointLight(PointLight* light);
    void addSpotLight(SpotLight* light);
    void updateMaterials(float timeElapsed);
    void draw();
    int getHoverId(Material* selectionMaterial, int x, int y);
    static Scene* fromFile(const string & filename);
    static Scene* fromFile(const string & filename, void (*progress)(string, float));
private:
    static void addChildrenRecursivelyJSON(Child* parent, Json::Value children, map<string, Mesh*>& meshesDict, map<string, Material*>& matDic);
    Camera* camera;
    list<DirectionalLight*> directionalLights;
    list<PointLight*> pointLights;
    list<SpotLight*> spotLights;
    list<Material*> materials;
};

#endif /* Scene_hpp */
