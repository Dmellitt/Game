//
//  fog.hpp
//  Game
//
//  Created by David Mellitt on 10/31/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#ifndef fog_hpp
#define fog_hpp

#include "gameObject.hpp"

class Fog : public GameObject {
public:
    Fog(GLfloat _x, GLfloat _y);
    virtual bool update(float);
private:
    float lifeTimer = 0;
};

#endif /* fog_hpp */
