#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speedx = 0;
    this->speedy = 0;
    this->speedz = 0;
    this->is_active = false;
    this->g = 0.02;
    this->angle = 0;
    //modify this
    float len = 0.2;
    this->leng = len;

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
        len, len, len,
        len,-len, len,
        len, len,-len,
        -len, len, len,
        -len, len,-len,
        len, len, len,
        -len, len,-len,
        len, len, len,
        -len, len, len,
        len,-len, len
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_BLACKS, GL_FILL);

}

void Cannon::draw(glm::mat4 VP) {
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

void Cannon::set_position(float x, float y , float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {

  //if it falls into water then it should be inactive
  if(this->position.z < -3)
  {
    this->is_active = false;
    this->speedx = 0;
    this->speedy = 0;
    this->speedz = 0;
  }

  //if active
  if(this->is_active)
  {
    this->position.x += this->speedx;
    this->position.y += this->speedy;
    this->position.z += this->speedz;
    this->speedz -= this->g;
  }

}


bounding_box_t Cannon::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  float r = 2 * this->leng;
  bounding_box_t bbox = { x, y, z, r, r, r};
    return bbox;
}
