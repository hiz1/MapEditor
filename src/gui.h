//
//  gui.h
//  PickerFrame
//
//  Created by hiz on 2014/11/03.
//
//

#ifndef PickerFrame_gui_h
#define PickerFrame_gui_h

class Label : public ofxWidget {
public:
  Label(const ofRectangle &rect, ofTrueTypeFont &font, string text) : ofxWidget(rect) , font(font){
    this->text = text;
  }
  virtual void drawImpl() {
    ofSetColor(255);
    ofFill();
    font.drawString(text, rect.x, rect.y + rect.height/2 +  font.getSize() / 2);
  }
private:
  string text;
  ofTrueTypeFont &font;
};

template <typename T>
class RefLabel : public ofxWidget {
public:
  RefLabel<T>(const ofRectangle &rect, ofTrueTypeFont &font, T &ref) : ofxWidget(rect) , font(font), ref(ref){
  }
  virtual void drawImpl() {
    ofSetColor(255);
    ofFill();
    font.drawString(ofToString(ref), rect.x, rect.y + rect.height/2 +  font.getSize() / 2);
  }
private:
  T &ref;
  ofTrueTypeFont &font;
};

class Slider : public ofxWidget {
public:
  Slider(const ofRectangle &rect, float value, float min, float max, float *ref, float step = 0.0) : ofxWidget(rect) {
    this->value = value;
    this->min   = min;
    this->max   = max;
    this->ref   = ref;
    this->step  = step;
    
    *this->ref  = value;
    dragging = false;
    state = 0;
  }
  
  virtual void drawImpl() {
    int barHeight   = 3;
    int sliderWidth = 5;
    
    // bar
    ofSetColor(122);
    ofFill();
    ofRect(rect.x, rect.y+rect.height / 2 - barHeight/2, rect.width, barHeight);
    // slider
    
    ofFill();
    float x = ofMap(value, min, max, rect.x, rect.x + rect.width);
    switch(state) {
      case 0:
        // normal
        ofSetColor(200);
        ofRect(x-sliderWidth/2, rect.y, sliderWidth, rect.height);
        break;
      case 1:
        // pressed
        ofSetColor(255);
        ofRect(x-sliderWidth/2-1, rect.y, sliderWidth+2, rect.height);
        break;
      case 2:
        // hovered
        ofSetColor(200);
        ofRect(x-sliderWidth/2-1, rect.y, sliderWidth+2, rect.height);
        break;
    }
    
    
  }
  virtual void mouseMovedImpl(int x, int y, bool inside) {
    if(inside)state = 2;
    else state = 0;
  }
  virtual void mouseDraggedImpl(int x, int y, int button, bool inside) {
    state = 0;
    if(dragging) {
      value = ofMap(x, 0, rect.width, min, max, true);
      if(step > 0) {
        value = (int)round(value / step) * step;
      }
      *ref  = value;
      state = 1;
    }
    
  }
  virtual void mousePressedImpl(int x, int y, int button, bool inside) {
    if(!inside)return;
    value = ofMap(x, 0, rect.width, min, max, true);
    if(step > 0) {
      value = (int)round(value / step) * step;
    }
    *ref  = value;
    dragging = true;
    state = 1;
  }
  virtual void mouseReleasedImpl(int x, int y, int button, bool inside) {
    if(inside)state = 2;
    else state = 0;
    dragging = false;
  }
private:
  int state;
  float value, min, max, step;
  float *ref;
  bool dragging;
};

class PushButton : public ofxWidget {
public:
  PushButton(const ofRectangle &rect, ofColor color=ofColor::white) : ofxWidget(rect) {
    state = 0;
    this->color = color;
  }
  
