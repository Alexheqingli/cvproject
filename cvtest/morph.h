//
//  Morph.h
//  cvtest
//
//  Created by Xueqian Jiang on 2/20/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#ifndef __cvtest__Morph__
#define __cvtest__Morph__

#include <iostream>
#include <opencv2/opencv.hpp>

#include <fstream>
#include <vector>
#include <cmath>
#include <assert.h>

#endif /* defined(__cvtest__Morph__) */

#define mp make_pair
#define pb push_back

#define A 0.1
#define P 1
#define B 1
#define FRAMENUM 80
#define GAIN 10.0


using namespace std;
using namespace cv;


inline double sigmoid(double x);

inline double lengthSquare (double x, double y);

inline double length (double x, double y);


CvPoint getMappingPoint (CvPoint p, CvPoint q, double u, double v);

