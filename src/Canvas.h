//
//  PickerFrame.h
//  PickerFrame
//
//  Created by hiz on 2014/11/02.
//
//

#ifndef __PickerFrame__PickerFrame__
#define __PickerFrame__PickerFrame__

#include <stdio.h>
#include "ofMain.h"
#include "ofxFrame.h" 

enum BrushShape {
  RECT, CIRCLE
};

struct BrushInfo {
  BrushShape shape;
  float      size;
  float      amt;
};

struct CanvasInfo {
  ofVec2f tileSize;
  ofVec2f selectedTile;
  ofTexture image;
  int       layer;
  BrushInfo brush;
};

class ToolFrame : public ofxFrame {
public:
  ToolFrame(const ofRectangle &rect, CanvasInfo *info) : ofxFrame(rect, ofVec2f(1000,32)) {
    this->info = info;
    font.loadFont("saxmono.ttf", 10);
    
    // layer
    addWidget(ofPtr<Segment>(new Segment(ofRectangle(10,0,84,28), 3, info->layer)));
    // brush
    addWidget(ofPtr<Label>( new Label(ofRectangle(100,0,90,28), font, "size")));
    addWidget(ofPtr<Slider>(new Slider(ofRectangle(150,0,90,28), 1,1,10, &info->brush.size, 1)));
    addWidget(ofPtr<RefLabel<float> >(new RefLabel<float>(ofRectangle(250,0,40,28), font,info->brush.size)));
    addWidget(ofPtr<Label>( new Label(ofRectangle(310,0,30,28), font, "amt")));
    addWidget(ofPtr<Slider>(new Slider(ofRectangle(340,0,90,28), 1.0,0.01,1.0, &info->brush.amt, 0.01)));
    addWidget(ofPtr<RefLabel<float> >(new RefLabel<float>(ofRectangle(440,0,40,28), font,info->brush.amt)));
    
  }
private:
  CanvasInfo *info;
  ofTrueTypeFont font;
};


class PickerFrame : public ofxFrame {
public:
  PickerFrame(const ofRectangle &rect, CanvasInfo *info) : ofxFrame(rect, ofVec2f(0,0)) {
    this->info = info;
    setContentSize(ofVec2f(info->image.getWidth(), info->image.getHeight()));
    hoveredTile = ofVec2f(0,0);
    info->selectedTile = ofVec2f(0,0);
    
    info->brush.shape = RECT;
    info->brush.size  = 3;
    info->brush.amt   = 0.5;
  }

  virtual void drawImpl() {
    ofDisableSmoothing();
    ofSetColor(255);
    info->image.draw(0,0);
    
    // hovered tile
    ofSetColor(0);
    ofSetLineWidth(4);
    ofNoFill();
    ofRect(hoveredTile.x * info->tileSize.x, hoveredTile.y * info->tileSize.y,
           info->tileSize.x,info->tileSize.y);
    ofSetColor(200);
    ofSetLineWidth(2);
    ofNoFill();
    ofRect(hoveredTile.x * info->tileSize.x, hoveredTile.y * info->tileSize.y,
           info->tileSize.x,info->tileSize.y);
    
    // selected tile
    ofSetColor(0);
    ofSetLineWidth(4);
    ofNoFill();
    ofRect(info->selectedTile.x * info->tileSize.x, info->selectedTile.y * info->tileSize.y,
           info->tileSize.x,info->tileSize.y);
    ofSetColor(255);
    ofSetLineWidth(2);
    ofRect(info->selectedTile.x * info->tileSize.x, info->selectedTile.y * info->tileSize.y,
           info->tileSize.x,info->tileSize.y);
    ofEnableSmoothing();
  }
  virtual void mouseMovedImpl(int x, int y) {
    hoveredTile = ofVec2f((int)(x / info->tileSize.x), (int)(y / info->tileSize.y));
  }
  virtual void mouseDraggedImpl(int x, int y, int button) {
  }
  virtual void mousePressedImpl(int x, int y, int button) {
    info->selectedTile = ofVec2f((int)(x / info->tileSize.x), (int)(y / info->tileSize.y));
  }
  virtual void mouseReleasedImpl(int x, int y, int button) {
  }
  virtual void mouseScrolledImpl(int mx, int my, int sx, int sy) {
    hoveredTile = ofVec2f((int)(mx / info->tileSize.x), (int)(my / info->tileSize.y));
  }
  private:
  CanvasInfo *info;
  ofVec2f hoveredTile;
};

