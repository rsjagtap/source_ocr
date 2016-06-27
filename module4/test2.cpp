/*
 * test2.cpp
 *
 *  Created on: 17-Jun-2016
 *      Author: rohit
 */

#include "ExtractSingleText.h"
#include "RecognizeLP.h"


//string dataSetPath = "/home/rohit/Desktop/source_ocr/module1/dataset/";

int main( int argc, char** argv ){



	cout<<"===================================================================================================="<<endl;
	cout<<"########################################--ExtractSingleText--#######################################"<<endl;
	cout<<"===================================================================================================="<<endl;
	cout<<endl<<endl;
	ExtractSingleText extract;
	RecognizeLP detect;

	string inpImage = argv[1];

//	string resizeImageCommand = "convert " + inpImage + " -resize 4500 ../../module1/dataset/c2.jpg";
//	system(resizeImageCommand.c_str());
//	cout<<resizeImageCommand<<endl;
//
//	string resizeImage = dataSetPath + "c2.jpg";


	std::vector<std::vector<cv::Point> > contours;


	cout<<"----------------------createFolder4CroppedText()----------------------"<<endl;
	extract.createFolder4CroppedText();
	cout<<"----------------------initilizeTesseract(api)----------------------"<<endl;
	extract.initilizeTesseract();
	cout<<"----------------------binarizeLP----------------------"<<endl;
	extract.binarizeLP(inpImage);
	cout<<"----------------------findContours----------------------"<<endl;
	extract.findContours(extract.contours);
	cout<<"----------------------recognizeTextInImg----------------------"<<endl;
	extract.recognizeTextInImg();
	cout<<"----------------------cropTextWithContourPoints----------------------"<<endl;
	extract.cropTextWithContourPoints();



	cout<<"----------------------drawRectOverSingleText----------------------"<<endl;
//	vector<vector<Point> > contours_poly( contours.size() );
//	vector<Rect> boundRect( contours.size() );
//	vector<Rect> boundRectCrop(contours.size());
//	vector<Point2f>center( contours.size() );
//	vector<float>radius( contours.size() );

	extract.contours_poly.resize(extract.contours.size());
	extract.boundRect.resize(extract.contours.size());
	extract.center.resize(extract.contours.size());
	extract.boundRectCrop.resize(extract.contours.size());
	extract.radius.resize(extract.contours.size());

	extract.drawRectOverSingleText(extract.contours, extract.contours_poly, extract.boundRect, extract.boundRectCrop, extract.center, extract.radius);


	cout<<"----------------------sort----------------------"<<endl;
	extract.sort(extract.contours, extract.boundRectCrop);
	cout<<"----------------------cropRectOverSingleText----------------------"<<endl;
	extract.cropRectOverSingleText(extract.contours, extract.boundRectCrop);


	cout<<"===================================================================================================="<<endl;
	cout<<"##########################################--RecognizeLP--###########################################"<<endl;
	cout<<"===================================================================================================="<<endl;
	cout<<endl<<endl;

	string lpPath;
	VideoCapture cap;
	lpPath = "/home/rohit/Desktop/source_ocr/module4/crop/crop%d.jpg";
	cap.open(lpPath);

	detect.captrureLP(cap);
	detect.readNRecognize(cap);

	waitKey(0);
}
