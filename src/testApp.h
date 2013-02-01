#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        
        ofVideoGrabber movie;
        
        ofxCvColorImage sourceImg,bgImg;
        ofxCvGrayscaleImage sourceImgGray,bgImgGray,diffImg;
        ofPixels pixels;
        ofImage maskedOutput, maskedSave, maskedGrab;
    
        unsigned char * colorPixels;
        unsigned char * alphaPixels;
        unsigned char * savedPixels;
    
//        ofImage** imgBuffer;
    
        int w,h,bufferSize,bufferCount,frameCount;
};
