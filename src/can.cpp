#include "can.h"
#include "main.h"

Can::Can(float x, float y) {
    this->position = glm::vec3(x, y, -2.0f);
    this->rotation = 0;
    this->rotation1 = 0;
    this->speed = 0;
    float len = 0.2f;
    this->length = len;
    this->is_active = true;
    float up = 0.75;


    float pi = 3.14159,x_cord=len,y_cord=len;

    static  GLfloat vertex_buffer_data5[360 * 6];
    for(int i = 0 ;i<360 * 6;i = i + 6)
    {
      float tempx = x_cord*cos(pi/180) - y_cord*sin(pi/180);
         float tempy = x_cord*sin(pi/180) + y_cord*cos(pi/180);
         //for first vertex
         vertex_buffer_data5[i] = x_cord;
         vertex_buffer_data5[i+1] = -up; //
         vertex_buffer_data5[i+2] = y_cord;
         //for second vertex
         vertex_buffer_data5[i+3] = x_cord;
         vertex_buffer_data5[i+4] = up;//
         vertex_buffer_data5[i+5] = y_cord;

         x_cord =tempx;
         y_cord= tempy;
    }
    //one circle on top of the cylinder
    static  GLfloat vertex_buffer_data6[360*9];
    x_cord = len , y_cord = len;
    for(int i=0;i<360*9;i=i+9)
         {
             float tempx = x_cord*cos(pi/180) - y_cord*sin(pi/180);
             float tempy = x_cord*sin(pi/180) + y_cord*cos(pi/180);
             //for first vertex
             vertex_buffer_data6[i] = x_cord;
             vertex_buffer_data6[i+1] = up;
             vertex_buffer_data6[i+2] = y_cord;
             //for second vertex
             vertex_buffer_data6[i+3] = tempx;
             vertex_buffer_data6[i+4] = up;
             vertex_buffer_data6[i+5] = tempy;
             //for third vertex
             vertex_buffer_data6[i+6] = 0.0f;
             vertex_buffer_data6[i+7] = up;
             vertex_buffer_data6[i+8] = 0.0f;
             x_cord =tempx;
             y_cord= tempy;
         }

         this->object5 = create3DObject(GL_LINES ,360 * 2, vertex_buffer_data5, COLOR_CANNON, GL_FILL);
         this->object6 = create3DObject(GL_TRIANGLES ,360 * 3, vertex_buffer_data6, COLOR_CANNON, GL_FILL);

}

void Can::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1 * cos((M_PI/180)*this->rotation1), 1 * sin((M_PI/180)*this->rotation1), 0));
    glm::mat4 rotate1    = glm::rotate((float) (this->rotation1 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
}

void Can::set_position(float x, float y , float z) {
    this->position = glm::vec3(x, y, z);
}

void Can::tick() {

    //this->rotation += 10;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Can::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  float l = 2 * this->length;
  bounding_box_t bbox = { x, y, z, l, l, l};
    return bbox;
}
