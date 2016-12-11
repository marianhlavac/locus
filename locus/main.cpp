#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <iostream>
#include <string>

#include "WavefrontParser.hpp"
#include "Window.hpp"
#include "Scene.hpp"
#include "Object.hpp"
#include "ResourcePath.hpp"
#include "Camera.hpp"
#include "FreeCamera.hpp"
#include "PointLight.hpp"
#include "Text2D.hpp"
#include "GUI.hpp"

//
// TODO:
//  - constantify all getters and setters and others.
//  - un-std::-ize everytings
//  - headers consistence and remove unnecessary
//  - make pointers referencers and dereferencers consistent

using namespace glm;
using namespace std;

TextRenderer* fontFaceGravityBook24Renderer;
TextRenderer* fontFaceGravityRegular24Renderer;
TextRenderer* fontFaceGravityBold24Renderer;

Shader* text2Dshader;
Text2D* fps;
float fpsUpdateTimer = 0;
Material* selectionMaterial;
GUI* gui;

int objHover = -1;

// ---

//
// init()
//
Scene* init(Window* window) {
    // create scene, load from json, attach
    Scene* scene = Scene::fromFile(resourcePath() + "Scenes/Scene.json");
    window->attachScene(scene);
    
    // load fonts from resources
    fontFaceGravityBook24Renderer = new TextRenderer(resourcePath() + "Fonts/Gravity-Book.otf", 24, text2Dshader);
    fontFaceGravityRegular24Renderer = new TextRenderer(resourcePath() + "Fonts/Gravity-Regular.otf", 24, text2Dshader);
    fontFaceGravityBold24Renderer = new TextRenderer(resourcePath() + "Fonts/Gravity-Bold.otf", 24, text2Dshader);
    
    // init fps meter
    fps = new Text2D("FPS", fontFaceGravityBook24Renderer, vec2(20, window->getHeight() - 20 - 24), vec3(1, 0.84f, 0), 1);
    
    // init gui
    Material* graphic2Dmaterial = Material::fromFile(resourcePath() + "Materials/Graphic2DBase.mat");
    gui = new GUI(fontFaceGravityRegular24Renderer, fontFaceGravityBold24Renderer, graphic2Dmaterial);
    gui->init(resourcePath() + "Textures/gui_navigation.png");
    
    return scene;
}

//
// update()
//
void update(Window* window, double timeElapsed, double timeDelta) {
    Scene* sc = window->getAttachedScene();
    
    // free camera update
    if (sc->getAttachedCamera()->getName() == "Free Camera") {
        ((FreeCamera*)sc->getAttachedCamera())->update(window, timeDelta);
    }
    
    // update all materials
    sc->updateMaterials();
    
    // update fps meter
    if (fpsUpdateTimer <= 0) {
        fps->setText(to_string((int)(1 / timeDelta)));
        fpsUpdateTimer = 0.25f;
    }
    
    fpsUpdateTimer -= timeDelta;
}

// ---

//
// render()
//
void render(Window* window) {
    // get hover object id
    objHover = window->getAttachedScene()->getHoverId(selectionMaterial, window->getWidth() / 2, window->getHeight() / 2);
    
    // draw the whole thing
    window->beginDraw();
    
    window->getAttachedScene()->draw();
    gui->draw();
    fps->draw();
    
    window->endDraw();
    
    // poll for events
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
    
    // Prepare global resources
    selectionMaterial = Material::fromFile(resourcePath() + "Materials/Selection.mat");
    text2Dshader = Shader::fromFile(resourcePath() + "Shaders/Text2D.vert", resourcePath() + "Shaders/Text2D.frag");
    
    // Init application
    Scene* scene = init(window);
    
    scene->addMaterial(selectionMaterial);
    
    // Application loop, update then render
    while (!window->hasBeenClosed()) {
        double elapsed = glfwGetTime();
        
        update(window, elapsed, elapsed - lastTime);
        render(window);
        
        lastTime = elapsed;
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
