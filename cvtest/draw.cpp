//
//  draw.cpp
//  cvtest
//
//  Created by Alex Li on 2/15/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#include "draw.h"
#include <Recognition.h>


void draw_face_rect(CvRect* r, IplImage* &img){
    // this function draws the face rectangles on an image
    
    CvPoint pt1, pt2;
    
    // Find the dimensions of the face,and scale it if necessary
    pt1.x = r->x;
    pt2.x = (r->x+r->width);
    pt1.y = r->y;
    pt2.y = (r->y+r->height);
    
    // Draw the rectangle in the input image
    cvRectangle( img, pt1, pt2, CV_RGB(255,0,0), 3, 8, 0 );
}
