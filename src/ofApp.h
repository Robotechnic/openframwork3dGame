#pragma once

#include <ofBaseApp.h>
#include <of3dPrimitives.h>
#include <ofCamera.h>
#include <ofTexture.h>
#include "labyrinthe.h"
#include "player.h"
#include "ofxMouseController.h"
#include <ofLight.h>
#include <ofTrueTypeFont.h>

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);

    private:
        ofCamera cam;
        Player p;

        Labyrinthe l;
        ofTexture text;
        ofTrueTypeFont infoDisplay;


        int lastX,lastY;
        bool setCenter;

};
