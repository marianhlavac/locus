//
//  Window.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.hpp"

/// Basic window class
class Window {
public:
    Window(int width, int height);

    /// Gets GLFW window object.
    GLFWwindow* getWindow();

    /// Attached scene to the window, which is going to be drawn.
    /// \param scene Scene to be attached.
    void attachScene(Scene* scene);

    /// Gets attached scene to the window.
    Scene* getAttachedScene();

    /// Activate procedure. Enables all needed GL properties.
    void activate();

    /// Clears the window and makes it ready for drawing.
    void beginDraw();

    /// Swaps the buffers, displaying drawings in the window.
    void endDraw();

    /// Has been the window closed?
    bool hasBeenClosed();

    /// Window width.
    int getWidth();

    /// Window height.
    int getHeight();
private:
    int width;
    int height;
    GLFWwindow* window;
    Scene* scene;
};

#endif /* Window_hpp */
