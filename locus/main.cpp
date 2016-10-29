#include <GL/glew.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>

#include <ctime>

#include "WavefrontParser.hpp"
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
//  - make pointers referencers and dereferencers consistent

using namespace glm;
using namespace std;

// ---

//
// init
//
void init(Window* window) {
    Scene* scene = new Scene("The Scene");
    window->attachScene(scene);
    
    Camera* camera = new Camera("Default Camera", vec3(0, 0, -1), vec3(0, 0, 0));
    scene->attachCamera(camera);
    
    // Add cone
    /*Mesh* meshCone = Mesh::loadFromFile(resourcePath() + "cone.obj", Material::solid());
    Object* obj = new Object(meshCone, "Cone", vec3(0, 0, -1), vec3(0), vec3(0.1f));
    scene->addChild(obj);*/
    
    Mesh* mesh = new Mesh(WavefrontParser::parse(resourcePath() + "Small Lamp.obj"), Material::solid());
    Object* obj = new Object(mesh, "Model", vec3(0, 0, 0), vec3(0), vec3(1));
    scene->addChild(obj);
}

//
// update
//
void update(Window* window, double timeElapsed) {
    Scene* sc = window->getAttachedScene();
    
    sc->getChildByName("Model")->setRotation(vec3(0, 0, timeElapsed));
}

// ---

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
        update(window, glfwGetTime());
        render(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
