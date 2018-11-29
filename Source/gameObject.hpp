//
//  square.hpp
//  Game
//
//  Created by David Mellitt on 10/22/18.
//  Copyright © 2018 David Mellitt. All rights reserved.
//

#ifndef square_hpp
#define square_hpp

#include <GL/glew.h>
#include <vector>
using std::vector;

struct uv_t {
    GLfloat l, r, b, t;
};

class GameObject {
public:
    void buffer(vector<GLfloat>&, vector<GLfloat>&);
    virtual bool update(float) {return true;};
protected:
    GLfloat x, y, w, h;
    uv_t uv;
};

#endif /* square_hpp */
