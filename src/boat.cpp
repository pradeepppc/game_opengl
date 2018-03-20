#include "boat.h"
#include "main.h"

Boat::Boat(float x_co, float y_co) {
    this->position = glm::vec3(x_co, y_co, -2.5f);
    this->rotation = 0;
    this->speedy = 0;
    this->speedx = 0;
    this->speedz = 0;
    this->in_air = false;
    this->exchange = false;
    this->gravity = 0.03;
    this->boost_mode = false;
    this->upgrade = false;
    float x = 1.0f;
    float y = 1.5f;
    float up = -0.5f;
    float bottom = 0.5f;
    float x1 = 0.5f;


    static const GLfloat vertex_buffer_data[] = {
      //base rectangle

      x1,-y , -bottom ,
      x1 , y , -bottom,
      -x1, -y , -bottom,
      x1 , y , -bottom,
      -x1, -y , -bottom,
      -x1 , y , -bottom,
      x1 , y , -bottom , //side rectangle
      x , y , -up ,
      x1 , -y , -bottom ,
      x , y , -up ,
      x1 , -y , -bottom ,
      x , -y , -up,
      -x1 , y , -bottom , // left side rectangle
      -x , y , -up ,
      -x1 , -y , -bottom,
      -x , y , -up ,
      -x1 , -y , -bottom,
      -x, -y , -up

    };
    //front prism
    static const GLfloat vertex_buffer_data1[] ={
       // base side
       x1 , y , -bottom ,
       -x1 , y , -bottom,
       x , y , -up ,
       x , y , -up ,
       -x , y , -up ,
       -x1 , y , -bottom ,
       -x , y , -up , // up face of the prism
       x , y , -up,
       0.0f , y + 1.0 , -up,
       0.0f , y + 1.0 , -up,//left face
       -x , y , -up ,
       -x1 , y , -bottom,
       0.0f , y + 1.0 , -up, // right face
       x , y , -up ,
       x1 , y , -bottom,
       0.0f , y + 1.0 , -up, // base side triangle
       -x1 , y , -bottom,
       x1 , y , -bottom

    };

    y = -y;
    static const GLfloat vertex_buffer_data2[] ={
       // base side
       x1 , y , -bottom ,
       -x1 , y , -bottom,
       x , y , -up ,
       x , y , -up ,
       -x , y , -up ,
       -x1 , y , -bottom ,
       -x , y , -up , // up face of the prism
       x , y , -up,
       0.0f , y - 1.0 , -up,
       0.0f , y - 1.0 , -up,//left face
       -x , y , -up ,
       -x1 , y , -bottom,
       0.0f , y - 1.0 , -up, // right face
       x , y , -up ,
       x1 , y , -bottom,
       0.0f , y - 1.0 , -up, // base side triangle
       -x1 , y , -bottom,
       x1 , y , -bottom

    };
    y = -y;
    float x2 = (x + x1)/2;
    float middle = (up + bottom)/2;
    static const GLfloat vertex_buffer_data3[] = {
      x2 , y , -middle ,
      -x2 , y , -middle ,
      x2 , - y , -middle ,
      -x2 , y , -middle ,
      x2 , - y , -middle ,
      -x2 , -y , -middle

    };

    //for red 3d appearence
    static const GLfloat vertex_buffer_data4[] = {
      x , y , -up,
      -x , y , -up, //first prism
      0.0f , y+1.0 , -up,
      -x , -y , -up, //second prism
      x , -y , -up,
      0.0f , -y-1.0 , -up

    };


    //for cylinder
    float pi = 3.14159,x_cord=0.2,y_cord=0.2;
    float add_y = 0.8f;
    static  GLfloat vertex_buffer_data5[360 * 6];
    for(int i = 0 ;i<360 * 6;i = i + 6)
    {
      float tempx = x_cord*cos(pi/180) - y_cord*sin(pi/180);
         float tempy = x_cord*sin(pi/180) + y_cord*cos(pi/180);
         //for first vertex
         vertex_buffer_data5[i] = x_cord;
         vertex_buffer_data5[i+1] = y_cord + add_y;
         vertex_buffer_data5[i+2] = 0.0f;
         //for second vertex
         vertex_buffer_data5[i+3] = x_cord;
         vertex_buffer_data5[i+4] = y_cord + add_y;
         vertex_buffer_data5[i+5] = 1.5f;

         x_cord =tempx;
         y_cord= tempy;
    }
    //one circle on top of the cylinder
    static  GLfloat vertex_buffer_data6[360*9];
    x_cord = 0.2 , y_cord = 0.2;
    for(int i=0;i<360*9;i=i+9)
         {
             float tempx = x_cord*cos(pi/180) - y_cord*sin(pi/180);
             float tempy = x_cord*sin(pi/180) + y_cord*cos(pi/180);
             //for first vertex
             vertex_buffer_data6[i] = x_cord;
             vertex_buffer_data6[i+1] = y_cord + add_y;
             vertex_buffer_data6[i+2] = 1.5f;
             //for second vertex
             vertex_buffer_data6[i+3] = tempx;
             vertex_buffer_data6[i+4] = tempy + add_y;
             vertex_buffer_data6[i+5] = 1.5f;
             //for third vertex
             vertex_buffer_data6[i+6] = 0.0f;
             vertex_buffer_data6[i+7] = 0.0f + add_y;
             vertex_buffer_data6[i+8] = 1.5f;
             x_cord =tempx;
             y_cord= tempy;
         }




    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, COLOR_BOAT, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES ,6*3, vertex_buffer_data1, COLOR_BOAT_PRISM, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES ,6*3, vertex_buffer_data2, COLOR_BOAT_PRISM, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES ,2*3, vertex_buffer_data3, COLOR_BOAT_BASE, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES ,2*3, vertex_buffer_data4, COLOR_BOAT_RED, GL_FILL);
    this->object5 = create3DObject(GL_LINES ,360 * 2, vertex_buffer_data5, COLOR_BOAT_ROD, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES ,360 * 3, vertex_buffer_data6, COLOR_BOAT_ROD, GL_FILL);
  }

void Boat::draw(glm::mat4 VP) {
  glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model = glm::mat4(1.0f);
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
}

void Boat::set_position(float x, float y , float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {

  if(this->position.z < -2.5)
  {
    this->position.z = -2.5;
    this->in_air = false;
  }
  // if boat is in air decrease its speed along z dir and add the speed to the distance along the z dir
  if(this->in_air)
  {
    this->position.z += this->speedz;
    this->speedz -= this->gravity;
  }
  //add speed_x along the x direction
  this->position.x += this->speedx;



  //these are done for the bounding box
  this->rotation = ((int)this->rotation) % 360;
  if((this->rotation >= 45 && this -> rotation <= 135) || (this->rotation >= 225 && this->rotation <= 315))
  {
    this->exchange = true;
  }
  else
  {
    if(this->rotation > 0)
    {
      this->exchange = false;
    }
  }

  if((this->rotation >= -135 && this -> rotation <= -45) || (this->rotation >= -315 && this->rotation <= -225))
  {
    this->exchange = true;
  }
  else
  {
    if(this->rotation < 0)
    {
      this->exchange = false;
    }
  }


}


bounding_box_t Boat::bounding_box(){
  float x = this->position.x, y = this->position.y , z = this->position.z;
  bounding_box_t bbox = { x, y, z, 2.0, 3.5, 1.0};
  bounding_box_t bbox1 = { x, y, z, 3.5, 2.0, 1.0};
  if(this->exchange)
  return bbox1;
  else
  return bbox;
}
