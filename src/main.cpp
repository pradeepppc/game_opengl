#include "main.h"
#include "timer.h"
#include "ball.h"
#include "water.h"
#include "boat.h"
#include "cannon.h"
#include "barrel.h"
#include "coin.h"
#include "player.h"
#include "rock.h"
#include "monster.h"
#include "sail.h"
#include "health.h"
#include "booster.h"
#include "boss.h"
#include "land.h"
#include "mon.h"
#include "can.h"
#include "money.h"
#include <math.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <sstream>


using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
//integers
int number_of_barrels = 50;
int numbet_of_rocks = 100;
int number_of_mosters = 50;
int min_score = 10;
//initializing variables for the objects
Ball ball1;
Boat boat;
Water water;
Land land;
Cannon cannon;
Barrel barrel[50];
Coin coin[50];
Player player;
Rock rock[100];
Mon bigrock;
Monster monster[50];
Sail sail;
Health health;
Booster booster;
Boss boss;
Can can;
bool drag;
Money money;
double mouse_x,mouse_y;
float init_x = 0, init_y = 0 , init_z = 0;
float range = 5; // range of the cannon
bool orth = false;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
//angle of rotation of camera
float camera_rotation_angle = 0;
float camera_vertical_angle = 0;
//camera views
int cam_view = 0; // 0 => Follow cam view , 1 => tower view , 2 => top view , 3 => boat view , 4 => helicop view , 5 => original moves as start
// cordinates of the camera
float camera_x = 5*sin(camera_rotation_angle*M_PI/180.0f), camera_y = -5*cos(camera_rotation_angle*M_PI/180.0f), camera_z = 0.1f;
float cam_x = 5*sin(camera_rotation_angle*M_PI/180.0f), cam_y = -5*cos(camera_rotation_angle*M_PI/180.0f) , cam_z = 0.0f;
float target_x = 0.0f , target_y = 0.0f , target_z = 0.0f;
float pi = 3.14159;
double theta;
double alpha;
double dtheta = 1 * M_PI/180.0f;

Timer t60(1.0 / 60);
//timer for the wind blow
Timer timer(14.0),timex(5.0);
//timer for the booster
Timer boost_time(30.0);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    //camera_y = -5*cos(camera_rotation_angle*M_PI/180.0f);
    //camera_x = 5*sin(camera_rotation_angle*M_PI/180.0f);
    //camera_z =  0;
    // Eye - Location of camera. Don't change unless you are sure!!
    /*camera_x = 0;
    camera_y = 0;
    camera_z = 2;*/
    glm::vec3 eye (camera_x , camera_y ,camera_z);
    if(cam_view == 5)
    {
      eye[0] = cam_x;
      eye[1] = cam_y;
      eye[2] = cam_z;
    }
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (target_x, target_y, target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 0, 1);
    // Compute Camera matrix (view)

    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D  (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model


    //draw Water
    water.draw(VP);

    //draw the land
    land.draw(VP);
    bigrock.draw(VP);
    //draw the mosters if not is_killed
    for(int i =0;i<number_of_mosters;i++)
    {
      if(!monster[i].is_killed)
      monster[i].draw(VP);
    }

    //draw the rocks
    for(int i=0;i<numbet_of_rocks;i++)
    {
      rock[i].draw(VP);
    }

    // draw the barrels,coins
    for(int i = 0;i<number_of_barrels;i++)
    {
      barrel[i].draw(VP);
      if(coin[i].is_active)
      coin[i].draw(VP);
    }
    //draw the health if active
    if(health.is_active)
    health.draw(VP);
    //draw the booster if active
    if(booster.is_active)
    booster.draw(VP);

    // draw the boss if not killed
      if(boss.is_active)
      if(!boss.is_killed)
      boss.draw(VP);

    //draw the cannon if it is active
    if(cannon.is_active)
    {
      cannon.draw(VP);
    }
    //draw the money if active

    if(money.is_active)
    money.draw(VP);
    //draw the sail if active
    if(sail.is_active)
    sail.draw(VP);

    //draw thw can if it is active
    if(can.is_active)
    can.draw(VP);
    //draw boat
    boat.draw(VP);

    //draw the player if he is not in the boat
    if(!player.in_boat)
    player.draw(VP);
    //draw the cannon
    //cannon.draw(VP);
}

