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

/// Scene graph class
class Scene : public Child {
public:
    Scene(string name);

    /// Attaches a camera to the scene. Making it active and looking through
    /// when rendering.
    void attachCamera(Camera* camera);

    /// Gets currently attached camera.
    Camera* getAttachedCamera();

    /// Adds a material to the scene. Saved to the material manager keeping all
    /// the materials updated with updateMaterials() method.
    void addMaterial(Material* material);

    /// Adds a directional light. Updates all lights in scene later with
    /// updateMaterials() method.
    void addDirectionalLight(DirectionalLight* light);

    /// Adds a point light. Updates all lights in scene later with
    /// updateMaterials() method.
    void addPointLight(PointLight* light);

    /// Adds a spot light. Updates all lights in scene later with
    /// updateMaterials() method.
    void addSpotLight(SpotLight* light);

    /// Updates all materials and its shaders with view, light and other positions,
    /// transformations, etc.
    void updateMaterials(float timeElapsed);

    /// Draws the whole scene.
    void draw();

    /// Draws the whole scene using specified forced material.
    void draw(Material* forcedMaterial);

    /// Currently hovered selection id. Gets currently hovered over object ID,
    /// that was set using Object::setSelectionId().
    int getHoverId(Material* selectionMaterial, int x, int y);

    /// Loads whole scene from scene JSON file.
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
