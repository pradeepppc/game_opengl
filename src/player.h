#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y , float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y , float z);
    void tick();
    bool in_boat;
    int health;
    float leng;
    int score;
    bool in_air;
    float gravity;
    float speedx;
    float speedy;
    float speedz;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
