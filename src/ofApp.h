#pragma once

#include "ofMain.h"
#include "ofxFrame.h"
#include "gui.h"
#include "Canvas.h"

// TODO:複数レイヤー対応
// TODO:複数タイルの同時選択に対応



class ToolFrame : public ofxFrame {
public:
  ToolFrame(const ofRectangle &rect, CanvasInfo *info) : ofxFrame(rect, ofVec2f(1000,32)) {
    this->info = info;
    font.loadFont("saxmono.ttf", 10);
//    ofPtr<PushButton> w(new PushButton(ofRectangle(2,0,28,28), ofColor::cyan));
//    addWidget(w);
    
    addWidget(ofPtr<Label>( new Label(ofRectangle(10,0,90,28), font, "size")));
    addWidget(ofPtr<Slider>(new Slider(ofRectangle(50,0,90,28), 1,1,10, &info->brush.size, 1)));
    addWidget(ofPtr<RefLabel<float> >(new RefLabel<float>(ofRectangle(150,0,40,28), font,info->brush.size)));
    addWidget(ofPtr<Label>( new Label(ofRectangle(210,0,30,28), font, "amt")));
    addWidget(ofPtr<Slider>(new Slider(ofRectangle(240,0,90,28), 1.0,0.01,1.0, &info->brush.amt, 0.01)));
    addWidget(ofPtr<RefLabel<float> >(new RefLabel<float>(ofRectangle(340,0,40,28), font,info->brush.amt)));
  }
private:
  CanvasInfo *info;
  ofTrueTypeFont font;
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
  
  CanvasInfo        *info;
  ofPtr<ToolFrame>   toolFrame;
  ofPtr<PickerFrame> pickerFrame;
  ofPtr<CanvasFrame>    mapFrame;
  
  
  const ofImage *image;
};
