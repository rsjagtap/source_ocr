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
	//RNG rng(12345);

	void createFolder4CroppedText();
	void initilizeTesseract(tesseract::TessBaseAPI* api);
	void binarizeLP(string inpImage, Mat& binaryImage , Mat& grayImage, Mat& threholdImage);
	void findContours(Mat& binaryImage, std::vector<std::vector<cv::Point> > &contours);
	void recognizeTextInImg(tesseract::TessBaseAPI* api, Mat& binaryImage, Mat& grayImage, char *outText);
	void cropTextWithContourPoints(tesseract::TessBaseAPI* api, float& conf , float& conf_avg, Mat& threholdImage, char* imageToSave,int& const_y1,int& const_y2,int& letter_count);
	void drawRectOverSingleText(Mat& binaryImage, std::vector<std::vector<cv::Point> > &contours,int& const_y1,int& const_y2,int& letter_count,int& count_crop, Mat& drawing, vector<vector<Point> > &contours_poly, vector<Rect> &boundRect, vector<Rect> &boundRectCrop, vector<Point2f> &center, vector<float> &radius);
	void sort(int& count_crop, std::vector<std::vector<cv::Point> > &contours, vector<Rect> &boundRectCrop);
	void cropRectOverSingleText(int& count_crop, Mat& threholdImage, Mat& binaryImage, int& count_temp, Mat& drawing, char* imageToSave_crop, std::vector<std::vector<cv::Point> > &contours, vector<Rect> &boundRectCrop);

};
#endif /* EXTRACTSINGLETEXT_H_ */
