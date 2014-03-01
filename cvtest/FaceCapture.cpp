//
//  FaceCapture.cpp
//  cvtest
//
//  Created by Xueqian Jiang on 2/19/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#include "FaceCapture.h"

void capture_frame(CvCapture *capture, IplImage* &img){
    // img is the destination
    
    img = cvQueryFrame(capture); // capture the image from the camera
    if (!img) {
        //error
        fprintf( stderr, "ERROR: Camera is not working");
    } // error checking
    cvFlip(img, img, 1); // flip the image so you see a mirror image of yourself
    
}