//
//  FaceRecord.cpp
//  cvtest
//
//  Created by Alex Li on 2/15/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#include "FaceRecord.h"

void crop_and_scale_face(IplImage *imgCamera, IplImage* &imgFace, CvRect *r){
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
