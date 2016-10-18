
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

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



void init(Window* window) {
    Scene* scene = new Scene("The Scene");
    window->attachScene(scene);
    
    Mesh* mesh = Mesh::loadFromFile(resourcePath() + "cone.obj", Material::solid());
    Object* obj = new Object(mesh, sf::Vector3f(0, 0, 0), "Mesh");
    scene->addChild(obj);
}

void update(Window* window, sf::Time elapsed) {
    window->draw();
}

int main(int, char const**) {
    sf::Clock clock;
    
    Window *window = Window::createWindow(1366, 768);
    init(window);
    
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            // Close event
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window->close();
            }
        }
        
        update(window, clock.restart());
    }

    return EXIT_SUCCESS;
}
