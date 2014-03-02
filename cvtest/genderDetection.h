//
//  genderDetection.h
//  cvtest
//
//  Created by Xueqian Jiang on 2/22/14.
//  Copyright (c) 2014 Alex Li. All rights reserved.
//

#ifndef __cvtest__genderDetection__
#define __cvtest__genderDetection__

#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <fstream>
#include <sstream>

using namespace std;
using namespace cv;

#endif /* defined(__cvtest__genderDetection__) */


// the input is a face and the output will be statement on the window, whether this person is female or male
// input: a face rectangle
// output:  a string indicating  "Female" or "Male"
// processes: does the person once the person is in view, this will show up immediately

// this part is for pca method before the actual boost

int detect(Ptr<FaceRecognizer> model, string filename);

Ptr<FaceRecognizer> gender_detection(const string& filename);

static Mat norm_0_255(InputArray _src);

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') ;