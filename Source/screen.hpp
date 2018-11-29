//
//  screen.hpp
//  Game
//
//  Created by David Mellitt on 10/29/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#ifndef screen_hpp
#define screen_hpp

#include "gameObject.hpp"

class Screen : public GameObject {
public:
    Screen(GLfloat _x, GLfloat _y);
};

#endif /* screen_hpp */
