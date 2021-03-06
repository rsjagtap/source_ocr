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
	//ExtractSingleText* extract;
	//RecognizeLP* detect;


	//VideoCapture capture(argv[1]);
	Mat src_img, gray_img, resize_src_img;
	vector<Rect> cars;
	Rect crop;	//To create resize the grabbed faces and store the result  in this variable.
	bool count;
	int CarCount;

	char imageToSave[50];
	string folderName;
	bool check;
	int even;
	int odd;
	int even_fix;
	int odd_fix;
	int count_check;


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
	void createFolderToSvCroppedLP(string& folderName);
	void detectLPUseCascadeFile(VideoCapture& capture, Mat& src_img, Mat& gray_img, vector<Rect>& cars, CascadeClassifier& car_cascade);
	void saveCroppedLP(string& folderName,bool& check, vector<Rect>& cars, Mat& src_img, int& CarCount, char imageToSave[], ExtractSingleText& extract, RecognizeLP& detect, int& even, int& odd, int& even_fix, int& odd_fix,int& count_check);
	void showResultLPOnFrame(Mat& src_img);
	//void* convert_image(/*void* resizeImageCommand1);
	//void destroyNReleaseCapNWindow();
};

#endif /* DETECTLP_H_ */
