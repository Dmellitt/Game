//
//  guy.hpp
//  Game
//
//  Created by David Mellitt on 10/31/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#ifndef guy_hpp
#define guy_hpp

#include "gameObject.hpp"

class Guy : public GameObject {
public:
    Guy(GLfloat _x, GLfloat _y);
    void control(bool[255], float);
    void update(vector<GameObject*>&, float);
private:
    float burstTime = 0;
    float fogTime = 0;
    bool burst = false;
};

#endif /* guy_hpp */
