//
//  background.hpp
//  Game
//
//  Created by David Mellitt on 10/28/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#ifndef background_hpp
#define background_hpp

#include "gameObject.hpp"

class Background : public GameObject {
public:
    Background(GLfloat _x, GLfloat _y);
};

#endif /* background_hpp */
