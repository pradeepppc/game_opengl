#include "main.h"

#ifndef BARREL_H
#define BARREL_H


class Barrel {
public:
    Barrel() {}
    Barrel(float x, float y , float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y , float z);
    void tick();
    double speed;
    double length;
    bounding_box_t bounding_box();
private:

    VAO *object;
    VAO *object1;
};

#endif // BALL_H
