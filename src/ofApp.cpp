#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    l = Labyrinthe(30);
    l.loadLayout("lab1");
    l.generate();
    ofLoadImage(this->text,"textures.png");
    ofEnableNormalizedTexCoords();
    ofEnableAntiAliasing();

    infoDisplay.load("verdana.ttf",15);

    //center mouse
    setCenter = true;
    ofxMouseController::setPos(ofGetWindowPositionX()+ofGetWidth()/2,ofGetWindowPositionY()+ofGetHeight()/2);
    ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update(){
    //fist, update playqer movement with keyboard
    if (ofGetKeyPressed(' ')){
        p.moove(Player::UP);
    }

    if (ofGetKeyPressed(OF_KEY_SHIFT)){
        p.moove(Player::DOWN);
    }

    if (ofGetKeyPressed('z')){
        p.moove(Player::FORWARD);
    }

    if (ofGetKeyPressed('s')){
        p.moove(Player::BACKWARD);
    }

    if (ofGetKeyPressed('q')){
        p.moove(Player::LEFT);
    }

    if (ofGetKeyPressed('d')){
        p.moove(Player::RIGHT);
    }

    p.evolve(&l);
    //update camera position
    cam.setPosition(p.getPosition());
    cam.lookAt(p.getLook());
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
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
    //p.draw();
    cam.end();

    ofDisableDepthTest();
    infoDisplay.drawString(ofToString(ofGetFrameRate()),10,10);
    infoDisplay.drawString(ofToString(p.getPosition()),10,30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //if mouse is not center
    if ((x != ofGetWidth()/2 || y != ofGetWidth()/2) && !setCenter){
        p.changeDirection(x-lastX,y-lastY);
        lastX = x;
        lastY = y;
        ofxMouseController::setPos(ofGetWindowPositionX()+ofGetWidth()/2,ofGetWindowPositionY()+ofGetHeight()/2);
        setCenter = true;
    } else {
        setCenter = false;
        lastX = ofGetWidth()/2;
        lastY = ofGetHeight()/2;
    }
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
