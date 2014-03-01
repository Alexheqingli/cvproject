//
//  draw.h
//  cvtest
//
//  Created by Alex Li on 2/15/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#ifndef __cvtest__draw__
#define __cvtest__draw__

#include <iostream>
#include <opencv2/opencv.hpp>

#endif /* defined(__cvtest__draw__) */

// Function prototype for detecting and drawing an object from an image
//IplImage* detect_and_draw( IplImage* img, CvSeq* faces, int scale);
void draw_face_rect(CvRect* r, IplImage* &img);