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

// ---

//
// init
//
void init(Window* window) {
    Scene* scene = new Scene("The Scene");
    window->attachScene(scene);
    
    Camera* camera = new FreeCamera("Default Free Camera", vec3(0, 0, -1));
    scene->attachCamera(camera);
    
    Mesh* mesh = new Mesh(WavefrontParser::parse(resourcePath() + "untitled.obj"), Material::solid());
    Object* obj = new Object(mesh, "Model", vec3(0, 0, 0), vec3(0), vec3(0.25f));
    scene->addChild(obj);
}

//
// update
//
void update(Window* window, double timeElapsed, double timeDelta) {
    Scene* sc = window->getAttachedScene();
    
    ((FreeCamera*)sc->getAttachedCamera())->update(window);  
    
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
