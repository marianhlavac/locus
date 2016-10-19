#include <GL/glew.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Window.hpp"
#include "Scene.hpp"
#include "Object.hpp"
#include "ResourcePath.hpp"

//
// TODO:
//  - constantify all getters and setters and others.
//  - maybe move small utilities like MeshShader, MeshShaderProgram etc.?
//  - un-std::-ize everytings
//  - headers consistence and remove unnecessary
//

using namespace glm;
using namespace std;

void init(Window* window) {
    Scene* scene = new Scene("The Scene");
    window->attachScene(scene);
    
    Mesh* mesh = Mesh::loadFromFile(resourcePath() + "cone.obj", Material::solid());
    Object* obj = new Object(mesh, vec3(0, 0, 0), "Mesh");
    scene->addChild(obj);
}

void update() {
    
}

void render(Window* window) {
    window->draw();
    glfwPollEvents();
}

int main(int, char const**) {
    // Init GLFW
    if (!glfwInit()) {
        cerr << "Failed to init GLFW" << endl;
        return EXIT_FAILURE;
    }
    
    // Create new window
    Window *window = new Window(1366, 768);
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
        update();
        render(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
