#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
#include "Curve.hpp"
#include "Skybox.hpp"

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
    make_pair("animations", 1),
    make_pair("collisions", 1),
    make_pair("scene", 0),
    make_pair("camera", 1)
};

TextRenderer* fontFaceGravityBook24Renderer;
TextRenderer* fontFaceGravityRegular24Renderer;
TextRenderer* fontFaceGravityBold24Renderer;

Window* mainWindow;
Shader* text2Dshader;
Text2D* fps;
float fpsUpdateTimer = 0;
float clickTimeout = 0;
Material* selectionMaterial;
Material* graphic2Dmaterial;
Material* skyboxMaterial;
Graphic2D* loading;
Graphic2D* loadingProgress;
Graphic2D* cursor;
Text2D* loadingText;
GUI* gui;
Curve* testcurve;
Skybox* skybox;

int objHover = -1;

void loadingScreenRedraw(string statusText, float progress) {
    mainWindow->beginDraw();
    loading->draw();
    loadingText->setText(statusText);
    loadingText->draw();
    loadingProgress->setSize(vec2(progress * 250.0f, 2));
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
    
    testcurve = new Curve(vector<vec3> {
        vec3(-2, 3, 0), vec3(0, 2, 2), vec3(2, 2, 0), vec3(0, 3, -2)
    });
    
    // Load skybox textures
    vector<string> textFilenames = { resourcePath() + "Textures/skybox/right.jpg", resourcePath() + "Textures/skybox/left.jpg", resourcePath() + "Textures/skybox/top.jpg", resourcePath() + "Textures/skybox/bottom.jpg", resourcePath() + "Textures/skybox/back.jpg", resourcePath() + "Textures/skybox/front.jpg" };
    Texture* skyboxTexture = Texture::loadCubemap(textFilenames);
    skyboxMaterial->setTexture(skyboxTexture);
    skybox = new Skybox(50, skyboxMaterial);
    scene->addMaterial(skyboxMaterial);
    
    // Animated objects
    Mesh* animMesh = Mesh::createQuad(vec2(5,5));
    Material* animMat = Material::fromFile(resourcePath() + "Materials/Animated.mat");
    animMat->setAnimatedUnlitProps(4, 3.5f);
    scene->addMaterial(animMat);
    Object* anim = new Object(animMesh, "Animated", vec3(0, 2.32f, -6.6), vec3(radians(-90.0f), radians(180.0f), 0), vec3(0.45f, 1, 0.20f), animMat);
    anim->setSelectionId(2);
    scene->addChild(anim);
    
    Mesh* animCube = Mesh::createQuad(vec2(2,2));
    Material* animCubeMat = Material::fromFile(resourcePath() + "Materials/Moving.mat");
    scene->addMaterial(animCubeMat);
    Object* anim2 = new Object(animCube, "Animated2", vec3(0, 0.1f, 2), animCubeMat);
    scene->addChild(anim2);
    
    // Add secondary camera
    Camera* secondary = new Camera("Secondary Cam", vec3(0), vec3(0));
    Object* lc = ((Object*)scene->getChildByName("Light Cube"));
    lc->addChild(secondary);
    
    
    return scene;
}

