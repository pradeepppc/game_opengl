#include "main.h"

#ifndef ROCK_H
#define ROCK_H


class Rock {
public:
    Rock() {}
    Rock(float x, float y , float z , float l);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float leng;
    //double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
