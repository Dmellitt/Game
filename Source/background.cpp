//
//  background.cpp
//  Game
//
//  Created by David Mellitt on 10/28/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#include "background.hpp"

Background::Background(GLfloat _x, GLfloat _y) {
    x = _x;
    y = _y;
    w = 2;
    h = 2;
    uv = {
        0.0625*0,
        0.0625*3,
        0.0625*0,
        0.0625*3
    };
}
