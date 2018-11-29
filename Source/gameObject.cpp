//
//  square.cpp
//  Game
//
//  Created by David Mellitt on 10/22/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#include "gameObject.hpp"

void GameObject::buffer(vector<GLfloat> &vertices, vector<GLfloat> &uvs) {
    GLfloat l = x-w/2, r = x+w/2, b = y-h/2, t = y+h/2;
    
    if(l > 1 || r < -1 || b > 1 || t < -1)
        return;
    
    vertices.push_back(l);
    vertices.push_back(t);
    vertices.push_back(l);
    vertices.push_back(b);
    vertices.push_back(r);
    vertices.push_back(b);
    
    vertices.push_back(l);
    vertices.push_back(t);
    vertices.push_back(r);
    vertices.push_back(t);
    vertices.push_back(r);
    vertices.push_back(b);
    
    uvs.push_back(uv.l);
    uvs.push_back(uv.t);
    uvs.push_back(uv.l);
    uvs.push_back(uv.b);
    uvs.push_back(uv.r);
    uvs.push_back(uv.b);
    
    uvs.push_back(uv.l);
    uvs.push_back(uv.t);
    uvs.push_back(uv.r);
    uvs.push_back(uv.t);
    uvs.push_back(uv.r);
    uvs.push_back(uv.b);
}
