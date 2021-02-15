#include "labyrinthe.h"

Labyrinthe::Labyrinthe(int caseSize) :
    verticles{{ofVec3f(0,0,0),ofVec3f(caseSize,0,0),ofVec3f(caseSize,0,caseSize),ofVec3f(0,0,caseSize)},
              {ofVec3f(0,0,0),ofVec3f(caseSize,0,0),ofVec3f(caseSize,caseSize,0),ofVec3f(0,caseSize,0)},
              {ofVec3f(0,0,0),ofVec3f(0,0,caseSize),ofVec3f(0,caseSize,caseSize),ofVec3f(0,caseSize,0)},
              {ofVec3f(caseSize,0,0),ofVec3f(caseSize,0,caseSize),ofVec3f(caseSize,caseSize,caseSize),ofVec3f(caseSize,caseSize,0)},
              {ofVec3f(0,0,caseSize),ofVec3f(caseSize,0,caseSize),ofVec3f(caseSize,caseSize,caseSize),ofVec3f(0,caseSize,caseSize)},
              {ofVec3f(0,caseSize,0),ofVec3f(caseSize,caseSize,0),ofVec3f(caseSize,caseSize,caseSize),ofVec3f(0,caseSize,caseSize)}},
    id{0,2,1,0,2,3},
    textCoords{ {ofVec2f(0,0),ofVec2f(0.5,0),ofVec2f(0.5,1),ofVec2f(0,1)},
                {ofVec2f(0.5,0),ofVec2f(1,0),ofVec2f(1,1),ofVec2f(0.5,1)},
                {ofVec2f(0.5,0),ofVec2f(1,0),ofVec2f(1,1),ofVec2f(0.5,1)},
                {ofVec2f(0.5,0),ofVec2f(1,0),ofVec2f(1,1),ofVec2f(0.5,1)},
                {ofVec2f(0.5,0),ofVec2f(1,0),ofVec2f(1,1),ofVec2f(0.5,1)},
                {ofVec2f(0.5,0),ofVec2f(1,0),ofVec2f(1,1),ofVec2f(0.5,1)}}
{
    this->caseSize = caseSize;
}

bool Labyrinthe::loadLayout(string name){
    ofBuffer buff = ofBufferFromFile(name+".txt");
    int x = 0, y = 0;

    if (buff.size())
        for (ofBuffer::Line line = buff.getLines().begin(); line != buff.getLines().end(); line ++){
            vector<ofVec3f>lineLayout;
            x = 0;
            for (char i : *line){
                if (i == '0'){
                    lineLayout.push_back(ofVec3f(x,y,0));
                } else {
                    lineLayout.push_back(ofVec3f(x,y,1));
                }
                x += this->caseSize;
            }
            this->layout.push_back(lineLayout);
            y += this->caseSize;
        }
    else
        return false;

    return true;
}

bool Labyrinthe::isWall(int x, int y){
    if (x>0 && y>0 && x<(int)this->layout.at(0).size()-1 && y<(int)this->layout.size()-1){
        if (this->layout.at(y).at(x).z == 1){
            return true;
        }
        return false;
    }

    return true;
}

bool Labyrinthe::wallsArround(int x, int y){
    return isWall(x-1,y) && isWall(x+1,y) && isWall(x,y-1) && isWall(x,y+1);
}

void Labyrinthe::addFace(ofMesh &m, int x, int y, int id){ // generate face from arrays
    ofVec3f pos(x,0,y);

    for (int i = 0; i<4; i++){
        m.addVertex(this->verticles[id][i]+pos);
        m.addTexCoord(this->textCoords[id][i]);
    }

    for (const int verticleId : this->id){
        m.addIndex(this->drawIndex+verticleId);
    }

    this->drawIndex += 4;
}

void Labyrinthe::generate() {
    this->drawIndex = 0;
    this->m.clear();
    m.setMode(OF_PRIMITIVE_TRIANGLES);

    for (const vector<ofVec3f> &line : this->layout){
        for (const ofVec3f &pos : line){
            //if arround walls, player can't see it, so don't draw
            if (!wallsArround(pos.x/this->caseSize,pos.y/this->caseSize) ) {
                if (pos.z == 0)
                    addFace(m,pos.x,pos.y,0);
                if (pos.z == 1){
                    addFace(m,pos.x,pos.y,5);
                    if (!isWall(pos.x/this->caseSize,pos.y/this->caseSize-1))
                          addFace(m,pos.x,pos.y,1);
                    if (!isWall(pos.x/this->caseSize-1,pos.y/this->caseSize))
                        addFace(m,pos.x,pos.y,2);
                    if (!isWall(pos.x/this->caseSize+1,pos.y/this->caseSize))
                        addFace(m,pos.x,pos.y,3);
                    if (!isWall(pos.x/this->caseSize,pos.y/this->caseSize+1))
                        addFace(m,pos.x,pos.y,4);
                }

            }

        }
    }
}

bool Labyrinthe::playerColision(ofVec3f size, ofVec3f position, ofVec3f &moove){
    int width = this->layout.size()*this->caseSize;
    int height = this->layout.at(0).size()*this->caseSize;

    if (position.x > 0 && position.x<width && position.z > 0 && position.z < height){
        int x = position.x / this->caseSize;
        int y = position.z / this->caseSize;

        size /= 2;
        //simple floor colision for all tiles
        if (position.y < 0 && moove.y >= -size.y){
            moove.y = -size.y-1;
            return true;
        } else if (position.y > 0 && moove.y <= size.y){
            moove.y = size.y+1;
            return true;
        }


        //test for top of walls
        if (this->layout.at(y).at(x).z == 1 && position.y > this->caseSize && moove.y <= this->caseSize+size.y){
            moove.y = this->caseSize + size.y + 1;
            return true;
        }

        //test for sides
        if (position.y > 0 && position.y < this->caseSize){
            int xp = moove.x / this->caseSize;
            int yp = moove.z / this->caseSize;

            if (yp >= 0 && yp < (int)this->layout.size() && xp >= 0 && xp < (int)this->layout.at(0).size())
                if (this->layout.at(yp).at(xp).z == 1){
                    //ofLog()<<x<<" "<<xp;
                    if (x <= xp){
                        moove.x = xp * caseSize;
                    } else if (x > xp){
                        moove.x = (xp + 1) * caseSize;
                    }
                }
            xp = moove.x / this->caseSize;
            yp = moove.z / this->caseSize;
            if (yp >= 0 && yp < (int)this->layout.size() && xp >= 0 && xp < (int)this->layout.at(0).size())
                if (this->layout.at(yp).at(xp).z == 1){
                    if (y <= yp){
                        ofLog()<<moove.z<<" "<<(yp * caseSize);
                        moove.z = yp * caseSize;
                    } else if (y > yp){
                        moove.z = (yp + 1) * caseSize;
                    }
                }
        }
    }

    return false;
}

void Labyrinthe::draw() {
    m.draw();
}

int Labyrinthe::getHeight() {
    return this->layout.size()*this->caseSize;
}

int Labyrinthe::getWidth() {
    if (this->layout.size()>0){
        return this->layout.at(0).size()*this->caseSize;
    }
    return 0;
}

