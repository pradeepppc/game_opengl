#include "water.h"
#include "main.h"

Water::Water(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    //speed = 1;
    // water will be a big cuboid


    static const GLfloat vertex_buffer_data[] = {
      //triangle 1
      1000.0f , 1500.0f , -3.0f,
      1000.0f , -1500.0f , -3.0f,
      -1000.0f, -1500.0f , -3.0f,
      -1000.0f, -1500.0f , -3.0f, // trinagle  2
       1000.0f , 1500.0f , -3.0f,
       -1000.0f , 1500.0f , -3.0f

    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Water::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Water::tick() {

    // this->position.x -= speed;
    // this->position.y -= speed;
}
