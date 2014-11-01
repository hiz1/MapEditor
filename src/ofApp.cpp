#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  
  
  
  pickerFrame = ofPtr<PickerFrame>(new PickerFrame(ofRectangle(0  , 0, 128, ofGetHeight())));
  pickerFrame->setResizeFlag(RESIZE_SIZE | RESIZE_Y);
  pickerFrame->setImage("base.png", ofVec2f(16,16));
  
  toolFrame  = ofPtr<ToolFrame>(new ToolFrame(ofRectangle(128, 0, ofGetWidth() - 128, 32)));
  toolFrame->setResizeFlag(RESIZE_SIZE | RESIZE_X);
  
  mapFrame = ofPtr<MapFrame>(new MapFrame(ofRectangle(128 , 32, ofGetWidth() - 128, ofGetHeight()-32)));
  mapFrame->setResizeFlag(RESIZE_SIZE | RESIZE_X | RESIZE_Y );
  mapFrame->setSelectedTilePtr(&pickerFrame->selectedTile);
  mapFrame->setTileImage(&pickerFrame->image, pickerFrame->tileSize);
}

//--------------------------------------------------------------
void ofApp::update(){
  pickerFrame->update();
  toolFrame->update();
  mapFrame->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  pickerFrame->draw();
  toolFrame->draw();
  mapFrame->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

void ofApp::mouseScrolled(double x, double y) {
  MouseScrollArgs args;
  args.mx = mouseX;
  args.my = mouseY;
  args.sx = x;
  args.sy = y;
  ofNotifyEvent(mouseScrolledEvent, args);
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
