//
//  Recognition.h
//  cvtest
//
//  Created by Alex Li on 2/15/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#ifndef __cvtest__Recognition__
#define __cvtest__Recognition__

#include <iostream>
#include <opencv2/opencv.hpp>

#endif /* defined(__cvtest__Recognition__) */

// Function to detect faces in an image
//CvSeq* face_detect( IplImage* img );


void find_faces( IplImage* img, CvMemStorage* &storage, CvHaarClassifierCascade* &cascade, CvSeq* &faces, float scale);