void tick_input(GLFWwindow *window) {

    glm::vec3 boat_pos = boat.position;
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int space  =  glfwGetKey(window, GLFW_KEY_SPACE);
    int detach = glfwGetKey(window,GLFW_KEY_F);
    int d = glfwGetKey(window,GLFW_KEY_D);
    int a = glfwGetKey(window,GLFW_KEY_A);
    int w = glfwGetKey(window,GLFW_KEY_W);
    int s = glfwGetKey(window,GLFW_KEY_S);
    int t = glfwGetKey(window,GLFW_KEY_T); // top view
    int c = glfwGetKey(window,GLFW_KEY_C); // follow cam view
    int b = glfwGetKey(window,GLFW_KEY_B); // boat view
    int n = glfwGetKey(window,GLFW_KEY_N); // normal movable camera
    int o = glfwGetKey(window,GLFW_KEY_O); // cannon
    int y = glfwGetKey(window,GLFW_KEY_Y); // tower view
    int h = glfwGetKey(window,GLFW_KEY_H); // helicopter cam view
    int m = glfwGetKey(window,GLFW_KEY_M); //for stoping the booster or turning it on
    int num_8 = glfwGetKey(window,GLFW_KEY_8);
    int num_2 = glfwGetKey(window,GLFW_KEY_2);

    int z  = glfwGetKey(window,GLFW_KEY_Z); // for ortho graphic view
    if(z)
    {
      if(orth)
      {
        orth = false;
      }
      else
      {
        orth = true;
      }
      reset_screen();
    }

    if(can.is_active)
    {
      float can_angle = can.rotation;

      if(num_8)
      {
        if(can_angle <= 70)
        can.rotation += 5;
      }
      if(num_2)
      {
        if(can_angle >= 0)
        can.rotation -= 5;
      }

    }

    if(boat.upgrade) //booster only if boat is upgraded
    if(m)
    {
      system(" canberra-gtk-play -f  ./resources/gift.wav --volume=\"1\"   &");
      if(boat.boost_mode)
      boat.boost_mode = false;
      else
      boat.boost_mode = true;
    }

    if(!cannon.is_active)
    if(o)
    {
      //for playing the sound
      //system("canberra-gtk-play --file = ../resources/granade.wav --volume=\"10\" &");
      system(" canberra-gtk-play -f  ./resources/cannon.wav --volume=\"1\"   &");
      cannon.is_active = true;
      cannon.angle = -boat.rotation;
      float can_angle = can.rotation;
      double ans = (double)2 * cannon.g * range;
      float vel = (float)sqrt(ans);
      float velxy = (float)vel * cos((pi/180)*can_angle);
      float vz = (float)vel * sin((pi/180)*can_angle);
      cannon.speedz = vz;
      cannon.speedx = velxy * sin((pi/180)*cannon.angle);
      cannon.speedy = velxy * cos((pi/180)*cannon.angle);
    }

    if(h) // helicopter cam view
    cam_view = 4;

    if(y) //tower view
    cam_view = 1;

    if(n) //normal movable camera
    cam_view = 5;

    if(b) //change the cam view to boat view
    {
      cam_view = 3;
    }

    if(c) // change the camera for the follow cam views
    {
      cam_view = 0;
      camera_z = 0;
    }
    if(t) //change the camera view to tower view
    {
      cam_view = 2;
      camera_z = 15;
    }
    if(cam_view == 5)
    {

    if(a){
      camera_rotation_angle -= 1;
    }
    if(d)
    {
      camera_rotation_angle += 1;
    }
    if(w)
    {
      cam_z += 0.5;
    }
    if(s)
    {
      cam_z -= 0.5;
    }
  }

    if (left) {
        // Do something
        //camera_rotation_angle -= 1;
        if(player.in_boat)
        boat.rotation += 5;
        else
        player.rotation += 5;

    }

    if (right)
    {
      //camera_rotation_angle += 1;
      if(player.in_boat)
      boat.rotation -= 5;
      else
      player.rotation -= 5;
    }
    if(up)
    {
      //system(" canberra-gtk-play -f  ./resources/ocean.wav --volume=\"1\"   &");
        if(player.in_boat)
        {
        float dl = 0.1;
        float angle = -boat.rotation;
        bounding_box_t temp;
        temp = boat.bounding_box();
        temp.x = boat_pos[0] + dl * sin((pi/180)*angle);
        temp.y = boat_pos[1] + dl * cos((pi/180)*angle);
        temp.z = boat_pos[2];
        bool move = true;
        //check with the collision of the barrel
        for(int i=0;i<number_of_barrels;i++)
        {
          if(detect_collision(barrel[i].bounding_box() , temp))
          {
            printf("Collision occured with barrel \n");
            move = false;
          }
        }

        boat.tick();

        //check for the collision with the rocks
        for(int i=0;i<numbet_of_rocks;i++)
        {
          if(detect_collision(rock[i].bounding_box() ,boat.bounding_box()))
          {
              move = false;
              player.health -= 5;
              printf("health of the player is %d\n",player.health);
              //move the boat little backwards so that it wont collide again
              float x_co  = boat_pos[0] - 1 * sin((pi/180)*angle);
              float y_co  = boat_pos[1] - 1 * cos((pi/180)*angle);
              boat.set_position(x_co , y_co , boat.position.z);
          }
        }
        //check with the collision with the land
        if(detect_collision(boat.bounding_box() , land.bounding_box()))
        move  = false;

        if(move)
        {
        boat.set_position(temp.x , temp.y , temp.z);
        sail.is_active = true;
        }
      }
      else
      {
        float dl = 0.1;
        float angle = -player.rotation;
        bounding_box_t temp;
        temp = player.bounding_box();
        temp.x = player.position.x + dl * sin((pi/180)*angle);
        temp.y = player.position.y + dl * cos((pi/180)*angle);
        temp.z = player.position.z;
        bool move = true;

        if(move)
        {
        player.set_position(temp.x , temp.y , temp.z);

        }
      }


    }
    else
    {
      sail.is_active = false;
    }
    if(!boat.in_air)
    if(space)
    {
      //jump the boat
      system(" canberra-gtk-play -f  ./resources/jump.wav --volume=\"1\"   &");
      if(player.in_boat)
      {
      boat.speedz = 0.5;
      boat.in_air = true;
      }
      else
      {
          player.speedz = 0.3;
          player.in_air = true;
      }
    }


    if(detach)
    {
      //system(" canberra-gtk-play -f  ./resources/cann.wav --volume=\"1\"   &");
      if(player.in_boat)
      {
      //check if the boat is near the island
      if(detect_collision(land.bounding_box() , boat.bounding_box()))
        {
          player.in_boat = false;
          player.set_position(boat.position.x, boat.position.y , boat.position.z);
          system(" canberra-gtk-play -f  ./resources/gift.wav --volume=\"1\"   &");
        }
      }
      else
      {
        if(detect_collision(player.bounding_box() , boat.bounding_box()))
        player.in_boat = true;
      }
    }

}

