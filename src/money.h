#include "main.h"

#ifndef MONEY_H
#define MONEY_H


class Money {
public:
    Money() {}
    Money(float x, float y , float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y , float z);
    void tick();
    bool is_active;
    float leng;

    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
