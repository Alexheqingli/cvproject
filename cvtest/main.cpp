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
#include <Capture.h>
//#include <genderDetection.h>

using namespace std;

// Create a string that contains the exact cascade name
const char* cascade_name =
"/opt/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";

// Main function, defines the entry point for the program.
int main( int argc, char** argv )
{
    Ptr<FaceRecognizer>  model;
    //gender_detection("/Users/xueqianjiang/Desktop/cvproject/male.txt"); // CHANGE THIS
    
    // memeory allocation
    static CvMemStorage* storage = 0;
    storage = cvCreateMemStorage(0);
    static CvMemStorage* storage2 = 0;
    storage2 = cvCreateMemStorage(0);
    
    // Create a new named window with title: result
    cvNamedWindow("Window"); // create a window to display in
    CvCapture* capture = capture = cvCaptureFromCAM(-1); // capture from video device (Macbook iSight)
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 1000 );// set window size to 640
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 600 ); // set window size to 480
    
    // Declare images
    IplImage *imgCamera; // captured from camera
    IplImage *imgCamera_last; // last campera image
    IplImage *imgDrawn; // image with drawing (rect containing faces)
    IplImage *imgFace; // face picture extracted from the camera
    CvRect *r; // rects containing faces
    CvSeq *faces = cvCreateSeq(0, sizeof(CvSeq), sizeof(CvRect), storage); ; // sequnece of faces in the camera image - CURRENT
    CvSeq *faces_last = cvCreateSeq(0, sizeof(CvSeq), sizeof(CvRect), storage2); // sequnece of faces in the camera image - LAST FRAME
    float scale = 1.0/5; // how far do we want to scale down the haar detect objects images for speed
    
    // Create a new Haar classifier
    static CvHaarClassifierCascade* cascade = 0;
    cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
    
    // file name where to save the file
    std::stringstream filename;
    
    int counter = 1;
    int filecounter = 1;
    while(1) {
        //*************************************************************************************/
        //Step 1: stream video. Video to images
        //*************************************************************************************/
        
        // capture frame from video and then turn it into one single image-imgCamera
        capture_frame(capture, imgCamera);
        
        // allocate an image to be used later
        imgDrawn = cvCreateImage(cvGetSize(imgCamera), imgCamera->depth, imgCamera->nChannels);
        imgFace = cvCreateImage(cvSize(600, 600), imgCamera->depth, imgCamera->nChannels);
        cvCopy(imgCamera, imgDrawn);
        
        if (counter == 10) { // take action for every 10 frames

            counter = 1;
            //*************************************************************************************/
            //Step 2: Detection
            //*************************************************************************************/
            find_faces(imgCamera, storage, cascade, faces, scale);
            //printf("Last faces seq had %d faces detected. \n",faces_last->total);
            
            //*************************************************************************************/
            //Step 4: Draw every face in the picture
            //*************************************************************************************/
            
            // for each face found in the image
            for(int i = 0; i < (faces ? faces->total : 0); i++ ){
                // get the rect from the sequence
                r = (CvRect*)cvGetSeqElem(faces, i);
                
                // draw the rectange around the face on the imgDrawn
                draw_rect(imgDrawn, r, scale);
            }
            
            cvShowImage("Window", imgDrawn);
            // press escape to quit
            if( cvWaitKey(33) == 27 ) break;
            //*************************************************************************************/
            //Step 3: Recognize the new faces
            //*************************************************************************************/
            //TO DO: Combined the following into a funciton: match_faces(faces_new, faces, faces_last, lastspotted, currentspotted, imgCamera);
            for(int i = 0; i < (faces ? faces->total : 0); i++ ){
                // get the rect from the sequence
                r = (CvRect*)cvGetSeqElem(faces, i);
                if (faces_last->total == 0) {
                    cout<<"a face appeared: "<<"there are total faces of "<<faces->total<<"\n";
                    save_face(r, imgCamera, imgFace, scale, filecounter);
                    filecounter++;
                    float eig[3];
                    eig[0] = 0.5;
                    eig[1] = 1.5;
                    eig[2] = 2.6;
                    send_record(2.0, eig, 3);

                    //report_faces(filecounter, faces_new->total, model); // report new faces stored starting from filecounter
                }
                else {
                    for(int k = 0; k < (faces_last ? faces_last->total : 0); k++ ){
                        CvRect *r_last = (CvRect*)cvGetSeqElem(faces_last, k);
                        if (!same_face(r, r_last, imgCamera, imgCamera_last, i, k)) {
                            save_face(r, imgCamera, imgFace, scale, filecounter);
                            filecounter++;
                            //report_faces(filecounter, faces->total, model); // report new faces stored starting from filecounter
                        }
                    }
                }
            }
            
            
            
            
            
            
            
            
            
            
            
            
            
            //cvClearMemStorage(storage2);
            while (faces_last->total >0) {
                cvSeqPop(faces_last);}
            
            for(int i = 0; i < (faces ? faces->total : 0); i++ ){
                // get the rect from the sequence
                r = (CvRect*)cvGetSeqElem(faces, i);
                cvSeqPush(faces_last, r);
            }
            //cout << "face_last:" << faces_last->total << "\n";}
            cvClearMemStorage(storage);
        }
        counter++;
        imgCamera_last = imgCamera;
        
    }
    
    cvReleaseCapture( &capture );
    cvReleaseImage(&imgCamera);
    cvReleaseImage(&imgDrawn);
    cvReleaseImage(&imgFace);
    cvDestroyWindow("window");
    
    // return 0 to indicate successfull execution of the program
    return 0;
}