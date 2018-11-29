//
//  floater.cpp
//  Game
//
//  Created by David Mellitt on 11/13/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#include "floater.hpp"
#include <math.h>

Floater::Floater(GLfloat _x, GLfloat _y, float _vx, float _vy) {
    x = _x;
    y = _y;
    w = 0.03;
    h = 0.07;
    uv = {
        0.0625*1,
        0.0625*2,
        0.0625*15,
        0.0625*16
    };
    
    vx = _vx;
    vy = _vy;
    
    lifeTimer = rand()%100;
}

bool Floater::update(float delta) {
    lifeTimer += delta;
    if(lifeTimer > 30*M_PI)
        lifeTimer -= 30*M_PI;
    
    w = abs(0.03*sin(lifeTimer));
    
    y += vy*delta;
    x += vx*delta;
    
    if(y+h/2 < -1)
        y += 4/1.9;
    if(y-h/2 > 1)
        y -= 4/1.9;
    
    if(x+0.015 < -1)
        x += 2.4;
    if(x-0.015 > 1)
        x -= 2.4;
    
    
    return true;
}
