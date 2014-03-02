//
//  Capture.cpp
//  cvtest
//
//  Created by Xueqian Jiang on 2/19/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#include "Capture.h"

/*    "haarcascade_profileface.xml";*/


void capture_frame(CvCapture *capture, IplImage* &img){
    // img is the destination
    
    img = cvQueryFrame(capture); // capture the image from the camera
    if (!img) {
        //error
        fprintf( stderr, "ERROR: Camera is not working");
    } // error checking
    cvFlip(img, img, 1); // flip the image so you see a mirror image of yourself
    
}

void draw_rect(IplImage* &img, CvRect* r, float scale){
    // this function draws the face rectangles on an image
    
    // resize the rectangle faces found
    CvRect x = cvRect(r->x/scale, r->y/scale, r->width/scale, r->height/scale);
    r = &x;
    CvPoint pt1, pt2;
    
    // Find the dimensions of the face,and scale it if necessary
    pt1.x = r->x;
    pt2.x = (r->x+r->width);
    pt1.y = r->y;
    pt2.y = (r->y+r->height);
    
    // Draw the rectangle in the input image
    cvRectangle( img, pt1, pt2, CV_RGB(255,0,0), 3, 8, 0 );
}

void capture_face(IplImage *imgCamera, IplImage* &imgFace, CvRect *r, float scale){
    
    // resize the rectangle faces found
    CvRect x = cvRect(r->x/scale, r->y/scale, r->width/scale, r->height/scale);
    r = &x;
    
    // get face image
    cvSetImageROI(imgCamera, *r);
    
    IplImage *tmp = cvCreateImage(cvSize(r->width, r->height), imgCamera->depth, imgCamera->nChannels);
    cvCopy(imgCamera, tmp); // the rize width to height ratio here is 1:1 for the built in classifier
    
    cvResetImageROI(imgCamera);
    
    // scale image size accordingly
    //    imgFace = NULL;
    cvResize(tmp, imgFace);
    
    cvReleaseImage(&tmp);
}

void save_face(CvRect* f, IplImage* imgCamera,IplImage* imgFace, float scale, int j) {
    const char* folder_name ="/Users/alexli/Documents/Academics 2014 Winter/CV Proj/Images";
        // capture the face image into imgFace for processing
        capture_face(imgCamera, imgFace, f, scale);
        j++;
        std::stringstream filename;
        filename<< folder_name << "/img" << j << ".jpg";
        char *name = (char *)filename.str().c_str();
        cvSaveImage(name, imgFace);
}


