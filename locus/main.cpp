#include <GL/glew.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>

#include <ctime>

#include "Window.hpp"
#include "Scene.hpp"
#include "Object.hpp"
#include "ResourcePath.hpp"
#include "Camera.hpp"

//
// TODO:
//  - constantify all getters and setters and others.
//  - maybe move small utilities like MeshShader, MeshShaderProgram etc.?
//  - un-std::-ize everytings
//  - headers consistence and remove unnecessary
//

using namespace glm;
using namespace std;

float kek = 0.0f;

void init(Window* window) {
    Scene* scene = new Scene("The Scene");
    window->attachScene(scene);
    
    Camera* camera = new Camera("Default Camera", vec3(0, 0, 0), vec3(0));
    scene->attachCamera(camera);
    
    // Add cone
    Mesh* meshCone = Mesh::loadFromFile(resourcePath() + "cone.obj", Material::solid());
    Object* obj = new Object(meshCone, "Cone", vec3(0.5f, 0, 0), vec3(0), vec3(0));
    scene->addChild(obj);
    
    // Add donut
    Mesh* meshDonut = Mesh::loadFromFile(resourcePath() + "donut.obj", Material::solid());
    Object* obj2 = new Object(meshDonut, "Donut", vec3(-0.5f, 0, 0), vec3(0), vec3(0));
    scene->addChild(obj2);
}

void update(Window* window) {
    Scene* sc = window->getAttachedScene();
    
    // Rotate cone
    Object* obj = sc->getChildByName("Cone");
    obj->setRotation(vec3(kek, kek, kek));
    
    // Rotate donut
    Object* obj2 = sc->getChildByName("Donut");
    obj2->setRotation(vec3(kek, kek, kek));
    
    kek += 0.01f;
}

void render(Window* window) {
    window->beginDraw();
    window->getAttachedScene()->draw();
    window->endDraw();
    glfwPollEvents();
}

int main(int, char const**) {
    // Init GLFW
    if (!glfwInit()) {
        cerr << "Failed to init GLFW" << endl;
        return EXIT_FAILURE;
    }
    
    // Create new window
    Window *window = new Window(1280, 720);
    window->activate();
    
    // Init GLEW
    glewExperimental = true;
    
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to init GLEW" << endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    // Init application
    init(window);
    
    // Application loop, update then render
    while (!window->hasBeenClosed()) {
        update(window);
        render(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
