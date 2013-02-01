#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0,0,0);

    w = 640;
    h = 480;

    movie.initGrabber(w, h, true);

    //reserve memory for cv images
    sourceImg.allocate(w, h);
    sourceImgGray.allocate(w, h);
    bgImg.allocate(w, h);
    bgImgGray.allocate(w, h);
    diffImg.allocate(w, h);
    maskedOutput.allocate(w, h, OF_IMAGE_COLOR_ALPHA);
    maskedSave.allocate(w, h, OF_IMAGE_COLOR_ALPHA);
    maskedGrab.allocate(w, h, OF_IMAGE_COLOR_ALPHA);
    pixels.allocate(w, h, OF_IMAGE_COLOR_ALPHA);
    
    alphaPixels = new unsigned char[w*h];
    colorPixels = new unsigned char[w*h*3];
    savedPixels = new unsigned char[w*h*4];
    
//    bufferCount = 0;
//    bufferSize = BUFFERSIZE;
//	imgBuffer = new ofImage*[bufferSize];   // an array of pointers for the objects
//	
//    for (int i = 0; i < bufferSize; i++){
//        imgBuffer[i]->allocate(w, h, OF_IMAGE_COLOR_ALPHA);
//    }
    
    frameCount = 0;
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
        
        alphaPixels = diffImg.getPixels();
        
        if (frameCount > 30) {
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
            
//            imgBuffer[bufferCount]->setFromPixels(pixels.getPixels(), w, h, OF_IMAGE_COLOR_ALPHA);
//            
//            frameCount = 0;
//            bufferCount++;
//            if (bufferCount >= bufferSize) {
//                bufferCount = 0;
//            }
            
            
            maskedGrab.setFromPixels(pixels.getPixels(), w, h, OF_IMAGE_COLOR_ALPHA);
        }
        
        savedPixels = maskedSave.getPixels();
        for (int i = 0; i < w; i++){
            for (int j = 0; j < h; j++){
                int pos = (j * w + i);
                pixels[pos*4  ] = savedPixels[pos * 4];
                pixels[pos*4+1] = savedPixels[pos * 4+1];
                pixels[pos*4+2] = savedPixels[pos * 4+2];
                if (savedPixels[pos*4+3] > alphaPixels[pos]) {
                    pixels[pos*4+3] = alphaPixels[pos];
                } else {
                    pixels[pos*4+3] = savedPixels[pos*4+3];
                }
            }
        }
        
        maskedOutput.setFromPixels(pixels.getPixels(), w, h, OF_IMAGE_COLOR_ALPHA);
        
        frameCount++;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255,255,255);
    
    //draw all cv images
    bgImg.draw(0,0);
    sourceImg.draw(0,h,w/3,h/3);
    diffImg.draw(w/3, h,w/3,h/3);
    
    ofEnableAlphaBlending();
    maskedOutput.draw(0, 0);
    maskedSave.draw(w*2/3, h,w/3,h/3);
    //imgBuffer[bufferCount]->draw(w*2/3, h,w/3,h/3);
    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'r'){
        maskedSave.clone(maskedGrab);
    } else if (key == ' '){
        bgImg = sourceImg;
        bgImgGray = bgImg;
        bgImgGray.blur(2);
    }
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