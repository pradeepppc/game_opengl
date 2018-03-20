#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H

class Monster {

public:
    Monster() {}
    Monster(float x, float y , float z);
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
    int move;
    double leng;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
};

#endif // BALL_H
