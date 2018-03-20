#include "rock.h"
#include "main.h"


Rock::Rock(float x, float y , float z , float l) {
    this->position = glm::vec3(x, y, z); // z = -2.5
    this->rotation = 0;
    this->leng = l;
    //considering prisms for rock structure
    float len = this->leng;
    float zz = l;
    static const GLfloat vertex_buffer_data[] = {
      //base square of the prism
        len , -len  , -zz,
        -len , -len , -zz,
        len , len , -zz,
        -len , -len , -zz,
        len , len , -zz,
        -len , len , -zz,
        len , -len , -zz, //ist triangle
        -len , -len , -zz,
        0.0f , 0.0f , zz,
        len , len , -zz, //2 tri
        len , -len , -zz,
        0.0f , 0.0f , zz,
        0.0f , 0.0f , zz, // 3 tri
        len , len , -zz,
        -len , len , -zz,
        0.0f , 0.0f , zz, // 4 triangle
        -len , len , -zz,
        -len , -len , -zz
};

    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, COLOR_ROCK, GL_FILL);
}

void Rock::draw(glm::mat4 VP) {
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

void Rock::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Rock::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}


bounding_box_t Rock::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  float l = this->leng;
  bounding_box_t bbox = { x, y, z, 2*l, 2*l, 2*l};
    return bbox;
}
