/*
 * DetectLP.h
 *
 *  Created on: 21-Jun-2016
 *      Author: rohit
 */

#ifndef DETECTLP_H_
#define DETECTLP_H_

#include <stdio.h>
#include <math.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <pthread.h>

#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>


#include <cstdlib>
#include "ExtractSingleText.h"
#include "RecognizeLP.h"

using namespace cv;
using namespace std;

class DetectLP{

public:
	CascadeClassifier car_cascade;
	int CarCount;
	string folderName;

	DetectLP();
	~DetectLP();
	int loadCascade(string cascadeFile);
	void createCapturer(VideoCapture& capture);
	void createFolderToSvCroppedLP();
	void detectLPUseCascadeFile(VideoCapture& capture, CascadeClassifier& car_cascade, ExtractSingleText* extract, RecognizeLP* detect,int& CarCount);
	void saveCroppedLP(string& folderName, vector<Rect>& cars, Mat& src_img, ExtractSingleText* extract, RecognizeLP* detect,int& CarCount);
	void showResultLPOnFrame(Mat& src_img);
	//void* convert_image(/*void* resizeImageCommand1);
	//void destroyNReleaseCapNWindow();
};

#endif /* DETECTLP_H_ */
