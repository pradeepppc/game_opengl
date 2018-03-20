#include "sail.h"
#include "main.h"

Sail::Sail(float x, float y) {
    this->position = glm::vec3(x, y, -2.0f);
    this->rotation = 0;
    this->speed = 0;
    float len = 0.2f;
    this->length = len;
    this->is_active = false;


    static const GLfloat vertex_buffer_data[] = {
      0.0f , 0.0f , 0.0f,
      0.0f , 0.0f , 1.10f,
      0.0f , -0.6f , 0.0f

    };

    this->object = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data, COLOR_SAIL, GL_FILL);
}

void Sail::draw(glm::mat4 VP) {
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

void Sail::set_position(float x, float y) {
    this->position = glm::vec3(x, y, -2.0f);
}

void Sail::tick() {

    //this->rotation += 10;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Sail::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  float l = 2 * this->length;
  bounding_box_t bbox = { x, y, z, l, l, l};
    return bbox;
}
