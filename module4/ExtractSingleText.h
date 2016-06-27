/*
 * ExtractSingleText.h
 *
 *  Created on: 17-Jun-2016
 *      Author: rohit
 */

#ifndef EXTRACTSINGLETEXT_H_
#define EXTRACTSINGLETEXT_H_
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

#include <baseapi.h>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

using namespace std;
using namespace cv;


class ExtractSingleText{

public:
	int count_crop;
	int count_temp;
	float conf;
	float conf_avg;
	char *outText;
	char imageToSave[50];
	char imageToSave_crop[50];

	int letter_count;
	int const_y1;
	int const_y2;
	string dataSetPath;

	Mat binaryImage, grayImage, threholdImage, drawing;

	tesseract::TessBaseAPI *api;
public:
	std::vector<std::vector<cv::Point> > contours;
	vector<vector<Point> > contours_poly;
	vector<Rect> boundRect;
	vector<Point2f>center;
	vector<Rect> boundRectCrop;
	vector<float>radius;


	public:
	//RNG rng(12345);
	ExtractSingleText();
	~ExtractSingleText();
	void createFolder4CroppedText();
	void initilizeTesseract();
	void binarizeLP(string inpImage);
	void findContours(std::vector<std::vector<cv::Point> > &contours);
	void recognizeTextInImg();
	void cropTextWithContourPoints();
	void drawRectOverSingleText(std::vector<std::vector<cv::Point> > &contours, vector<vector<Point> > &contours_poly, vector<Rect> &boundRect, vector<Rect> &boundRectCrop, vector<Point2f> &center, vector<float> &radius);
	void sort(std::vector<std::vector<cv::Point> > &contours, vector<Rect> &boundRectCrop);
	void cropRectOverSingleText(std::vector<std::vector<cv::Point> > &contours, vector<Rect> &boundRectCrop);

};
#endif /* EXTRACTSINGLETEXT_H_ */
