#include "main.h"

#ifndef LAND_H

#define LAND_H

class Land {
public:
    Land() {}
    Land(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float leng;
    bounding_box_t bounding_box();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif
