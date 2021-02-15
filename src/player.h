#ifndef PLAYER_H
#define PLAYER_H

#include <ofVec3f.h>
#include <of3dPrimitives.h>
#include <of3dGraphics.h>
#include "labyrinthe.h"

#define GRAVITY 9.80665

class Player
{
    public:
        Player();

        enum Direction {
            UP=0,
            DOWN=1,
            BACKWARD=2,
            FORWARD=3,
            LEFT=4,
            RIGHT=5
        };

        void draw();

        void moove(Direction d);
        void evolve(Labyrinthe *l);

        void changeDirection(const int deltaX, const int deltaY, const float sensitivity = 0.5);
        ofVec3f getLook();

        ofVec3f getPosition(){return this->pos;};
        float getPitch(){return this->pitch;};
        float getYaw(){return this->yaw;};
        void setPitch(float pitch){this->pitch = (pitch > 89)? 89: (pitch < -89) ? -89 : pitch;};
        //void setYaw(float yaw){this->yaw = yaw > 180 ? yaw - 180*(int)(yaw/180) : (yaw<-180) ? yaw + 180*(int)(-yaw/180) : yaw;};
        void setYaw(float yaw){this->yaw = yaw;};

    private:
        ofVec3f pos,speed;
        float yaw,pitch;


};

#endif // PLAYER_H
