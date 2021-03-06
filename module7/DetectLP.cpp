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
//	namedWindow("Result");	//To show resulatnt image in this window.
//	namedWindow("Crop");	//To show cropped image in this window.



	count = true;
	CarCount = 0;

	folderName = "../Cars_Plates/";
	check = true;
	even = 1;
	odd = 2;
	even_fix = 20;
	odd_fix = 20;
	count_check = 0;

	imageToSave[300] = {0};


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



void DetectLP::detectLPUseCascadeFile(VideoCapture& capture, Mat& src_img, Mat& gray_img, vector<Rect>& cars, CascadeClassifier& car_cascade){
		capture.read(src_img);
//cout<<"width "<< src_img.size().width << endl;
//cout<<"height "<< src_img.size().height << endl;

		cvtColor(src_img,gray_img,CV_BGR2GRAY);
		equalizeHist(gray_img,gray_img);
		car_cascade.detectMultiScale(gray_img, cars, 1.11, 2, 0 | CASCADE_SCALE_IMAGE, Size(0,0));
}

void* convert_image(void* command){
	const char *command1 = (char*)command;
	int status = system(command1);
    if (status == -1) {
    	perror("Could not fork: ");
    	exit(1);
    }
	cout<<"status_1------: "<<status<<endl;

}

