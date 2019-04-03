Game Code
==========================
This is the code for the game which i have created in opengl.


src director consists of the all the files which i have used to create this game .


## How to run the game?
Go to the directory  and run the following commands

    cd build
    cmake ..
    make
    ./zelda

# Game controls:
The player is controlled by the arrow keys:

     left key       => Rotate left,
     right key      => Rotate right
     up key         => Move Forward

     space key      => jump
         o          => bombs

     "c key"        => Default view
     "b key"        => Camera in Boat
     "t key"        => Top view 2
     "y key"        => Tower view
     "z key"        => Helicopter view
      "q key"       => quit
      "2 key"       => for moving the cannon down
      "8 key"       => for raising the cannon up 
Score and Lives left are displayed on the title.

### Health
There are certain gifts on the sea which when collected will increase the health of the boat.
* Initially, you are given with health of 50. If you collide with an enemy boat or rocks, you loose health. When the health reaches 0, the GAME IS OVER.

### Collision
On collision with rocks and enemy boats, the health of the boat will be decreased.

### Gifts
There are barrels floating on the sea with gifts on them which when jumped over would increase the score of the boat.

### Boosters
There are some boosters floating on the sea which when collected would give boost to the boat for a couple of seconds.

### Fireball
Fireballs can be used to kill the monsters. They are realeased through cannons which is in front of the boat.

### Killing monsters
On Killing the monsters through Cannons, the score of the boat is increased and also the monsters leaves a booster(Coins) when it dies which can be collected to boost the speed of the boat.

### Boss Monster
On Killing 4 Monsters, a Boss Monster would appear in the sea. To kill the boss monster, the boat should fire atleast 3 fireballs to kill the Boss Monster. When it dies, it leaves a booster and the score of the boat is increased.
### Bonus
* Sounds for various actions are added.
* Created an Island where the man can move and inside island there is a hidden treassure .


How to Run
=========================

Open qt creator and give it cmakelist.txt file then , run the cmake , for running the game just type green arrow button at 

bottom left of the screen a pop up window will appear with running game .




