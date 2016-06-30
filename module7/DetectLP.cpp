/*
 * DetectLP.cpp
 *
 *  Created on: 21-Jun-2016
 *      Author: rohit
 */

//#include <stdio.h>
//#include <math.h>
//#include "opencv/cv.h"
//#include "opencv/highgui.h"
//
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/objdetect/objdetect.hpp"
//
//#include <iostream>
//#include <vector>
//#include <fstream>
//#include <sstream>
//#include <ctime>
//
//using namespace cv;
//using namespace std;


//int main(int argc, char* argv[]){
#include "DetectLP.h"


DetectLP::DetectLP(){
	namedWindow("Result");	//To show resulatnt image in this window.
	namedWindow("Crop");	//To show cropped image in this window.



	count = true;
	CarCount = 0;

	folderName = "../Cars_Plates/";

}



int DetectLP::loadCascade(string cascadeFile){
	if(!car_cascade.load(cascadeFile)){
		cout<< " Error while loading cascade file for face" << endl;
		return 1;
	}
}

void DetectLP::createCapturer(VideoCapture& capture){
//	VideoCapture capture(argv[1]);
	if (!capture.isOpened()) {
		cout<<"Error while opening camera"<<endl;
		//return 1;
	}
}


void DetectLP::createFolderToSvCroppedLP(string& folderName){


	string folderRemoveCommand = "rm -rf " + folderName;
	system(folderRemoveCommand.c_str());	//Remove the folder if already present
	string folderCreateCommand = "mkdir " + folderName;
	system(folderCreateCommand.c_str());	//Create the folder if not present.
}



void DetectLP::detectLPUseCascadeFile(VideoCapture& capture){
		capture.read(src_img);
cout<<"width "<< src_img.size().width << endl;
cout<<"height "<< src_img.size().height << endl;

		cvtColor(src_img,gray_img,CV_BGR2GRAY);
		equalizeHist(gray_img,gray_img);
		car_cascade.detectMultiScale(gray_img, cars, 1.11, 2, 0 | CASCADE_SCALE_IMAGE, Size(0,0));
}


