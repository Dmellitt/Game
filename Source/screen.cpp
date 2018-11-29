//
//  screen.cpp
//  Game
//
//  Created by David Mellitt on 10/29/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#include "screen.hpp"

Screen::Screen(GLfloat _x, GLfloat _y) {
    x = _x;
    y = _y;
    w = 2;
    h = 2;
    uv = {
        0,
        1,
        0,
        1
    };
}
