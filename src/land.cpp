#include "land.h"
#include "main.h"

Land::Land(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, -2.99);
    this->rotation = 0;
    this->leng = 100;
    //speed = 1;
    // water will be a big cuboid


    static const GLfloat vertex_buffer_data[] = {
      //triangle 1
      100.0f , 100.0f , 0.0f,
      100.0f , -100.0f , 0.0f,
      -100.0f, -100.0f , 0.0f,
      -100.0f, -100.0f , 0.0f, // trinagle  2
       100.0f , 100.0f , 0.0f,
       -100.0f , 100.0f , 0.0f

    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Land::draw(glm::mat4 VP) {
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

void Land::set_position(float x, float y) {
    this->position = glm::vec3(x, y, -2.99);
}

void Land::tick() {

    // this->position.x -= speed;
    // this->position.y -= speed;
}


bounding_box_t Land::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  float l = 2 * this->leng;
  bounding_box_t bbox = { x, y, z, l, l, 0};
    return bbox;
}
