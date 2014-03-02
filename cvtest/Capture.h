//
//  FaceCapture.h
//  cvtest
//
//  Created by Xueqian Jiang on 2/19/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#ifndef __cvtest__Capture__
#define __cvtest__Capture__

#include <iostream>
#include <opencv2/opencv.hpp>

#endif /* defined(__cvtest__FaceCapture__) */

//save the image from the captured frame
void capture_frame(CvCapture *capture, IplImage* &img);

// draw the rectangle r on image
void draw_rect(IplImage* &img, CvRect* r, float scale);

//crop the face image according to r, and save it to ImgFace after scaling
void capture_face(IplImage *imgCamera, IplImage* &imgFace, CvRect *r, float scale);

void save_face(CvRect* f, IplImage* imgCamera, IplImage* imgFace,float scale, int j);