  virtual void drawImpl() {
    int offset = 3;
    
    // shadow
    ofSetColor(122);
    ofFill();
    ofRect(rect.x+offset, rect.y+offset, rect.width - offset, rect.height - offset);
    ofSetColor(color);
    ofFill();
    
    // button
    switch(state) {
      case 0:
        // normal
        ofRect(rect.x+1, rect.y+1, rect.width - offset, rect.height - offset);
        break;
      case 1:
        // pressed
        ofRect(rect.x+offset-1, rect.y+offset-1, rect.width - offset, rect.height - offset);
        break;
      case 2:
        // hovered
        ofRect(rect.x, rect.y, rect.width - offset, rect.height - offset);
        break;
    }
  }
  virtual void mouseMovedImpl(int x, int y, bool inside) {
    if(inside)state = 2;
    else state = 0;
  }
  virtual void mouseDraggedImpl(int x, int y, int button, bool inside) {
    if(inside)state = 2;
    else state = 0;
  }
  virtual void mousePressedImpl(int x, int y, int button, bool inside) {
    if(!inside)return;
    state = 1;
  }
  virtual void mouseReleasedImpl(int x, int y, int button, bool inside) {
    if(inside)state = 2;
    else state = 0;
  }
private:
  int state;
  ofColor color;
};

class ToggleButton : public ofxWidget {
public:
  ToggleButton(const ofRectangle &rect, bool &ref, ofColor color=ofColor::white) : ofxWidget(rect), ref(ref) {
    state = 0;
    this->color = color;
  }
  
  virtual void drawImpl() {
    int offset = 5;
    
    // shadow
    ofSetColor(122);
    ofFill();
    ofRect(rect.x, rect.y+offset, rect.width, rect.height - offset);
    ofSetColor(color);
    ofFill();
    
    // button
    int delta = 0;
    switch(state) {
      case 0:
        // normal
        delta = 0;
        break;
      case 2:
        // hovered
        delta = 1;
        break;
    }
    
    if(ref) {
      ofRect(rect.x, rect.y+offset-delta, rect.width , rect.height - offset);
    } else {
      ofRect(rect.x, rect.y+1-delta, rect.width, rect.height - offset);
    }
    
  }
  virtual void mouseMovedImpl(int x, int y, bool inside) {
    if(inside)state = 2;
    else state = 0;
  }
  virtual void mouseDraggedImpl(int x, int y, int button, bool inside) {
    if(inside)state = 2;
    else state = 0;
  }
  virtual void mousePressedImpl(int x, int y, int button, bool inside) {
    if(!inside)return;
    ref = !ref;
  }
  virtual void mouseReleasedImpl(int x, int y, int button, bool inside) {
    if(inside)state = 2;
    else state = 0;
  }
private:
  int state;
  bool &ref;
  ofColor color;
};

class Segment : public ofxWidget {
public:
  Segment(const ofRectangle &rect, int segNum, int &ref) : ofxWidget(rect), segmentNum(segNum), ref(ref){
    ref= 0;
    hoveredIdx = -1;
  }
  virtual void drawImpl() {
    int offset = 3;
    
    // base
    ofSetColor(122);
    ofFill();
    ofRect(rect.x, rect.y+offset, rect.width, rect.height-offset);
    
    // hovered
    if(hoveredIdx >= 0) {
      ofSetColor(200);
      ofFill();
      ofRect(rect.x + hoveredIdx * (rect.width / segmentNum), rect.y, rect.width / segmentNum, rect.height-offset);
    }
    
    // active
    ofSetColor(255);
    ofFill();
    ofRect(rect.x + ref * (rect.width / segmentNum), rect.y, rect.width / segmentNum, rect.height-offset);
  }
  virtual void mouseMovedImpl(int x, int y, bool inside) {
    if(inside) {
      hoveredIdx = (int)(x / (rect.width / segmentNum));
      hoveredIdx = ofClamp(hoveredIdx, 0, segmentNum-1);
    } else {
      hoveredIdx = -1;
    }
  }
  virtual void mouseDraggedImpl(int x, int y, int button, bool inside) {
  }
  virtual void mousePressedImpl(int x, int y, int button, bool inside) {
    if(!inside)return;
    ref = (int)(x / (rect.width / segmentNum));
    ref = ofClamp(ref, 0, segmentNum-1);
  }
  virtual void mouseReleasedImpl(int x, int y, int button, bool inside) {
  }
private:
  int state;
  int segmentNum;
  int &ref;
  int hoveredIdx;
};

#endif
