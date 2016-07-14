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
#include <unistd.h>

#include <baseapi.h>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

using namespace std;
using namespace cv;


class ExtractSingleText{
	public:
	//RNG rng(12345);

	//ExtractSingleText extract;
	tesseract::TessBaseAPI *api;// = new tesseract::TessBaseAPI();

	Mat binaryImage, grayImage, threholdImage, drawing;
	//string inpImage = argv[1];


        //string folderName = "crop";
    string resizeImageCommand;// = "convert " + inpImage + " -resize 4000 ../../module1/dataset/c2.jpg";
    string folderRemoveCommand;
    string folderCreateCommand;
    string removeImgCommand;
	//system(resizeImageCommand.c_str());
	//cout<<resizeImageCommand<<endl;

	string resizeImage;// = dataSetPath + "c2.jpg";


	int count_crop;// = 0;
	int count_temp;// = 0;
    float conf;// = 0;
    float conf_avg;// = 0;
	char *outText;
	char imageToSave[50];
	char imageToSave_crop[50];
	int count_convert;
	char imageToSave_convert[50];

	int letter_count;// = 0;
	int const_y1;// = 0;
	int const_y2;// = 0;
	string dataSetPath;
	string folderName;


	std::vector<std::vector<cv::Point> > contours;
	vector<vector<Point> > contours_poly;
	vector<Rect> boundRect;
	vector<Point2f>center;
	vector<Rect> boundRectCrop;
	vector<float>radius;

	ExtractSingleText();
	void createFolder4CroppedText(string& folderName, string& dataSetPath, string& folderRemoveCommand, string& folderCreateCommand,string& removeImgCommand);
	void initilizeTesseract(tesseract::TessBaseAPI* api);
	bool binarizeLP(string& imageToSave, Mat& binaryImage , Mat& grayImage, Mat& threholdImage, string& dataSetPath, string& resizeImageCommand,string& resizeImage, int& count_convert,char*  imageToSave_convert);
	void findContours(Mat& binaryImage, std::vector<std::vector<cv::Point> > &contours);
	void recognizeTextInImg(tesseract::TessBaseAPI* api, Mat& binaryImage, Mat& grayImage, char *outText);
	void cropTextWithContourPoints(tesseract::TessBaseAPI* api, float& conf , float& conf_avg, Mat& threholdImage, char imageToSave[],int& const_y1,int& const_y2,int& letter_count);
	void drawRectOverSingleText(Mat& binaryImage, std::vector<std::vector<cv::Point> > &contours,int& const_y1,int& const_y2,int& letter_count,int& count_crop, Mat& drawing, vector<vector<Point> > &contours_poly, vector<Rect> &boundRect, vector<Rect> &boundRectCrop, vector<Point2f> &center, vector<float> &radius);
	void sort(int& count_crop, std::vector<std::vector<cv::Point> > &contours, vector<Rect> &boundRectCrop);
	void cropRectOverSingleText(int& count_crop, Mat& threholdImage, Mat& binaryImage, int& count_temp, Mat& drawing, char imageToSave_crop[], std::vector<std::vector<cv::Point> > &contours, vector<Rect> &boundRectCrop);

};
#endif /* EXTRACTSINGLETEXT_H_ */
