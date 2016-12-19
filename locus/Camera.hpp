//
//  Camera.hpp
//  locus
//
//  Created by Marián Hlaváč on 04/10/2016.
//  Copyright © 2016 majko. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Object.hpp"

#include <glm/glm.hpp>

using namespace glm;

/// Camera object
class Camera : public Object {
public:
    Camera(string name, vec3 position, vec3 rotation);

    /// Returns view matrix (V in MVP).
    virtual mat4 getViewMatrix();

    /// Returns projection matrix (P in MVP).
    mat4 getProjectionMatrix();

    /// Holds boundaries of camera position. Holds boundaries specified with
    /// arguments, that way the user using the free camera can't leave specified boundaries.
    /// \param center The center of boundary box
    /// \param size Actual size of boundary box
    void holdBoundaries(vec3 center, vec3 size);
    
    /// Avoids camera to be in boundaries. Inverse function of holdBoundaries().
    /// \param center The center of boundary box
    /// \param size Actual size of boundary box
    void avoidBoundaries(vec3 center, float size);
protected:
};

#endif /* Camera_hpp */
