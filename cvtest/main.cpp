//
//  main.cpp
//  opencvtest
//
//  Created by Xueqian Jiang on 1/28/14.
//  Copyright (c) 2014 Xueqian Jiang. All rights reserved.
//

// include the necessary libraries
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
// Sample Application to demonstrate how Face detection can be done as a part of your source code.

// Include header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>


#include <Recognition.h>
#include <draw.h>
#include <FaceRecord.h>
#include <FaceCapture.h>
#include <morph.h>


// Create a string that contains the exact cascade name
const char* cascade_name =
"/opt/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
/*    "haarcascade_profileface.xml";*/



// Main function, defines the entry point for the program.
int main( int argc, char** argv )
{
    
    // Create a new named window with title: result
    cvNamedWindow( "result", 1 );
    
    CvCapture* capture =capture = cvCaptureFromCAM(-1); // capture from video device (Macbook iSight)
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 1000 );// set window size to 640
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 600 ); // set window size to 480
    
    // Create a sample image
    IplImage *imgCamera;
    IplImage *imgDrawn;
    IplImage *imgFace;
    
    cvNamedWindow("Window"); // create a window to display in

    while(1) {
        
        //*************************************************************************************/
        //Step 1: stream video. Video to images
        //*************************************************************************************/
        
        CvCapture* capture = cvCaptureFromCAM(-1); // capture from video device (Macbook iSight)
        
        // capture frame from video and then turn it into one single image-imgCamera
        capture_frame(capture, imgCamera);
        
        // allocate an image to be used later
        imgDrawn = cvCreateImage(cvGetSize(imgCamera), imgCamera->depth, imgCamera->nChannels);
        imgFace = cvCreateImage(cvSize(600, 600), imgCamera->depth, imgCamera->nChannels);
        
        // Create memory for calculations
        static CvMemStorage* storage = 0;
        
        // Allocate the memory storage
        storage = cvCreateMemStorage(0);
        
        // Clear the memory storage which was used before
        cvClearMemStorage( storage );
        
        // Create a new Haar classifier
        static CvHaarClassifierCascade* cascade = 0;
        
        // Load the HaarClassifierCascade
        cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
        char *name = new char[100];
        
        CvRect *r;
        CvSeq *faces;
        vector<int> number;
        float scale = 1.0/10; // how far do we want to scale down the haar detect objects images for speed
        
        //************************Implementation**************************
        // j is the iterator to keep track of the no of picture per person taken
        int j = 0;
        int i;
        capture_frame(capture, imgCamera);
        
        cvCopy(imgCamera, imgDrawn);
        
        find_faces(imgCamera, storage, cascade, faces, scale);
        
        // for each face found in the image
        for( i = 0; i < (faces ? faces->total : 0); i++ ){
            // get the rect from the sequence
            r = (CvRect*)cvGetSeqElem( faces, i );
            
            // resize the rectangle faces found
            CvRect x = cvRect(r->x/scale, r->y/scale, r->width/scale, r->height/scale);
            r = &x;
            
            draw_face_rect(r, imgDrawn); // draw the rectange around the face on the imgDrawn
            //crop_and_scale_face(imgCamera, imgFace, r);
            
            //j++;
            //sprintf(name,"/Users/alexli/Documents/Academics 2014 Winter/CV Proj/img%d.jpg",j);
            //cvSaveImage(name, imgFace);
            cvShowImage("Window", imgDrawn);
            
            char c = cvWaitKey(33); // press escape to quit
            if( c == 27 ) break;
            
        }
        
        
        // press escape to quit
        if( cvWaitKey(33) == 27 ) break;
    }
    
    cvReleaseCapture( &capture );
    
    // Release the image
    cvReleaseImage(&imgCamera);
    cvReleaseImage(&imgDrawn);
    cvReleaseImage(&imgFace);
    // Destroy the window previously created with filename: "result"
    cvDestroyWindow("window");
    
    // return 0 to indicate successfull execution of the program
    return 0;
}