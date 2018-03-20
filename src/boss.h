#include "main.h"

#ifndef BOSS_H
#define BOSS_H

class Boss {

public:
    Boss() {}
    Boss(float x, float y , float z);
    glm::vec3 position;
    float rotation;
    float init_x;
    float init_y;
    float init_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    void tick();
    double speedx;
    double speedy;
    double speedz;
    double speed;
    bool is_killed;
    bool is_active;
    int move;
    double leng;
    double health;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
};

#endif // BALL_H