//
// update()
//
void update(Window* window, double timeElapsed, double timeDelta) {
    Scene* sc = window->getAttachedScene();
    
    // camera update
    if (configuration["camera"] == 1) {
        FreeCamera* cam = (FreeCamera*)sc->getChildByName("Free Cam");
        sc->attachCamera(cam);
        cam->update(window, timeDelta);
        
        if (configuration["collisions"] == 1) {
            //cam->holdBoundaries(vec3(0, 2.5f, 0), vec3(10, 4, 14));
            cam->avoidBoundaries(vec3(0.07f, 0, -1.3f), vec3(2, 2, 2));
        }
    } else if (configuration["camera"] == 2) {
        Camera* cam = (Camera*)sc->getChildByName("Secondary Cam");
        sc->attachCamera(cam);
    } else if (configuration["camera"] == 0) {
        Camera* cam = (Camera*)sc->getChildByName("Primary Cam");
        sc->attachCamera(cam);
    }
    
    // update all materials
    sc->updateMaterials(configuration["animations"] == 1 ? timeElapsed : 0);
    
    // update fps meter
    if (fpsUpdateTimer <= 0) {
        fps->setText(to_string((int)(1 / timeDelta)));
        fpsUpdateTimer = 0.25f;
    }
    
    // --- animations
    if (configuration["animations"] == 1) {
        if (configuration["scene"] == 1) {
            Camera* cam = (Camera*)sc->getChildByName("Primary Cam");
            cam->setPosition(testcurve->calc(timeElapsed));
            cam->setRotation(toQuat(lookAt(vec3(0), testcurve->calcD(timeElapsed), vec3(0, 1, 0))));
        }
        
        float fireIntensity = abs(sin(timeElapsed)) * abs(cos(timeElapsed * 6.0f)) * abs(sin(timeElapsed * 12.0f)) * 0.125f + 0.2f;
        ((PointLight*)sc->getChildByName("Fire light"))->setColor(vec3(1.00f, 0.64f, 0.33f) * fireIntensity);
        
        Object* lc = ((Object*)sc->getChildByName("Light Cube"));
        Object* pl = ((Object*)sc->getChildByName("Rotating light"));
        vec3 lpos = vec3(sin(timeElapsed / 2.0f)*2.0f, 3.0, cos(timeElapsed / 2.0f)*2.0);
        lc->setPosition(lpos);
        pl->setPosition(lpos);
    }
    // ---
    
    // clicks on objects
    if (glfwGetMouseButton(window->getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && clickTimeout <= 0) {
        if (objHover == 1) {
            configuration["lights"] = configuration["lights"] == 0 ? 2 : 0;
            clickTimeout = 0.25f;
        } else if (objHover == 2) {
            configuration["animations"] = configuration["animations"] == 0 ? 1 : 0;
            clickTimeout = 0.25f;
        } else if (objHover == 3) {
            configuration["render"] = configuration["render"] == 0 ? 2 : 0;
            clickTimeout = 0.25f;
        }
    }
    
    
    fpsUpdateTimer -= timeDelta;
    clickTimeout -= timeDelta;
    
    gui->update(window, timeElapsed);
}

//
// render()
//
void render(Window* window) {
    // get hover object id
    objHover = window->getAttachedScene()->getHoverId(selectionMaterial, window->getWidth() / 2, window->getHeight() / 2);
    
    // render configuration
    if (configuration["render"] >= 1) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    } else {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }
    
    // draw the whole thing
    window->beginDraw();
    
    skybox->draw();
    
    window->getAttachedScene()->draw();
    gui->draw();
    fps->draw();
    
    if (objHover > 0 && objHover != 255) cursor->draw();
    
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
    skyboxMaterial = Material::fromFile(resourcePath() + "Materials/Skybox.mat");
    skyboxMaterial->setTextureType(Material::TEXTURE_CUBEMAP);
    
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
    loadingProgress = new Graphic2D(loadingProgressMat, vec2(511, 272), vec2(500, 1));
    loadingText = new Text2D("-", fontFaceGravityBold24Renderer, vec2(630, 235), vec3(1), 0.4f);
    loadingText->setAlign(Text2D::ALIGN_CENTER);
    loadingScreenRedraw("Initializing application...", 0.1f);
    
    // load cursor
    Texture* cursorTex = Texture::loadFromFile(resourcePath() + "Textures/cursor.png");
    Material* cursorMat = graphic2Dmaterial->clone();
    cursorMat->setTexture(cursorTex);
    cursor = new Graphic2D(cursorMat, vec2(608, 328), vec2(64, 64));
    
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
