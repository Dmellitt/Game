//
//  guy.cpp
//  Game
//
//  Created by David Mellitt on 10/31/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#include "guy.hpp"
#include "fog.hpp"

Guy::Guy(GLfloat _x, GLfloat _y) {
    x = _x;
    y = _y;
    w = 0.5;
    h = 0.5;
    uv = {
        0.0001,
        0.0624,
        0.9376,
        0.9999
    };
}

void Guy::update(vector<GameObject*> &mg, float delta) {
    burstTime += delta;
    if(burstTime > 4-3.85*burst) {
        burst = !burst;
        burstTime = 0;
    }
    
    if(burst) {
        fogTime += delta;
        if(fogTime > 0.015) {
            mg.push_back(new Fog(x-0.005,y+0.08));
            fogTime = 0;
        }
    }
}

void Guy::control(bool buffer[255], float delta) {
    if(buffer['A'])
        x -= 0.5*delta;
    if(buffer['D'])
        x += 0.5*delta;
    if(buffer['W'])
        y += 0.5*delta;
    if(buffer['S'])
        y -= 0.5*delta;
}
