#include "barrel.h"
#include "main.h"

Barrel::Barrel(float x, float y , float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 0;
    float len = 0.5f;
    this->length = len;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float pi = 3.14159,x_cord=len,y_cord=len;

    static  GLfloat vertex_buffer_data[360 * 6];
    for(int i = 0 ;i<360 * 6;i = i + 6)
    {
      float tempx = x_cord*cos(pi/180) - y_cord*sin(pi/180);
         float tempy = x_cord*sin(pi/180) + y_cord*cos(pi/180);
         //for first vertex
         vertex_buffer_data[i] = x_cord;
         vertex_buffer_data[i+1] = y_cord;
         vertex_buffer_data[i+2] = -len;
         //for second vertex
         vertex_buffer_data[i+3] = x_cord;
         vertex_buffer_data[i+4] = y_cord;
         vertex_buffer_data[i+5] = len;

         x_cord =tempx;
         y_cord= tempy;
    }
    //one circle on top of the cylinder
    static  GLfloat vertex_buffer_data1[360*9];
    x_cord = len , y_cord = len;
    for(int i=0;i<360*9;i=i+9)
         {
             float tempx = x_cord*cos(pi/180) - y_cord*sin(pi/180);
             float tempy = x_cord*sin(pi/180) + y_cord*cos(pi/180);
             //for first vertex
             vertex_buffer_data1[i] = x_cord;
             vertex_buffer_data1[i+1] = y_cord;
             //for second vertex
             vertex_buffer_data1[i+2] = len;
             vertex_buffer_data1[i+3] = tempx;
             vertex_buffer_data1[i+4] = tempy;
             vertex_buffer_data1[i+5] = len;
             //for third vertex
             vertex_buffer_data1[i+6] = 0.0f;
             vertex_buffer_data1[i+7] = 0.0f;
             vertex_buffer_data1[i+8] = len;
             x_cord =tempx;
             y_cord= tempy;
         }



    this->object = create3DObject(GL_LINES, 360*2, vertex_buffer_data, COLOR_BOAT, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data1, COLOR_BARREL, GL_FILL);
}

void Barrel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Barrel::set_position(float x, float y , float z) {
    this->position = glm::vec3(x, y, z);
}

void Barrel::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Barrel::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  float l = this->length * 2;
  bounding_box_t bbox = { x, y, z,l,l,l};
    return bbox;
}
