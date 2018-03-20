#include "main.h"

#ifndef SAIL_H
#define SAIL_H


class Sail {
public:
    Sail() {}
    Sail(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y );
    void tick();
    float leng;
    bool is_active; // sail appears only when the boat is moving
    double speed;
    float length;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
