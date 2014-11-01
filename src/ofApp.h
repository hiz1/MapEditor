#pragma once

#include "ofMain.h"
#include "ofxFrame.h"

class ToolFrame : public ofxFrame {
public:
  ToolFrame(const ofRectangle &rect) : ofxFrame(rect, ofVec2f(1000,32)) {}
};

class MapFrame : public ofxFrame {
public:
  MapFrame(const ofRectangle &rect) : ofxFrame(rect, ofVec2f(1600,1600)) {}
  void setTileImage(ofImage *image, const ofVec2f &tileSize) {
    this->image = image;
    this->tileSize = tileSize;
    for(int x=0;x<contentSize.x/tileSize.x;x++) {
      for(int y=0;y<contentSize.y/tileSize.y;y++) {
        tiles.push_back(ofVec2f(-1,-1));
      }
    }
  }
  void setSelectedTilePtr(ofVec2f *selectedTile) {
    this->selectedTilePtr = selectedTile;
  }
  virtual void drawImpl() {
    ofDisableSmoothing();
    ofSetColor(255);
    for(int x=0;x<contentSize.x/tileSize.x;x++) {
      for(int y=0;y<contentSize.y/tileSize.y;y++) {
        ofVec2f tile = tiles[y*(contentSize.x/tileSize.x)+x];
        if(tile.x < 0)continue;
        image->drawSubsection(x*tileSize.x, y*tileSize.y, tileSize.x, tileSize.y, tile.x*tileSize.x, tile.y*tileSize.y);
      }
    }
    // hovered tile
    ofSetColor(0);
    ofSetLineWidth(4);
    ofNoFill();
    ofRect(hoveredTile.x * tileSize.x, hoveredTile.y * tileSize.y,
           tileSize.x,tileSize.y);
    ofSetColor(255);
    ofSetLineWidth(2);
    ofRect(hoveredTile.x * tileSize.x, hoveredTile.y * tileSize.y,
           tileSize.x,tileSize.y);
    ofEnableSmoothing();
  }
  virtual void mouseMovedImpl(int x, int y) {
    hoveredTile = ofVec2f((int)(x / tileSize.x), (int)(y / tileSize.y));
  }
  virtual void mouseDraggedImpl(int x, int y, int button) {
    int tx = (int)(x / tileSize.x);
    int ty = (int)(y / tileSize.y);
    tiles[ty*(contentSize.x/tileSize.x)+tx] = *selectedTilePtr;
    
    hoveredTile = ofVec2f((int)(x / tileSize.x), (int)(y / tileSize.y));
  }
  virtual void mousePressedImpl(int x, int y, int button) {
    int tx = (int)(x / tileSize.x);
    int ty = (int)(y / tileSize.y);
    tiles[ty*(contentSize.x/tileSize.x)+tx] = *selectedTilePtr;
  }
  virtual void mouseScrolledImpl(int mx, int my, int sx, int sy) {
    hoveredTile = ofVec2f((int)(mx / tileSize.x), (int)(my / tileSize.y));
  }
private:
  ofImage *image;
  vector<ofVec2f> tiles;
  ofVec2f *selectedTilePtr;
  ofVec2f tileSize;
  ofVec2f hoveredTile;
};

class PickerFrame : public ofxFrame {
public:
  PickerFrame(const ofRectangle &rect) : ofxFrame(rect, ofVec2f(0,0)) {}
  void setImage(const string &imagePath, const ofVec2f &tileSize) {
    image.loadImage(imagePath);
    this->tileSize = tileSize;
    setContentSize(ofVec2f(image.getWidth(), image.getHeight()));
    hoveredTile = ofVec2f(0,0);
    selectedTile = ofVec2f(0,0);
  }
  
  virtual void drawImpl() {
    ofDisableSmoothing();
    ofSetColor(255);
    image.draw(0,0);
    
    // hovered tile
    ofSetColor(0);
    ofSetLineWidth(4);
    ofNoFill();
    ofRect(hoveredTile.x * tileSize.x, hoveredTile.y * tileSize.y,
           tileSize.x,tileSize.y);
    ofSetColor(200);
    ofSetLineWidth(2);
    ofNoFill();
    ofRect(hoveredTile.x * tileSize.x, hoveredTile.y * tileSize.y,
           tileSize.x,tileSize.y);
    
    // selected tile
    ofSetColor(0);
    ofSetLineWidth(4);
    ofNoFill();
    ofRect(selectedTile.x * tileSize.x, selectedTile.y * tileSize.y,
           tileSize.x,tileSize.y);
    ofSetColor(255);
    ofSetLineWidth(2);
    ofRect(selectedTile.x * tileSize.x, selectedTile.y * tileSize.y,
           tileSize.x,tileSize.y);
    ofEnableSmoothing();
  }
  virtual void mouseMovedImpl(int x, int y) {
    hoveredTile = ofVec2f((int)(x / tileSize.x), (int)(y / tileSize.y));
  }
  virtual void mouseDraggedImpl(int x, int y, int button) {
  }
  virtual void mousePressedImpl(int x, int y, int button) {
    selectedTile = ofVec2f((int)(x / tileSize.x), (int)(y / tileSize.y));
  }
  virtual void mouseReleasedImpl(int x, int y, int button) {
  }
  virtual void mouseScrolledImpl(int mx, int my, int sx, int sy) {
    hoveredTile = ofVec2f((int)(mx / tileSize.x), (int)(my / tileSize.y));
  }
  ofImage image;
  ofVec2f tileSize;
  ofVec2f selectedTile;
  ofVec2f hoveredTile;
};


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
    void mouseScrolled(double x, double y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
  
  ofPtr<ToolFrame>   toolFrame;
  ofPtr<PickerFrame> pickerFrame;
  ofPtr<MapFrame>    mapFrame;
};
