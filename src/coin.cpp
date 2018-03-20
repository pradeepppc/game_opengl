#include "coin.h"
#include "main.h"

Coin::Coin(float x, float y , int score) {
    this->position = glm::vec3(x, y, -1.5f);
    this->rotation = 0;
    this->speed = 0;
    float len = 0.2f;
    this->length = len;
    this->is_active = true;
    this->bonus = score;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
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

void Coin::draw(glm::mat4 VP) {
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

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coin::tick() {
    this->rotation += 10;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Coin::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  float l = 2 * this->length;
  bounding_box_t bbox = { x, y, z, l, l, l};
    return bbox;
}
