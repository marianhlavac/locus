#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <iostream>

#include <json/json.h>

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

Camera* freeCamera = new FreeCamera("Default Free Camera", vec3(0), vec3(0));
Camera* topCamera = new Camera("Top Camera", vec3(0.1f, 10.0f, 0.0f), vec3(0, 0, 0));
Camera* insideCamera = new Camera("Inside Camera", vec3(0.0f, 0.0f, 0.0f), vec3(0, 0, 0));

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
    Object* sofa = new Object(sofaMesh, "Sofa", vec3(-4.6f, 0, -3.0f), vec3(0, radians(90.0f), 0));
    scene->addChild(sofa);
    
    Mesh* tableMesh = new Mesh(WavefrontParser::parse(resourcePath() + "Models/Living Room Table.obj"), Material::solid());
    Object* table = new Object(tableMesh, "Living Room Table", vec3(0.0f, 0, -3.0f), vec3(0));
    scene->addChild(table);
    
    Mesh* stableMesh = new Mesh(WavefrontParser::parse(resourcePath() + "Models/Small Table.obj"), Material::solid());
    Object* smallTable = new Object(stableMesh, "Small Table", vec3(-4.95f, 0, 0.5f), vec3(0, radians(90.0f), 0));
    scene->addChild(smallTable);
    
    Mesh* tvStandMesh = new Mesh(WavefrontParser::parse(resourcePath() + "Models/TV stand.obj"), Material::solid());
    Object* tvStand = new Object(tvStandMesh, "TV Stand", vec3(5.1f, 0, -3.0f), vec3(0, radians(-90.0f), 0));
    scene->addChild(tvStand);
    
    Mesh* tvMesh = new Mesh(WavefrontParser::parse(resourcePath() + "Models/TV.obj"), Material::solid());
    Object* tv = new Object(tvMesh, "TV", vec3(5.1f, 0.8f, -3.0f), vec3(0, radians(-90.0f), 0));
    scene->addChild(tv);
    
    Mesh* fenceMesh = new Mesh(WavefrontParser::parse(resourcePath() + "Models/Terrace fence.obj"), Material::solid());
    Object* fence = new Object(fenceMesh, "Terrace fence", vec3(8.1f, 0.0f, 3.75f), vec3(0, radians(-90.0f), 0));
    scene->addChild(fence);
    
    Mesh* windowMesh = new Mesh(WavefrontParser::parse(resourcePath() + "Models/Window.obj"), Material::solid());
    Object* window1 = new Object(windowMesh, "Window", vec3(6.15f, 0.0f, 3.95f), vec3(0, radians(-90.0f), 0));
    scene->addChild(window1);
    Object* window2 = new Object(windowMesh, "Window (2)", vec3(5.9f, 0.0f, 1.5f), vec3(0, radians(-90.0f), 0));
    scene->addChild(window2);
    Object* window3 = new Object(windowMesh, "Window (3)", vec3(5.9f, 0.0f, 6.4f), vec3(0, radians(-90.0f), 0));
    scene->addChild(window3);
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
        Camera* attached = sc->getAttachedCamera();
        
        /*if (attached != freeCamera) {
            freeCamera->setPosition(attached->getPosition());
            freeCamera->setView(attached->getView());
        }*/
        
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
