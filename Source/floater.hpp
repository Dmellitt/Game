//
//  floater.hpp
//  Game
//
//  Created by David Mellitt on 11/13/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#ifndef floater_hpp
#define floater_hpp

#include "gameObject.hpp"

class Floater : public GameObject {
public:
    Floater(GLfloat _x, GLfloat _y, float, float);
    virtual bool update(float);
private:
    float vx, vy, lifeTimer;
};

#endif /* floater_hpp */
