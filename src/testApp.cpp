#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0,0,0);

    w = 320;
    h = 240;

    movie.initGrabber(w, h, true);

    //reserve memory for cv images
    sourceImg.allocate(w, h);
    sourceImgGray.allocate(w, h);
    bgImg.allocate(w, h);
    bgImgGray.allocate(w, h);
    diffImg.allocate(w, h);
    maskedOutput.allocate(w, h, OF_IMAGE_COLOR_ALPHA);
    pixels.allocate(w, h, OF_IMAGE_COLOR_ALPHA);
}

//--------------------------------------------------------------
void testApp::update(){
    movie.update();
    
    if (movie.isFrameNew()) {
        //copy webcam pixels to sourceImg image
        sourceImg.setFromPixels(movie.getPixels(), w, h);
        sourceImgGray = sourceImg;
        sourceImgGray.blur(2);
        diffImg.absDiff(bgImgGray,sourceImgGray);
        diffImg.threshold(30, false);
        diffImg.blur(2);

        unsigned char * colorPixels;
        unsigned char * alphaPixels;
        alphaPixels = diffImg.getPixels();
        colorPixels = movie.getPixels();
        for (int i = 0; i < w; i++){
            for (int j = 0; j < h; j++){
                int pos = (j * w + i);
                pixels[pos*4  ] = colorPixels[pos * 3];
                pixels[pos*4+1] = colorPixels[pos * 3+1];
                pixels[pos*4+2] = colorPixels[pos * 3+2];
                pixels[pos*4+3] = alphaPixels[pos];
            }
        }
        
        maskedOutput.setFromPixels(pixels.getPixels(), w, h, OF_IMAGE_COLOR_ALPHA);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255,255,255);
    
    //draw all cv images
    sourceImg.draw(0,0);
    bgImg.draw(w,0);
    diffImg.draw(w*2, 0);
    ofEnableAlphaBlending();
    maskedOutput.draw(0, h);
    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    bgImg = sourceImg;
    bgImgGray = bgImg;
    bgImgGray.blur(2);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}