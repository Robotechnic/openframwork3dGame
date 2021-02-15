#include "player.h"

Player::Player()
{
    yaw = 0;
    pitch = 0;
}

void Player::moove(Direction d) {
    ofVec3f moove;
    switch (d) {
        case UP:
            moove = ofVec3f(0,1,0);
            break;
        case DOWN:
            moove = ofVec3f(0,-1,0);
            break;

        case FORWARD:
            moove = ofVec3f(1,0,0);
            moove = moove.rotate(this->yaw,ofVec3f(0,1,0));
            break;

        case BACKWARD:
            moove = ofVec3f(-1,0,0);
            moove = moove.rotate(this->yaw,ofVec3f(0,1,0));
            break;

        case RIGHT:
            moove = ofVec3f(1,0,0);
            moove = moove.rotate(this->yaw-90,ofVec3f(0,1,0));
            break;

        case LEFT:
            moove = ofVec3f(1,0,0);
            moove = moove.rotate(this->yaw+90,ofVec3f(0,1,0));
            break;
    }

    this->speed += moove;
}

void Player::evolve(Labyrinthe *l){
    ofVec3f futurePos = this->pos + this->speed;

    l->playerColision(ofVec3f(15,15,15),this->pos,futurePos);
    this->pos = futurePos;



    this->speed = ofVec3f(0,0,0);
}

void Player::changeDirection(const int deltaX, const int deltaY, const float sensitivity){
    this->setYaw(this->getYaw()-deltaX*sensitivity);
    this->setPitch(this->getPitch()-deltaY*sensitivity);
}

ofVec3f Player::getLook() {
    ofVec3f look(1,0,0);
    look = look.rotate(0,this->yaw,this->pitch);
    return this->pos+look;
}

void Player::draw() {
    ofDrawBox(this->pos, 10);
}
