#include "main.h"

#ifndef CAN_H
#define CAN_H


class Can {
public:
    Can() {}
    Can(float x, float y);
    glm::vec3 position;
    float rotation;
    float rotation1;
    void draw(glm::mat4 VP);
    void set_position(float x, float y , float z);
    void tick();
    float leng;
    bool is_active; // sail appears only when the boat is moving
    double speed;
    float length;
    bounding_box_t bounding_box();
private:
    VAO *object5;
    VAO *object6;
};

#endif // BALL_H
