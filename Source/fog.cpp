//
//  fog.cpp
//  Game
//
//  Created by David Mellitt on 10/31/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#include "fog.hpp"

Fog::Fog(GLfloat _x, GLfloat _y) {
    x = _x;
    y = _y;
    w = 0.12;
    h = 0.12;
    uv = {
        0.0625*0,
        0.0625*2,
        0.0625*13,
        0.0625*15
    };
}

bool Fog::update(float delta) {
    y += 0.07*delta;
    
    lifeTimer += delta;
    return lifeTimer < 1;
}
