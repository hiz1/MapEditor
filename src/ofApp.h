#pragma once

#include "ofMain.h"
#include "ofxFrame.h"
#include "gui.h"
#include "Canvas.h"

//-------------------------------------------------------
//                   PHASE 1
//-------------------------------------------------------
// DONE:複数レイヤー対応
// DONE:アンドゥ・リドゥ対応
// DONE:複数タイルの同時選択に対応
// DONE:消しゴム実装
// TODO:スポイト機能の複数タイル同時選択
// TODO:散布ブラシにて、タイルグループ単位で散布する
// TODO:複数タイル選択時、タイルグループ単位で描画する
// TODO:マップ情報をファイルに保存・読み込み

//-------------------------------------------------------
//                   PHASE 2
//-------------------------------------------------------
// TODO:タイルセット設定
// TODO:オートタイル

//-------------------------------------------------------
//                   PHASE 3
//-------------------------------------------------------
// TODO:オートレイヤ
// TODO:散布ブラシの詳細設定（形状・散布の分布）

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
  bool  commandKey, shiftKey;
};