void tick_elements() {

  boat.tick();

  //tick for the cannon
  cannon.tick();

  //angle func for rotating the barrels
  angle_correlate(window);

  //if player is not in boat
  if(!player.in_boat)
  {
    player.tick();
    if(detect_collision(player.bounding_box() , money.bounding_box()))
    {
      player.score += 1000;
      money.is_active = false;
    }
  }
  else
  {
    player.set_position(boat.position.x , boat.position.y , boat.position.z);
    player.rotation = boat.rotation;
  }




  //to set cannon position in boat
  if(!cannon.is_active)
  {
    float boat_angle = -boat.rotation;
    cannon.set_position(boat.position.x + 2.5 * sin((pi/180)*boat_angle) , boat.position.y + 2.5 * cos((pi/180)*boat_angle) , boat.position.z + 0.5);
  }

  //check the collision of the cannon with the enemies
  if(cannon.is_active)
  {
    //iterate to number of monsters
   for(int i = 0;i<number_of_mosters;i++)
   {
     if(!monster[i].is_killed)
     {
       if(detect_collision(monster[i].bounding_box() , cannon.bounding_box()))
       {
         monster[i].is_killed = true;
         player.score += 10;
         int ran = rand() % 2;
         if(ran == 0)
         {
           //drop the health
           health.is_active = true;
           health.set_position(monster[i].position.x + 1.5 ,monster[i].position.y + 1.5);
         }
       }
     }
   }

 }

 //check the collision of the cannon with the boss baby
 if(cannon.is_active)
 if(boss.is_active)
 {
 if(!boss.is_killed)
 {
   boss.tick();
   if(detect_collision(boss.bounding_box(), cannon.bounding_box()))
   {
     boss.health -= 20;
     //system(" canberra-gtk-play -f  ./resources/boss.wav --volume=\"1\"   &");
     if(boss.health <= 0)
     {
       boss.is_killed = true;
     }
     if(boss.is_killed)
     {
     booster.is_active = true;
     booster.set_position(boss.position.x - 2 , boss.position.y + 2);
    }
   }
 }
}


  //for sail movement
  float boat_angle = -boat.rotation;
  sail.set_position(boat.position.x + 0.6 * sin((pi/180)*boat_angle) , boat.position.y + 0.6 * cos((pi/180)*boat_angle));

  //for can movement
  can.set_position(boat.position.x + 1.5 * sin((pi/180)*boat_angle) , boat.position.y + 1.5 * cos((pi/180)*boat_angle) , boat.position.z + 0.5);
  can.rotation1 = boat.rotation;
  //check the collision with the booster
  if(booster.is_active)
  {
    if(detect_collision(booster.bounding_box(), boat.bounding_box()))
    {
      boat.boost_mode = true;
      booster.is_active = false;
      boat.upgrade = true;
    }
  }

  //movement of the boat if the booster mode is on
  if(boat.boost_mode)
  {
      float angle = -boat.rotation;
      //chage this to increase the booster speed
      float diff = 0.3;
      float x = boat.position.x + diff * sin((pi/180)*angle);
      float y = boat.position.y + diff * cos((pi/180)*angle);
      boat.set_position(x , y , boat.position.z);
      /*if(boost_time.processTick())
      {
        boat.boost_mode = false;
      }*/
  }
  //check for score of the player to make boss active
  if(player.score >= min_score)
  {
    //printf("min score is reached \n");
    boss.is_active = true;
  }

  //check the collision of boat with main boss both will be killed
  if(boss.is_active)
  {
  if(!boss.is_killed)
  {
    boss.tick();
    if(detect_collision(boss.bounding_box(), boat.bounding_box()))
    {
      boss.is_killed = true;
      player.health = 0;
      booster.is_active = true;
      booster.set_position(boss.position.x - 2 , boss.position.y + 2);
    }
  }
}

  //if boat is in air make projectile motion
  if(boat.in_air)
  {
    float dl = 0.15;
    float angle = -boat.rotation;
    bounding_box_t temp;
    temp = boat.bounding_box();
    temp.x = temp.x + dl * sin((pi/180)*angle);
    temp.y = temp.y + dl * cos((pi/180)*angle);
    temp.z = temp.z;
    boat.set_position(temp.x,temp.y,temp.z);
  }

  //check for the collision of boat with the medic if is_active
  if(health.is_active)
  {
    if(detect_collision(health.bounding_box() , boat.bounding_box()))
    {
      player.health += 20;
      if(player.health > 100)
      player.health = 100;
      health.is_active = false;
      //printf("player health inc with medic %d \n" , player.health);
    }
  }

  //check for collision of boat with the mosters
  for(int i=0;i<number_of_mosters;i++)
  {
    if(!monster[i].is_killed)
    {
      monster[i].tick();
      if(detect_collision(monster[i].bounding_box(),boat.bounding_box()))
      {
        player.health -= 5;
        monster[i].is_killed = true;
        //printf("moster killed by colliding health is %d\n",player.health);

        //active the medic if the moster is killed
        int ran = rand() % 2;
        if(ran == 0)
        {
          //drop the health
          health.is_active = true;
          health.set_position(monster[i].position.x + 1.5 ,monster[i].position.y + 1.5);
        }
      }
    }
  }


  //check for sail direction
  float sail_angle = boat.rotation;
  if((sail_angle >= 0 && sail_angle <= 180)  || (sail_angle >= -180 && sail_angle <= -360))
  {
    sail.rotation = boat.rotation-50;
  }
  else
  {
    sail.rotation = boat.rotation + 50;
  }

  //timers for the wind
  //14 sec
  if(timer.processTick())
  {
    boat.speedx = 0.02;
  }
  //5 sec
  if(timex.processTick())
  {
    boat.speedx = 0;
  }


  //coins tick for the movement
  for(int i=0;i<number_of_barrels;i++)
  {
    if(coin[i].is_active)
    {
      coin[i].tick();
    }
  }
  //check for the collision of the  boat with every active coin
  for(int i=0;i<number_of_barrels;i++)
  {
    if(coin[i].is_active)
    {
      if(detect_collision(boat.bounding_box(),coin[i].bounding_box()))
      {
        //printf("Collision is detected with the coin \n");
        coin[i].is_active = false;
        player.score += coin[i].bonus;
      }
    }
  }

  //check for the camera position
  if(cam_view == 0 || cam_view == 2) // follow cam view
  {
      //target at boats position
      target_x = player.position.x;
      target_y = player.position.y;
      target_z = 0.0f;

      float angle = -player.rotation;
      camera_x = player.position.x - 5 * sin((pi/180)*angle);
      camera_y = player.position.y  - 5 * cos((pi/180)*angle);
      if(cam_view == 0)
      camera_z = 0.0f;

    }
  if(cam_view == 3) //boat view
  {
    float angle  = -player.rotation;
    camera_x = player.position.x;
    camera_y = player.position.y;
    camera_z = 0;
    target_x = player.position.x + 1 * sin((pi/180)*angle);
    target_y = player.position.y + 1 * cos((pi/180)*angle);
    target_z = 0;
  }
  if(cam_view == 1) // tower view
  {
    target_x = player.position.x;
    target_y = player.position.y;
    target_z = 0.0f;
    float angle  = -player.rotation;
    camera_x  = player.position.x - 10 * cos((pi/180)*angle);
    camera_y  = player.position.y + 10 * sin((pi/180)*angle);
    camera_z = 6.0f;
  }

  if(cam_view == 4) // helicopter cam view
  {
    target_x = player.position.x;
    target_y = player.position.y;
    target_z = 0.0f;
    float c_x = camera_x - target_x;
    float c_y = camera_y - target_y;
    if(drag)
    {
    //write later
    double m_x = mouse_x/1200;
    double m_z = mouse_y/1200;
      //printf("%lf %lf mousex mousey \n",mouse_x/1200 , mouse_y/1200);
    if(m_x > init_x)
    {
    //move the camera left side
    camera_x = c_x * cos(-dtheta) - c_y * sin(-dtheta) + target_x;
    camera_y = c_x * sin(-dtheta) + c_y * cos(-dtheta) + target_y;
    camera_z = camera_z;

    }
    else if(m_x < init_x)
    {//move camera right side by some angle
      camera_x = c_x * cos(dtheta) - c_y * sin(dtheta) + target_x;
      camera_y = c_x * sin(dtheta) + c_y * cos(dtheta) + target_y;
      camera_z = camera_z;
    }

    if(m_z > init_z)
    {
      //decrese the height of the camera
      camera_z += 0.05;
    }
    else if(m_z < init_z)
    {
      //increase the height of the camera
      camera_z -= 0.05;
    }

    }
    else{
      //camera_rotation_angle = 0;
    }


  }



}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    //create the money
    money = Money(0 , 300 , 1.0);

    //create the land
    land = Land(0 , 300 , COLOR_LAND);
    bigrock = Mon(0 , 300 , 17 , 20);
    //create the Player
    player = Player(0,0,0);



    //create the boat
    boat = Boat(0,0);
    //careate the sail
    sail  = Sail(0,0.6);

    // init of cannon
    can = Can(0 , 1.5);

    //create the water object
    water = Water(0,0,COLOR_WATER);

    //create the cannon
    cannon = Cannon(0 , 2.5 , -2);

    //create the boss
    boss = Boss(4 ,4 ,-2.0);

    //create the booster
    booster = Booster(3 ,3);

    //create the master
    for(int i=0;i<number_of_mosters;i++)
    {
      float bar_x = 0,bar_y = 0,bar_z = 0;
      int ran = rand() % 2;
      if(ran == 0)
        bar_x = rand() % 200;
      else
        bar_x = -rand() % 200;

      int ran2 = rand() % 2;
      if(ran2 == 0)
      bar_y = rand() % 200;
      else
      bar_y = -rand() % 200;

      int ran3 = rand()%2;
      if(ran3 == 0)
      bar_z = rand()%10;
      else
      bar_z = -rand()%10;

      if(rand()%2 == 0)
      bar_z = -2.0;



      monster[i] = Monster(bar_x ,bar_y , bar_z);
      int rr = rand() % 3;
      monster[i].move = rr;
    }

    //create the barrel objects
    barrel[0] = Barrel(2.0 , 0.0 , -2.85);
    coin[0] = Coin(2.0 , 0.0 , 10);
    for(int i=1;i<number_of_barrels;i++)
    {
        float bar_x = 0,bar_y = 0;
        int ran = rand() % 2;
        if(ran == 0)
          bar_x = rand() % 200;
        else
          bar_x = -rand() % 200;

        int ran2 = rand() % 2;
        if(ran2 == 0)
        bar_y = rand() % 200;
        else
        bar_y = -rand() % 200;

      barrel[i] = Barrel(bar_x , bar_y , -2.85);
      coin[i] = Coin(bar_x , bar_y , 10);
    }

    //create the rocks
    rock[0] = Rock(-2.0 , 0.0 , -2.5 , 0.75);
    for(int i=1;i<numbet_of_rocks;i++)
    {
        float bar_x = 0,bar_y = 0;
        int ran = rand() % 2;
        if(ran == 0)
          bar_x = rand() % 200;
        else
          bar_x = -rand() % 200;

        int ran2 = rand() % 2;
        if(ran2 == 0)
        bar_y = rand() % 200;
        else
        bar_y = -rand() % 200;

        rock[i] = Rock(bar_x , bar_y , -2.5 , 0.75);
      }

      //create the health
      health = Health(2 , 2);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1200;
    int height = 1200;
    drag = false;
    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps

            string player_score,player_level;
            stringstream Score,Levels;

            Score << player.score;
            player_score = Score.str();

            const char *score_string = "Score ";
            const char *score_value = player_score.c_str();
            const char *Level = "   Health ";
            Levels << player.health;

            player_level = Levels.str();
            const char *level_value = player_level.c_str();
            string total( string(score_string) + score_value + string(Level) + level_value);
            glfwSetWindowTitle(window, total.c_str());


            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            boat.rotation = ((int)boat.rotation) % 360;
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {

           if(abs(a.x - b.x)*2 < a.width + b.width)
            {
              //printf("x checked \n");
               //check the Y axis
               if(abs(a.y - b.y)*2 < a.height + b.height)
               {
                  //printf("y checked\n");
                   //check the Z axis
                   if(abs(a.z - b.z)*2 < a.length + b.length)
                   {
                     //printf("z checked\n");
                      return true;
                   }
               }
            }

            return false;
}



