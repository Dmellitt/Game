//
//  snow.cpp
//  Game
//
//  Created by David Mellitt on 11/3/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#include "snow.hpp"

Snow::Snow(GLfloat _x, GLfloat _y, float _vx, float _vy) {
    x = _x;
    y = _y;
    w = 2;
    h = 2;
    uv = {
        0.0625*2,
        0.0625*6,
        0.0625*11,
        0.0625*15-0.001
    };
    
    vx = _vx;
    vy = _vy;
}

bool Snow::update(float delta) {
    y += vy*delta;
    x += vx*delta;
    
    while(y+h/2 < -1)
        y += 2*h;
    while(y-h/2 > 1)
        y -= 2*h;
    
    while(x+w/2 < -1)
        x += 2*w;
    while(x-w/2 > 1)
        x -= 2*w;
    
    return true;
}
