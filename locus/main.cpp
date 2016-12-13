#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <map>

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

map<string, int> configuration = {
    make_pair("render", 2),
    make_pair("lights", 2),
    make_pair("animation", 1)
};

TextRenderer* fontFaceGravityBook24Renderer;
TextRenderer* fontFaceGravityRegular24Renderer;
TextRenderer* fontFaceGravityBold24Renderer;

Window* mainWindow;
Shader* text2Dshader;
Text2D* fps;
float fpsUpdateTimer = 0;
Material* selectionMaterial;
Material* graphic2Dmaterial;
Graphic2D* loading;
Graphic2D* loadingProgress;
Text2D* loadingText;
GUI* gui;

int objHover = -1;

void loadingScreenRedraw(string statusText, float progress) {
    mainWindow->beginDraw();
    loading->draw();
    loadingText->setText(statusText);
    loadingText->draw();
    loadingProgress->setSize(vec2(progress * 250.0f, 3));
    loadingProgress->draw();
    mainWindow->endDraw();
    glfwPollEvents();
}

// ---

//
// init()
//
Scene* init(Window* window) {
    // create scene, load from json, attach
    Scene* scene = Scene::fromFile(resourcePath() + "Scenes/Scene.json",
                                   [] (string progress, float progressB) {
                                       loadingScreenRedraw(progress, progressB);
                                   });
    window->attachScene(scene);
    
    loadingScreenRedraw("Finishing...", 0.95f);
    
    // init fps meter
    fps = new Text2D("FPS", fontFaceGravityBook24Renderer, vec2(20, window->getHeight() - 20 - 24), vec3(1, 0.84f, 0), 1);
    
    // init gui
    gui = new GUI(fontFaceGravityRegular24Renderer, fontFaceGravityBold24Renderer, graphic2Dmaterial, &configuration);
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
    
    gui->update(window, timeElapsed);
}

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

// ---

int main(int, char const**) {
    double lastTime = glfwGetTime();
    
    // Init GLFW
    if (!glfwInit()) {
        cerr << "Failed to init GLFW" << endl;
        return EXIT_FAILURE;
    }
    
    // create new window
    Window *window = new Window(1280, 720);
    window->activate();
    mainWindow = window;
    
    // init GLEW
    glewExperimental = true;
    
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to init GLEW" << endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // prepare global resources
    selectionMaterial = Material::fromFile(resourcePath() + "Materials/Selection.mat");
    text2Dshader = Shader::fromFile(resourcePath() + "Shaders/Text2D.vert", resourcePath() + "Shaders/Text2D.frag");
    graphic2Dmaterial = Material::fromFile(resourcePath() + "Materials/Graphic2DBase.mat");
    
    // load fonts from resources
    fontFaceGravityBook24Renderer = new TextRenderer(resourcePath() + "Fonts/Gravity-Book.otf", 24, text2Dshader);
    fontFaceGravityRegular24Renderer = new TextRenderer(resourcePath() + "Fonts/Gravity-Regular.otf", 24, text2Dshader);
    fontFaceGravityBold24Renderer = new TextRenderer(resourcePath() + "Fonts/Gravity-Bold.otf", 24, text2Dshader);
    
    // draw loading screen
    Texture* loadingTex = Texture::loadFromFile(resourcePath() + "Textures/gui_loading.png");
    Material* loadingMat = graphic2Dmaterial->clone();
    loadingMat->setTexture(loadingTex);
    loading = new Graphic2D(loadingMat, vec2(0), vec2(1280, 720));
    Texture* loadingProgressTex = Texture::loadFromFile(resourcePath() + "Textures/gui_loading_progressbar.png");
    Material* loadingProgressMat = graphic2Dmaterial->clone();
    loadingProgressMat->setTexture(loadingProgressTex);
    loadingProgress = new Graphic2D(loadingProgressMat, vec2(511, 271), vec2(500, 1));
    loadingText = new Text2D("-", fontFaceGravityBold24Renderer, vec2(630, 235), vec3(1), 0.4f);
    loadingText->setAlign(Text2D::ALIGN_CENTER);
    loadingScreenRedraw("Initializing application...", 0.1f);
    
    // init application
    Scene* scene = init(window);
    
    scene->addMaterial(selectionMaterial);
    
    // application loop, update then render
    while (!window->hasBeenClosed()) {
        double elapsed = glfwGetTime();
        
        update(window, elapsed, elapsed - lastTime);
        render(window);
        
        lastTime = elapsed;
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
