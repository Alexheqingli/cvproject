//
//  Recognition.cpp
//  cvtest
//
//  Created by Alex Li on 2/15/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#include "Recognition.h"


void find_faces( IplImage* img, CvMemStorage* &storage, CvHaarClassifierCascade* &cascade, CvSeq* &faces, float scale){
    // this function finds the faces and returns a sequence
    
    cvClearMemStorage( storage ); // Clear the memory storage which was used before
    IplImage* tmp = cvCreateImage(cvSize(cvGetSize(img).width*scale, cvGetSize(img).height*scale), img->depth, img->nChannels);
    
    cvResize(img, tmp);
    
    if( !cascade ){
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        return;
    }// Check whether the cascade has loaded successfully. Else report and error and quit
    
    if( cascade )
    {
        float faceFraction = 1.0/16; // face can be a minimum size of 1/16 the size of the image
        int w = (int)(cvGetSize(tmp).width*faceFraction);
        int h = (int)(cvGetSize(tmp).height*faceFraction);
        faces = cvHaarDetectObjects( tmp, cascade, storage, 1.2, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(w, h)); // create sequence of images for however many faces are detected
    }
    
    // resize all of the rects
    
    cvReleaseImage(&tmp);
    
}
