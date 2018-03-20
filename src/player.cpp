#include "player.h"
#include "main.h"

Player::Player(float x, float y , float z) {
    this->position = glm::vec3(x, y,z);
    this->rotation = 0;
    float len = 0.3f;
    this->in_boat = true;
    this->score = 0;
    this->health = 100;
    this->speedx = 0;
    this ->speedy = 0;
    this->speedz = 0;
    this->gravity = 0.03;
    this->leng = len;
    this->in_air = false;

      static const GLfloat vertex_buffer_data[] = {
        -len,-len,-len, // triangle 1 : begin
        -len,-len, len,
        -len, len, len, // triangle 1 : end
        len, len,-len, // triangle 2 : begin
        -len,-len,-len,
        -len, len,-len, // triangle 2 : end
        len,-len, len,
        -len,-len,-len,
        len,-len,-len,
        len, len,-len,
        len,-len,-len,
        -len,-len,-len,
        -len,-len,-len,
        -len, len, len,
        -len, len,-len,
        -len,-len,-len,
        len,-len, len,
        -len,-len, len,
        -len, len, len,
        -len,-len, len,
        len,-len, len,
        len, len, len,
        len,-len,-len,
        len, len,-len,
        len,-len,-len,
        len, len, len,
        len,-len, len,
        len, len, len,
        len, len,-len,
        -len, len,-len,
        len, len, len,
        -len, len,-len,
        -len, len, len,
        len, len, len,
        -len, len, len,
        len,-len, len
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_COIN, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Player::set_position(float x, float y , float z) {
    this->position = glm::vec3(x, y, z);
}

void Player::tick() {

  //for jumping of the player block
  if(this->position.z < -2.5)
  {
    this->position.z = -2.5;
    this->in_air = false;
  }
  //if it is in air
  if(this->in_air)
  {
    this->position.z += this->speedz;
    this->speedz -= this->gravity;
  }

}

bounding_box_t Player::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  float l = this->leng;
  bounding_box_t bbox = { x, y, z, 2 * l, 2 * l, 2 * l};
    return bbox;
}
