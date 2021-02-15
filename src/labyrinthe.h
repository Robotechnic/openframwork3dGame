#ifndef LABYRINTHE_H
#define LABYRINTHE_H
#pragma once

#include <vector>
#include <string>
#include <ofFileUtils.h>
#include <of3dGraphics.h>
#include <ofGraphics.h>
#include <ofVec4f.h>
#include <ofLog.h>

using namespace std;

class Labyrinthe
{
    public:
        Labyrinthe(int caseSize = 20);
        bool loadLayout(string name);
        void draw();
        void generate();

        bool playerColision(ofVec3f size, ofVec3f position, ofVec3f &moove);

        int getWidth();
        int getHeight();

    private:
        void addFace(ofMesh &m, int x, int y, int id);
        bool isWall(int x, int y);
        bool wallsArround(int x, int y);
        vector<vector<ofVec3f>> layout;
        ofMesh m;
        int caseSize;
        int drawIndex;

        ofVec3f verticles[6][4];
        int id[6];
        ofVec2f textCoords[6][4];
};

#endif // LABYRINTHE_H
