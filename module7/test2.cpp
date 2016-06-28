/*
 * test2.cpp
 *
 *  Created on: 17-Jun-2016
 *      Author: rohit
 */

#include "ExtractSingleText.h"
#include "RecognizeLP.h"


string dataSetPath = "/home/rohit/Desktop/source_ocr/module1/dataset/";

int main( int argc, char** argv ){



cout<<"===================================================================================================="<<endl;
cout<<"########################################--ExtractSingleText--#######################################"<<endl;
cout<<"===================================================================================================="<<endl;
cout<<endl<<endl;
	ExtractSingleText extract;
	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();

	Mat binaryImage, grayImage, threholdImage, drawing;
	string inpImage = argv[1];
	

//        //string folderName = "crop";
//        string resizeImageCommand = "convert " + inpImage + " -resize 4000 ../../module1/dataset/c2.jpg";
//	system(resizeImageCommand.c_str());
//	cout<<resizeImageCommand<<endl;
//
//	string resizeImage = dataSetPath + "c2.jpg";


	int count_crop = 0;
	int count_temp = 0;
    float conf = 0;
    float conf_avg = 0;
	char *outText;
	char imageToSave[50];
	char imageToSave_crop[50];

	int letter_count = 0;
	int const_y1 = 0;
	int const_y2 = 0;

	std::vector<std::vector<cv::Point> > contours;
//	vector<vector<Point> > contours_poly( contours.size() );
//	vector<Rect> boundRect( contours.size() );
//	vector<Rect> boundRectCrop(contours.size());
//	vector<Point2f>center( contours.size() );
//        vector<float>radius( contours.size() );


	extract.createFolder4CroppedText();
	cout<<"----------------------initilizeTesseract(api)----------------------"<<endl;
	extract.initilizeTesseract(api);
	cout<<"----------------------binarizeLP----------------------"<<endl;
	extract.binarizeLP(inpImage, binaryImage, grayImage , threholdImage);
	cout<<"----------------------findContours----------------------"<<endl;
	extract.findContours(binaryImage, extract.contours);
	cout<<"----------------------recognizeTextInImg----------------------"<<endl;
	extract.recognizeTextInImg(api, binaryImage, grayImage, outText);
	cout<<"----------------------cropTextWithContourPoints----------------------"<<endl;
	extract.cropTextWithContourPoints(api, conf , conf_avg, threholdImage, imageToSave, const_y1, const_y2, letter_count);
	cout<<"----------------------drawRectOverSingleText----------------------"<<endl;
//	vector<vector<Point> > contours_poly( contours.size() );
//        vector<Rect> boundRect( contours.size() );
//        vector<Rect> boundRectCrop(contours.size());
//        vector<Point2f>center( contours.size() );
//        vector<float>radius( contours.size() );
	extract.contours_poly.resize(extract.contours.size());
	extract.boundRect.resize(extract.contours.size());
	extract.center.resize(extract.contours.size());
	extract.boundRectCrop.resize(extract.contours.size());
	extract.radius.resize(extract.contours.size());

	extract.drawRectOverSingleText(binaryImage, extract.contours, const_y1, const_y2, letter_count, count_crop, drawing, extract.contours_poly, extract.boundRect, extract.boundRectCrop, extract.center, extract.radius);
	cout<<"----------------------sort----------------------"<<endl;
	extract.sort(count_crop, extract.contours, extract.boundRectCrop);
	cout<<"----------------------cropRectOverSingleText----------------------"<<endl;
	extract.cropRectOverSingleText(count_crop, threholdImage, binaryImage, count_temp, drawing, imageToSave_crop, extract.contours, extract.boundRectCrop);

cout<<"===================================================================================================="<<endl;
cout<<"##########################################--RecognizeLP--###########################################"<<endl;
cout<<"===================================================================================================="<<endl;
cout<<endl<<endl;
        RecognizeLP detect;

        Mat scene_plate;
        string lpr = "";
        int count_letters = 0;
        //        int count_non_letters = 0;
        string lpPath = "/home/rohit/Desktop/source_ocr/module7/crop/crop%d.jpg";
        VideoCapture cap(lpPath);
        detect.captrureLP(cap);
        detect.readNRecognize(cap,scene_plate, lpr,count_letters,detect.lpFile);




	waitKey(0);
}
