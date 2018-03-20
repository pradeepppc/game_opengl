#include "main.h"

#ifndef MON_H
#define MON_H


class Mon {
public:
    Mon() {}
    Mon(float x, float y , float z , float l);
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
