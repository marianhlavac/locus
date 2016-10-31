#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <iostream>

#include "WavefrontParser.hpp"
#include "Window.hpp"
#include "Scene.hpp"
#include "Object.hpp"
#include "ResourcePath.hpp"
#include "Camera.hpp"
#include "FreeCamera.hpp"

//
// TODO:
//  - constantify all getters and setters and others.
//  - maybe move small utilities like MeshShader, MeshShaderProgram etc.?
//  - un-std::-ize everytings
//  - headers consistence and remove unnecessary
//  - make pointers referencers and dereferencers consistent

using namespace glm;
using namespace std;

Camera* freeCamera = new FreeCamera("Default Free Camera", vec3(0, 0, -1));
Camera* topCamera = new Camera("Top Camera", vec3(0.1f, 10.0f, 0.0f), vec3(0.0f));
Camera* insideCamera = new Camera("Inside Camera", vec3(5.0f, 5.0f, 7.0f), vec3(0.0f));

// ---

//
// init
//
void init(Window* window) {
    Scene* scene = new Scene("The Scene");
    window->attachScene(scene);
    
    scene->attachCamera(insideCamera);
    
    Mesh* roomMesh = new Mesh(WavefrontParser::parse(resourcePath() + "Models/Room.obj"), Material::solid());
    Object* room = new Object(roomMesh, "Room", vec3(0, 0, 0));
    scene->addChild(room);
    
    Mesh* sofaMesh = new Mesh(WavefrontParser::parse(resourcePath() + "Models/Sofa.obj"), Material::solid());
    Object* sofa = new Object(sofaMesh, "Sofa", vec3(0, 0, 0));
    scene->addChild(sofa);
}

//
// update
//
void update(Window* window, double timeElapsed, double timeDelta) {
    Scene* sc = window->getAttachedScene();
    
    // camera sel
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_1) == GLFW_PRESS) {
        sc->attachCamera(topCamera);
    }
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_2) == GLFW_PRESS) {
        sc->attachCamera(insideCamera);
    }
    
    if (glfwGetKey(window->getWindow(), GLFW_KEY_3) == GLFW_PRESS) {
        sc->attachCamera(freeCamera);
    }
    
    // free camera update
    
    if (sc->getAttachedCamera() == freeCamera) {
        ((FreeCamera*)sc->getAttachedCamera())->update(window);
    }
    
}

// ---

void render(Window* window) {
    window->beginDraw();
    window->getAttachedScene()->draw();
    window->endDraw();
    glfwPollEvents();
}

int main(int, char const**) {
    double lastTime = glfwGetTime();
    
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
    
    glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Init application
    init(window);
    
    // Application loop, update then render
    while (!window->hasBeenClosed()) {
        double elapsed = glfwGetTime();
        
        update(window, elapsed, elapsed - lastTime);
        render(window);
        
        if (((int)(elapsed*100) % (int)50) == 0) cout << "FPS: " << 1 / (elapsed - lastTime) << endl;
        
        lastTime = elapsed;
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
