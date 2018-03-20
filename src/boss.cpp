#include "boss.h"
#include "main.h"

Boss::Boss(float x, float y , float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 0.1;
    this->speedx = 0;
    this->speedy = 0;
    this->speedz = 0;
    this->init_x = x;
    this->init_y = y;
    this->init_z = z;
    float len = 0.5f;
    this->leng = len;
    this->health = 60; // canon has to hit 3 times to kill it
    this->is_killed = false;
    this->is_active = false;
    this->move = 0; // by default move moster along x-axis


    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -len,-len,-len, // triangle 1 : begin
        -len,-len, len,
        -len, len, len, // triangle 1 : end
        len,-len, len,
        len, len,-len, // triangle 2 : begin
        -len,-len,-len,
        -len, len,-len, // triangle 2 : end
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

    static GLfloat vertex_buffer_data1[] = {
      len , len , len, // first prism
      len , -len , len,
      2*len, 0.0f , 0.0f,
      len , -len , len,//2 tri
      2*len, 0.0f , 0.0f,
      len , -len , -len ,
      2*len, 0.0f , 0.0f, // 3 tri
      len , -len , -len ,
      len , len , -len,
      2*len, 0.0f , 0.0f, // 4 tri
      len , len , len,
      len , len , -len

    };
    static GLfloat vertex_buffer_data2[] = {
      -len , len , len, // second prism
      -len , -len , len,
      -2*len, 0.0f , 0.0f,
      -len , -len , len,//2 tri
      -2*len, 0.0f , 0.0f,
      -len , -len , -len ,
      -2*len, 0.0f , 0.0f, // 3 tri
      -len , -len , -len ,
      -len , len , -len,
      -2*len, 0.0f , 0.0f, // 4 tri
      -len , len , len,
      -len , len , -len

    };

    static  GLfloat vertex_buffer_data3[360*9];
    float pi = 3.14159,x_cord=0.1,z_cord=0.1;
    float x_diff = 0.2;
    for(int i=0;i<360*9;i=i+9)
     {
         float tempx = x_cord*cos(pi/180) - z_cord*sin(pi/180);
         float tempy = x_cord*sin(pi/180) + z_cord*cos(pi/180);
         //for first vertex
         vertex_buffer_data3[i] = x_cord - x_diff;
         vertex_buffer_data3[i+1] = -len - 0.001;
         vertex_buffer_data3[i+2] = z_cord;
         //for second vertex
         vertex_buffer_data3[i+3] = tempx - x_diff;
         vertex_buffer_data3[i+4] = -len - 0.001;
         vertex_buffer_data3[i+5] = z_cord;
         //for third vertex
         vertex_buffer_data3[i+6] = 0.0f - x_diff;
         vertex_buffer_data3[i+7] = -len - 0.001;
         vertex_buffer_data3[i+8] = 0.0f;
         x_cord =tempx;
         z_cord= tempy;
     }
     x_cord=0.1,z_cord=0.1;
     static  GLfloat vertex_buffer_data4[360*9];

         for(int i=0;i<360*9;i=i+9)
          {
              float tempx = x_cord*cos(pi/180) - z_cord*sin(pi/180);
              float tempy = x_cord*sin(pi/180) + z_cord*cos(pi/180);
              //for first vertex
              vertex_buffer_data4[i] = x_cord + x_diff;
              vertex_buffer_data4[i+1] = -len - 0.001;
              vertex_buffer_data4[i+2] = z_cord;
              //for second vertex
              vertex_buffer_data4[i+3] = tempx + x_diff;
              vertex_buffer_data4[i+4] = -len - 0.001;
              vertex_buffer_data4[i+5] = z_cord;
              //for third vertex
              vertex_buffer_data4[i+6] = 0.0f + x_diff;
              vertex_buffer_data4[i+7] = -len - 0.001;
              vertex_buffer_data4[i+8] = 0.0f;
              x_cord =tempx;
              z_cord= tempy;
          }

          float xx = 0.1;
          float diff_z = 0.26;
          //rectangle for mouth
          static  GLfloat vertex_buffer_data5[] = {
                xx,-len - 0.001,xx - diff_z, //rectangle
                xx , -len - 0.001 , -xx - diff_z,
                -xx ,  -len - 0.001 , xx -diff_z,
                xx , -len - 0.001 , -xx -diff_z,
                -xx ,  -len - 0.001 , xx - diff_z,
                -xx ,   -len - 0.001 , -xx - diff_z
            };

            //upward prism
            static GLfloat vertex_buffer_data6[] = {
              -len , len , len ,
              len , len , len ,
              0.0f , 0.0f , 2 * len,
              len , len , len , //2
              0.0f , 0.0f , 2 * len,
              len , -len , len,
              0.0f , 0.0f , 2 * len, // 3
              len , -len , len,
              -len , -len , len,
              -len , -len , len, // 4
              0.0f , 0.0f , 2 * len,
              -len , len , len
            };
            //downward prism
            static GLfloat vertex_buffer_data7[] = {

              -len , len , -len ,
              len , len , -len ,
              0.0f , 0.0f , -2 * len,
              len , len , -len , //2
              0.0f , 0.0f , -2 * len,
              len , -len , -len,
              0.0f , 0.0f , -2 * len, // 3
              len , -len , -len,
              -len , -len , -len,
              -len , -len , -len, // 4
              0.0f , 0.0f , -2 * len,
              -len , len , -len
            };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, COLOR_BOSS, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data1, COLOR_BLUE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_BLUE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data3, COLOR_WHITE, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 360*3, vertex_buffer_data4, COLOR_WHITE, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data5, COLOR_WHITE, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data6, COLOR_BOSS_TOP, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data7, COLOR_BOSS_TOP, GL_FILL);
}

void Boss::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->object7);
}

void Boss::set_position(float x, float y , float z) {
    this->position = glm::vec3(x, y, z);
}

void Boss::tick() {


    //check for the movement of the monster

    if(this->move == 0) //move along x-axis and y-axis
    {
      if(this->speedx == 0)
      this->speedx = this->speed;

      if(this -> speedy == 0)
      this->speedy = this->speed;

      float diffx = this->position.x - this->init_x;
      if(diffx <= -14)
      {
        this->speedx = this->speed;
      }
      if(diffx >= 14)
      {
        this->speedx = -this->speed;
      }

      float diffy = this->position.y - this->init_y;
      if(diffy <= -14)
      {
        this->speedy = this->speed;
      }
      if(diffy >= 14)
      {
        this->speedy = -this->speed;
      }

    }


    this->position.x += this->speedx;
    this->position.y += this->speedy;
    this->position.z += this->speedz;


}

bounding_box_t Boss::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  float l = 2 * this->leng;
  bounding_box_t bbox = { x, y, z, l, l, l};
    return bbox;
}
