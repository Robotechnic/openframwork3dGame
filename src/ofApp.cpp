#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    p.setRadius(20);
    ofEnableDepthTest();
    l = Labyrinthe(20);
    l.loadLayout("lab1");
    l.generate();
    ofLoadImage(this->text,"textures.png");
    ofEnableNormalizedTexCoords();

    //ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    cam.begin();
    ofSetColor(255,0,0);
    ofDrawLine(0,0,0,100,0,0);
    ofSetColor(0,255,0);
    ofDrawLine(0,0,0,00,100,0);
    ofSetColor(0,0,255);
    ofDrawLine(0,0,0,0,0,100);

    ofSetColor(255);
    this->text.bind();
    l.draw();
    this->text.unbind();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofVec3f pos = cam.getPosition();
    switch (key) {
        case 'z':
            pos.y += 5;
            cam.setPosition(pos);
            break;
        case 's':
            pos.y -= 5;
            cam.setPosition(pos);
            break;

        case 'd':
            pos.x += 5;
            cam.setPosition(pos);
            break;

        case 'q':
            pos.x -= 5;
            cam.setPosition(pos);
            break;

        case OF_KEY_SHIFT:
            pos.z -= 5;
            cam.setPosition(pos);
            break;

        case ' ':
            pos.z += 5;
            cam.setPosition(pos);
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
