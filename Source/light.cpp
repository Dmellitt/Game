//
//  light.cpp
//  Game
//
//  Created by David Mellitt on 10/22/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#include "light.hpp"

Light::Light(GLfloat _x, GLfloat _y) {
    x = _x;
    y = _y;
    w = 2.3;
    h = 1.3;
    uv = {
        0.75,
        0.9999,
        0.75,
        0.9999
    };
}
