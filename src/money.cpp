#include "money.h"
#include "main.h"

Money::Money(float x, float y , float z) {
    this->position = glm::vec3(x, y,z);
    this->rotation = 0;
    float len = 2.0f;
    this->leng = len;
    this->is_active = true;

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

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_REDS, GL_FILL);
}

void Money::draw(glm::mat4 VP) {
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

void Money::set_position(float x, float y , float z) {
    this->position = glm::vec3(x, y, z);
}

void Money::tick() {



}

bounding_box_t Money::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  float l = this->leng;
  bounding_box_t bbox = { x, y, z, 2 * l, 2 * l, 2 * l};
    return bbox;
}
