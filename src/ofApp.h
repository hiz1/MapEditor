#pragma once

#include "ofMain.h"
#include "ofxFrame.h"
#include "gui.h"
#include "Canvas.h"

// DONE:複数レイヤー対応
// TODO:複数タイルの同時選択に対応
// TODO:アンドゥ・リドゥ対応

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