class CanvasFrame : public ofxFrame {
public:
  CanvasFrame(const ofRectangle &rect, CanvasInfo *info) : ofxFrame(rect, ofVec2f(1600,1600)) {
    this->info = info;
    for(int layer = 0;layer < 3;layer ++) {
      vector<ofVec2f> t;
      for(int x=0;x<contentSize.x/info->tileSize.x;x++) {
        for(int y=0;y<contentSize.y/info->tileSize.y;y++) {
          t.push_back(ofVec2f(-1,-1));
        }
      }
      tiles.push_back(t);
    }
    
    preBrushedTileIdx = ofVec2f(-1,-1);
    history.push_back(tiles);
    dirty = false;
  }
  virtual void drawImpl() {
    ofDisableSmoothing();
    ofSetColor(255);
    // 表示範囲外は処理をスキップ
    ofRectangle displayArea = getDisplayArea();
    
    for(int l=0;l<3;l++) {
      if(l == info->layer) ofSetColor(255,255,255,255);
      else ofSetColor(255,255,255,122);
      for(int x=0;x<contentSize.x/info->tileSize.x;x++) {
        if(x < (displayArea.getLeft() / info->tileSize.x)-1 || (displayArea.getRight() / info->tileSize.x)+1 < x) continue;
        for(int y=0;y<contentSize.y/info->tileSize.y;y++) {
          if(y < (displayArea.getTop() / info->tileSize.y)-1 || (displayArea.getBottom() / info->tileSize.y)+1 < y) continue;
          ofVec2f tile = tiles[l][y*(contentSize.x/info->tileSize.x)+x];
          if(tile.x < 0)continue;
          info->image.drawSubsection(x*info->tileSize.x, y*info->tileSize.y, info->tileSize.x, info->tileSize.y, tile.x*info->tileSize.x, tile.y*info->tileSize.y);
        }
      }
    }
    
    // hovered tile
    ofSetColor(0);
    ofSetLineWidth(4);
    ofNoFill();
    ofRect(hoveredTile.x * info->tileSize.x, hoveredTile.y * info->tileSize.y,
           info->tileSize.x * info->brush.size,info->tileSize.y * info->brush.size);
    ofSetColor(255);
    ofSetLineWidth(2);
    ofRect(hoveredTile.x * info->tileSize.x, hoveredTile.y * info->tileSize.y,
           info->tileSize.x * info->brush.size,info->tileSize.y * info->brush.size);
    ofEnableSmoothing();
  }
  ofVec2f getTileIdx(int x, int y) {
    int tx = (int)(x / info->tileSize.x);
    int ty = (int)(y / info->tileSize.y);
    return ofVec2f(tx, ty);
  }
  void putTile(ofVec2f tileIdx, ofVec2f tile) {
    tiles[info->layer][tileIdx.y*(contentSize.x/info->tileSize.x)+tileIdx.x] = tile;
    dirty = true;
  }
  void pickTile(ofVec2f tileIdx) {
    const ofVec2f &tile = tiles[info->layer][tileIdx.y*(contentSize.x/info->tileSize.x)+tileIdx.x];
    if(tile.x < 0)return;
    info->selectedTile = tile;
  }
  void fillRectTile(ofRectangle rect, ofVec2f tile, float amt=1.0) {
    for(int y=rect.getTop();y <= rect.getBottom();y++) {
      if(y < 0 || y >= contentSize.y/info->tileSize.y)continue;
      for(int x=rect.getLeft();x <= rect.getRight();x++) {
        if(x < 0 || x >= contentSize.x/info->tileSize.x)continue;
        if(ofRandom(1.0) <= amt) {
          putTile(ofVec2f(x, y), info->selectedTile);
        }
      }
    }
  }
  
  void brushTile(int x, int y) {
    ofVec2f tileIdx = getTileIdx(x, y);
    if(preBrushedTileIdx == tileIdx)return;
    fillRectTile(ofRectangle(tileIdx, tileIdx + ofVec2f(info->brush.size-1,info->brush.size-1)), info->selectedTile, info->brush.amt);
    
    preBrushedTileIdx = tileIdx;
  }
  
  void undo() {
    if(history.size() > 1) {
      redoHistory.push_back(history.back());
      history.pop_back();
      tiles = history.back();
    }
  }
  
  void redo() {
    if(redoHistory.size() > 0) {
      history.push_back(redoHistory.back());
      tiles = redoHistory.back();
      redoHistory.pop_back();
      
    }
  }
  
  virtual void mouseMovedImpl(int x, int y) {
    hoveredTile = ofVec2f((int)(x / info->tileSize.x), (int)(y / info->tileSize.y));
  }
  virtual void mouseDraggedImpl(int x, int y, int button) {
    brushTile(x, y);
    
    hoveredTile = ofVec2f((int)(x / info->tileSize.x), (int)(y / info->tileSize.y));
  }
  virtual void mousePressedImpl(int x, int y, int button) {
    if(button == 0) {
      // left click
      brushTile(x, y);
    } else if(button == 2){
      // right click
      pickTile(getTileIdx(x, y));
    }
    
  }
  virtual void mouseScrolledImpl(int mx, int my, int sx, int sy) {
    hoveredTile = ofVec2f((int)(mx / info->tileSize.x), (int)(my / info->tileSize.y));
  }
  virtual void mouseReleasedImpl(int x, int y, int button) {
    if(button == 0) {
      if(dirty) {
        if(history.size() > 128)history.erase(history.begin());
        history.push_back(tiles);
        redoHistory.clear();
      }
    }
    dirty = false;
  }
private:
  CanvasInfo *info;
  vector<vector<ofVec2f> > tiles;
  vector<vector<vector<ofVec2f> > > history;
  vector<vector<vector<ofVec2f> > > redoHistory;
  ofVec2f hoveredTile;
  ofVec2f preBrushedTileIdx;
  bool dirty;
};


#endif /* defined(__PickerFrame__PickerFrame__) */