void DetectLP::saveCroppedLP(string& folderName){
		for(int i = 0; i<cars.size(); i++){

//		    extract.removeImgCommand = "rm " + extract.dataSetPath + "c2.jpg";
//		    system(extract.removeImgCommand.c_str());
//		    cout<<extract.removeImgCommand<<endl;




		if((cars[i].width + 65) <= src_img.size().width- 20)
                	cars[i].width += 45;
		else if((cars[i].width + 55) <= src_img.size().width-20)
			cars[i].width += 45;
		else if((cars[i].width + 45) <= src_img.size().width-20)
                        cars[i].width += 45;
                else if((cars[i].width + 35) <= src_img.size().width-20)
                        cars[i].width += 35;
                else if((cars[i].width + 25) <= src_img.size().width-20)
                        cars[i].width += 25;
                else if((cars[i].width + 15) <= src_img.size().width -20)
                        cars[i].width += 15;


//		if((cars[i].height + 20) <= src_img.size().height)
//			cars[i].height +=20;
//                if((cars[i].height + 15) <= src_img.size().height)
//                        cars[i].height +=15;
//                else if((cars[i].height + 10) <= src_img.size().height)
//                        cars[i].height +=10;
                if((cars[i].height + 5) <= src_img.size().height)
                        cars[i].height += 5;


		Point pt1(cars[i].x + cars[i].width, cars[i].y+cars[i].height);
		Point pt2(cars[i].x, cars[i].y);

//			Mat faceROI = gray_img(faces[i]);
//			if(!faces.empty()){
//
//				//To grab faces and store in separate jpg files.
//				if((faces[i].y - 20) >= 0)
//					faces[i].y -= 20;
//
//				faces[i].width +=20;
//				faces[i].height+=20;
//
//				//Grab faces in sepaate matrix
//				Mat crop_img = src_img(cars[i]);
//
//				imshow("Crop", src_img(cars[i]));
//				//Write in jpg file grabbed face

//		contours_poly();
//		boundRect();
//		center();
//		boundRectCrop();
//		radius();

if(cars[i].x <= (src_img.size().width - cars[i].width) && cars[i].y <= (src_img.size().height - cars[i].height))
{
#ifdef SHOW_STEPS
				imshow("Crop", src_img(cars[i]));
#endif
				CarCount +=1;
				sprintf(imageToSave,"%scar_plate_%d.jpg",folderName.c_str(),CarCount);
				imwrite(imageToSave, src_img(cars[i]));



				cout<<endl<<endl;


					//string inpImage = argv[1];

				//	string resizeImageCommand = "convert " + inpImage + " -resize 4500 ../../module1/dataset/c2.jpg";
				//	system(resizeImageCommand.c_str());
				//	cout<<resizeImageCommand<<endl;
				//
				//	string resizeImage = dataSetPath + "c2.jpg";


					//std::vector<std::vector<cv::Point> > contours;

					bool check = true;
					extract.const_y1 = 0;
					extract.const_y2 = 0;
					extract.count_crop = 0;
					extract.count_temp = 0;
					extract.letter_count = 0;
					extract.binaryImage.release();
					extract.grayImage.release();
					extract.threholdImage.release();
					extract.drawing.release();
					extract.folderCreateCommand = "";
					extract.folderRemoveCommand = "";
					extract.removeImgCommand = "";
					extract.resizeImageCommand = "";
					extract.resizeImage = "";


					cout<<"----------------------createFolder4CroppedText()----------------------"<<endl;
					extract.createFolder4CroppedText(extract.folderName,extract.dataSetPath,extract.folderRemoveCommand, extract.folderCreateCommand,extract.removeImgCommand);
					cout<<"----------------------initilizeTesseract(api)----------------------"<<endl;
					extract.initilizeTesseract(extract.api);
					cout<<"----------------------binarizeLP----------------------"<<endl;
					//string InpImage(imageToSave);
					//cout<<"---------------"<<InpImage<<endl;
					check = extract.binarizeLP(imageToSave,extract.binaryImage, extract.grayImage , extract.threholdImage, extract.dataSetPath, extract.resizeImageCommand,extract.resizeImage, extract.count_convert, extract.imageToSave_convert);
					if(check == true){
					//InpImage = "";
					cout<<"----------------------findContours----------------------"<<endl;
					extract.findContours(extract.binaryImage,extract.contours);
					cout<<"----------------------recognizeTextInImg----------------------"<<endl;
					extract.recognizeTextInImg(extract.api, extract.binaryImage, extract.grayImage, extract.outText);
					cout<<"----------------------cropTextWithContourPoints----------------------"<<endl;
					extract.cropTextWithContourPoints(extract.api, extract.conf , extract.conf_avg, extract.threholdImage, imageToSave, extract.const_y1, extract.const_y2, extract.letter_count);
					extract.letter_count = 0;



					cout<<"----------------------drawRectOverSingleText----------------------"<<endl;
//					vector<vector<Point> > contours_poly( contours.size());
//					vector<Rect> boundRect( contours.size());
//					vector<Point2f>center( contours.size());
//					vector<Rect> boundRectCrop(contours.size());
//					vector<float>radius( contours.size());

					extract.contours_poly.resize(extract.contours.size());
					extract.boundRect.resize(extract.contours.size());
					extract.center.resize(extract.contours.size());
					extract.boundRectCrop.resize(extract.contours.size());
					extract.radius.resize(extract.contours.size());


					extract.drawRectOverSingleText(extract.binaryImage, extract.contours, extract.const_y1, extract.const_y2, extract.letter_count, extract.count_crop, extract.drawing, extract.contours_poly, extract.boundRect, extract.boundRectCrop, extract.center, extract.radius);


					cout<<"----------------------sort----------------------"<<endl;
					extract.sort(extract.count_crop, extract.contours, extract.boundRectCrop);
					cout<<"----------------------cropRectOverSingleText----------------------"<<endl;
					//extract.count_temp = 0;
					extract.cropRectOverSingleText(extract.count_crop, extract.threholdImage, extract.binaryImage, extract.count_temp, extract.drawing, extract.imageToSave_crop, extract.contours, extract.boundRectCrop);


					cout<<"===================================================================================================="<<endl;
					cout<<"##########################################--RecognizeLP--###########################################"<<endl;
					cout<<"===================================================================================================="<<endl;
					cout<<endl<<endl;

					string lpPath;
					detect.scene_plate.release();
					detect.lpr = "";
					detect.count_letters = 0;
					VideoCapture cap;
					lpPath = "../crop/crop%d.jpg";
					cap.open(lpPath);


					detect.captrureLP(cap);
					detect.readNRecognize(cap,detect.scene_plate, detect.lpr,detect.count_letters, detect.lpFile);
					//waitKey(1);
//				    extract.removeImgCommand = "rm " + extract.dataSetPath + "c2.jpg";
//				    system(extract.removeImgCommand.c_str());
//				    cout<<extract.removeImgCommand<<endl;


					//extract.count_crop = 0;
					//extract.count_temp = 0;
					memset(extract.imageToSave, 0, sizeof extract.imageToSave);
					memset(extract.imageToSave_crop, 0, sizeof extract.imageToSave_crop);
					}



//					boundRect.clear();
//					boundRectCrop.clear();
////
////					contours_poly.clear();
////					center.clear();
////					radius.clear();
////					contours.clear();
//
//boundRect.resize(0);
////center.resize(0);
//
//boundRectCrop.resize(0);
//std::vector<std::vector<cv::Point> >.swap(contours);
//contours_poly.resize(0);
//vector<float>.swap(radius);

//contours_poly();
//boundRect();
//center();
//boundRectCrop();
//
//vector<float>().swap(radius);

					//waitKey(0);





}
//
//
//


//void drawRectOvrLP()
				//                if(!eyes.empty())i
				//To show the rectangle on face
				//rectangle(src_img, pt1, pt2, Scalar(0,255,0),2, 8, 0);
	//		}
}
}
//#endif

void DetectLP::showResultLPOnFrame(){
#ifdef SHOW_STEPS
		if(!src_img.empty())
			imshow("Result", src_img);
#endif
		waitKey(30);
}
		//	int c = waitKey(30);
		//	if((char)c == 37)
		//	break;
	//}
DetectLP::~DetectLP(){
	//destroy GUI windows
	destroyAllWindows();

	//delete capture object
	//capture.release();
//                waitKey(0);
}
//	return 0;
//	}
