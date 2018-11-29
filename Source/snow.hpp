//
//  snow.hpp
//  Game
//
//  Created by David Mellitt on 11/3/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#ifndef snow_hpp
#define snow_hpp

#include "gameObject.hpp"

class Snow : public GameObject {
public:
    Snow(GLfloat _x, GLfloat _y, float, float);
    virtual bool update(float);
private:
    float vx, vy;
};

#endif /* snow_hpp */