void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    if(orth){
      Matrices.projection = glm::ortho(left*4, right*4,bottom*4, top*4,  0.1f, 500.0f); // 0.1
      cam_view = 2; // top view
      camera_z = 15;
      }
      else
    Matrices.projection = glm::infinitePerspective(glm::radians(90.0f), 2.0f,0.1f);
}

void angle_correlate(GLFWwindow *window) {
    glfwGetCursorPos(window, &mouse_x, &mouse_y);
    float angle = 1 - 2*mouse_y/1200.0;
    can.rotation = angle*180.0/M_PI;
}

void init_drag()
{
  if(cam_view == 4)
  {
  drag = true;
  init_x = mouse_x/1200;
  init_y = mouse_y/1200;
  init_z = mouse_y/1200;
  //init_z = mouse_z/1200;
  }
}

void close_drag()
{
  if(cam_view == 4)
  {
  drag = false;
  }
}

//used for zooming in and out of the boat in helicaophter cam view
void zoom_func(double xoffset ,double yoffset)
{
  //just chage the camera position
  if(cam_view == 4)
  {
  //printf("%lf %lf zoom_func \n",xoffset , yoffset);

  if(camera_z <= 0.1)
  {
    camera_z = 0.3;
  }
  double f_x = camera_x - target_x , f_y = camera_y - target_y , f_z = camera_z - target_z;
  bool zoom = true;


  if(f_z <=  0)
  {
  f_z = 0.1;
  camera_z = 0.4;
  double def_z = camera_z - target_z;
  double x_y = def_z / tan(theta);
  camera_x = x_y * cos(alpha) + target_x;
  camera_y = x_y * sin(alpha) + target_y;
  zoom = false;
  }
  if(zoom)
  {
  //printf("%lf %lf %lf fx fy fz \n", f_x , f_y , f_z);
  double param = (double) f_z/sqrt(f_y * f_y + f_x * f_x);
  theta = atan (param); // theta radians
  alpha = atan(f_y / f_x);
  double act = sqrt(f_x * f_x + f_y * f_y + f_z * f_z);
  if(yoffset > 0)
  act -= 0.03;
  else
  act += 0.03;

  double len = act * cos(theta);
  f_z = act * sin(theta);
  camera_x = (float)len * cos(alpha) + target_x;
  camera_y = (float)len * sin(alpha) + target_y;
  camera_z = f_z + target_z;
  //printf("%f %f %f camx camy camz\n",camera_x , camera_y , camera_z);
  }
  }

}