void DetectLP::saveCroppedLP(string& folderName, bool& check, vector<Rect>& cars, Mat& src_img, int& CarCount, char imageToSave[], ExtractSingleText& extract, RecognizeLP& detect, int& even, int& odd, int& even_fix, int& odd_fix,int& count_check){
	check = true;
	FILE *file = NULL;
	imageToSave[300] = {0};
		for(int i = 0; i<cars.size(); i++){

//		    extract.removeImgCommand = "rm " + extract.dataSetPath + "c2.jpg";
//		    system(extract.removeImgCommand.c_str());
//		    cout<<extract.removeImgCommand<<endl;




		if((cars[i].width + 65) <= src_img.size().width- 20)
                	cars[i].width += 60;
		else if((cars[i].width + 55) <= src_img.size().width-20)
			cars[i].width += 55;
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
                if((cars[i].height + 10) <= src_img.size().height)
                        cars[i].height +=10;
                else if((cars[i].height + 5) <= src_img.size().height)
                        cars[i].height += 5;


		Point pt1(cars[i].x + cars[i].width, cars[i].y+cars[i].height);
		Point pt2(cars[i].x, cars[i].y);

//			Mat faceROI = gray_img(faces[i]);
//			if(!faces.empty()){
//command
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

if(cars[i].x <= (src_img.size().width - cars[i].width) && cars[i].y <= (src_img.size().height - cars[i].height) && cars[i].x >= 20 && cars[i].y >= 20 && (cars[i].y + cars[i].height) <= (src_img.size().height - 20) && (cars[i].x + cars[i].width) <= (src_img.size().width - 20))
{


#ifdef SHOW_STEPS
				imshow("Crop", src_img(cars[i]));
#endif
				CarCount +=1;
				//sprintf(imageToSave,"%scar_plate_%d.jpg",folderName.c_str(),CarCount);
				sprintf(imageToSave,"../Cars_Plates/car_plate_%d.jpg",CarCount);
				imwrite(imageToSave, src_img(cars[i]));
				//sleep(1);

//if(CarCount==82)
//sleep(10);


//char imageToSave_convert1[100];

//sprintf(imageToSave_convert1,"../%d.jpg",CarCount);
//	imwrite(imageToSave_convert, src_img(cars[i]));

//string inpImage(imageToSave);
string inpImage1(imageToSave);

stringstream ss;
ss << CarCount;
//string imageToSave11 = "/home/rohit/Desktop/source_ocr/module7/Cars_Plates/car_plate_" + ss.str() +".jpg";

//string imageToSave_convert1 = "/home/rohit/Desktop/source_ocr/module7/"+ ss.str() +".jpg";
//string resizeImageCommand1 = "convert /home/rohit/Desktop/source_ocr/module7/Cars_Plates/car_plate_" + ss.str() +".jpg -resize 4000 /home/rohit/Desktop/source_ocr/module7/"+ ss.str() +".jpg";
//string resizeImageCommand1 = "xterm -e convert "+ inpImage1 +" -resize 4000 ../"+ ss.str() +".jpg";
string resizeImageCommand1 = "convert "+ inpImage1 +" -resize 4000 ../"+ ss.str() +".jpg";
//string resizeImageCommand1 = "./Convert "+ ss.str();
const char *command = resizeImageCommand1.c_str();
int status = 0;
bool cvt_st = true;
//do{

///string check_file = "../Cars_Plates/car_plate_" + ss.str() +".jpg";
const char *command_check = inpImage1.c_str();

ifstream file1(command_check);
if(!file1){            // If the file was not found, then file is 0, i.e. !file=1 or true.
	cout<<"Image is --- False"<<endl;
    //return false;    // The file was not found.
}
else{                 // If the file was found, then file is non-0.
	cout<<"Image is --- True"<<endl;
    //return true;
}



cout<<"CarCount:\t"<<CarCount<<endl;
cout<<"even:\t"<<even<<endl;
cout<<"even_fix:\t"<<even_fix<<endl;
cout<<"count_check:\t"<<count_check<<endl;
cout<<"odd_fix:\t"<<odd_fix<<endl;
cout<<"odd:\t"<<odd<<endl;


//cout.flush();
cout<<endl;
//sleep(2);
//system(NULL);
cout<<endl;
//system("PAUSE");

//std::thread t(&DetectLP::convert_image, &resizeImageCommand1);
//pthread_t t1;
//pthread_create(&t1,NULL,&convert_image,(void*)command);
//pthread_join(t1,NULL);

status = system(command);
if (status == -1) {
	perror("Could not fork: ");
	exit(1);
}
//system("PAUSE");
cout<<endl;
//t.join();
//cout.flush();
//sleep(2);
cout<<"status_1------: "<<status<<endl;
/*
if(CarCount < (even * even_fix) && CarCount > count_check)
{
	status = system(command);
	sleep(2);
	cout<<"status_1------: "<<status<<endl;
	if(CarCount == (even * even_fix)-1){
		even +=2;
		count_check =odd * even_fix;
	}
}
else{

	//status = system(command);

	file = popen(command, "r");
	sleep(2);
	cout<<"status_2------: "<<status<<endl;
//		FILE *file = popen(command, "r");
	//	sleep(2);
		//pclose(file);
		//file = NULL;
		if(CarCount == (odd * odd_fix)){
			odd +=2;
			//count_check =even * even_fix;
		}

}*/

//}while(cvt_st == false);


//FILE *file = popen(command, "r");
////sleep(5);
//
//    fclose(file);
//
//
//
cout<<command<<endl;
//sleep(2);






//extract = new ExtractSingleText();
//detect = new RecognizeLP();

				cout<<endl<<endl;
			    check = true;

					//string inpImage = argv[1];

				//	string resizeImageCommand = "convert " + inpImage + " -resize 4500 ../../module1/dataset/c2.jpg";
				//	system(resizeImageCommand.c_str());
				//	cout<<resizeImageCommand<<endl;
				//
				//	string resizeImage = dataSetPath + "c2.jpg";


					//std::vector<std::vector<cv::Point> > contours;


					cout<<"----------------------createFolder4CroppedText()----------------------"<<endl;
					extract.createFolder4CroppedText(extract.folderName,extract.dataSetPath,extract.folderRemoveCommand, extract.folderCreateCommand,extract.removeImgCommand);
					cout<<"----------------------initilizeTesseract(api)----------------------"<<endl;
					extract.initilizeTesseract(extract.api);
					cout<<"----------------------binarizeLP----------------------"<<endl;
					//string InpImage(imageToSave);
					cout<<"---image read flag---:"<<check<<endl;
					//stringstream ss;
					//ss << CarCount;
					//string imageToSave11 = "/home/rohit/Desktop/source_ocr/module7/Cars_Plates/car_plate_" + ss.str() +".jpg";

					string imageToSave_convert1 = "/home/rohit/Desktop/source_ocr/module7/"+ ss.str() +".jpg";
					check = extract.binarizeLP(imageToSave_convert1,extract.binaryImage, extract.grayImage , extract.threholdImage, extract.dataSetPath, extract.resizeImageCommand,extract.resizeImage, extract.count_convert, extract.imageToSave_convert);
					if(check == true){
					cout<<"---image read flag if---:"<<check<<endl;
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
					//memset(extract.imageToSave, 0, sizeof extract.imageToSave);
					//memset(extract.imageToSave_crop, 0, sizeof extract.imageToSave_crop);
					//check =false;



//										extract.contours_poly.resize(0);
//										extract.boundRect.resize(0);
//										extract.center.resize(0);
//										extract.boundRectCrop.resize(0);
//										extract.radius.resize(0);
//
//
//										extract.contours_poly.shrink_to_fit();
//										extract.boundRect.shrink_to_fit();
//										extract.center.shrink_to_fit();
//										extract.boundRectCrop.shrink_to_fit();
//										extract.radius.shrink_to_fit();

															vector<vector<Point> > contours_poly(0);
															vector<Rect> boundRect(0);
															vector<Point2f>center(0);
															vector<Rect> boundRectCrop(0);
															vector<float>radius(0);

															extract.contours_poly.swap(contours_poly);
															extract.boundRect.swap(boundRect);
															extract.center.swap(center);
															extract.boundRectCrop.swap(boundRectCrop);
															extract.radius.swap(radius);


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
					}
					else{

						cout<<"---image read flag else---:"<<check<<endl;
						//check =true;
						//continue;
						//break;
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


//					delete extract;
//					delete detect;


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

void DetectLP::showResultLPOnFrame(Mat& src_img){
#ifdef SHOW_STEPS
		if(!src_img.empty())
			imshow("Result", src_img);
#endif
//		waitKey(1);
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
