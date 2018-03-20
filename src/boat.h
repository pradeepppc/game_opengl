#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y , float z);
    void tick();
    double speedy;
    double speedx;
    double speedz;
    double gravity;
    bool exchange;
    bool upgrade;
    bool in_air;
    bool boost_mode;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5; // for cylinder
    VAO *object6;
};

#endif
