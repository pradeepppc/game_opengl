#include "main.h"

#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y , float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y , float z);
    void tick();
    double speedx;
    double speedy;
    double speedz;
    double leng;
    double g;
    float angle;
    bool is_active;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif
