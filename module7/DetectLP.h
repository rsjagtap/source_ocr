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

#include "ExtractSingleText.h"
#include "RecognizeLP.h"

using namespace cv;
using namespace std;

class DetectLP{

	CascadeClassifier car_cascade;
	ExtractSingleText extract;
	RecognizeLP detect;


	//VideoCapture capture(argv[1]);
	Mat src_img, gray_img, resize_src_img;
	vector<Rect> cars;
	Rect crop;	//To create resize the grabbed faces and store the result  in this variable.
	bool count;
	int CarCount;

	char imageToSave[50];
	string folderName;

//	std::vector<std::vector<cv::Point> > contours;
//	vector<vector<Point> > contours_poly;
//	vector<Rect> boundRect;
//	vector<Point2f>center;
//	vector<Rect> boundRectCrop;
//	vector<float>radius;


//	Point pt1;
//	Point pt2;
public:
	DetectLP();
	~DetectLP();
	int loadCascade(string cascadeFile);
	void createCapturer(VideoCapture& capture);
	void createFolderToSvCroppedLP();
	void detectLPUseCascadeFile(VideoCapture& capture);
	void saveCroppedLP();
	void showResultLPOnFrame();
	//void destroyNReleaseCapNWindow();
};

#endif /* DETECTLP_H_ */
