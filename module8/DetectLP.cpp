/*
 * DetectLP.cpp
 *
 *  Created on: 21-Jun-2016
 *      Author: rohit
 */


#include "DetectLP.h"


DetectLP::DetectLP(){
#ifdef SHOW_STEPS
	namedWindow("Result");	//To show resulatnt image in this window.
	namedWindow("Crop");	//To show cropped image in this window.
#endif
	CarCount = 0;
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


void DetectLP::createFolderToSvCroppedLP(){


	string folderName = "../Cars_Plates/";
	string folderRemoveCommand = "rm -rf " + folderName;
	system(folderRemoveCommand.c_str());	//Remove the folder if already present
	string folderCreateCommand = "mkdir " + folderName;
	system(folderCreateCommand.c_str());	//Create the folder if not present.
}



void DetectLP::detectLPUseCascadeFile(VideoCapture& capture, CascadeClassifier& car_cascade, ExtractSingleText* extract, RecognizeLP* detect,int& CarCount, Mat& src_img){

		Mat /*src_img,*/ gray_img;
		string folderName = "../Cars_Plates/";

		//capture.read(src_img);
//		capture >> src_img;


		vector<Rect> cars;
		gray_img = src_img.clone();
		cvtColor(src_img,gray_img,CV_BGR2GRAY);
		equalizeHist(gray_img,gray_img);
		car_cascade.detectMultiScale(gray_img, cars, 1.11, 2, 0 | CASCADE_SCALE_IMAGE, Size(0,0));


		saveCroppedLP(folderName, cars, src_img, extract, detect,CarCount);

		showResultLPOnFrame(src_img);

		//destroyAllWindows();

		cars.clear();
		src_img.release();
		gray_img.release();

}

void DetectLP::saveCroppedLP(string& folderName, vector<Rect>& cars, Mat& src_img , ExtractSingleText* extract, RecognizeLP* detect,int& CarCount){
	bool check = true;

	char imageToSave[50] = {0};
	int even = 1;
	int odd = 2;
	int even_fix = 20;
	int odd_fix = 20;
	int count_check = 0;


		for(int i = 0; i<cars.size(); i++){

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

#if 1
//if(CarCount > 79)
{

string inpImage1(imageToSave);

stringstream ss;
ss << CarCount;


//string imageToSave11 = "/home/rohit/Desktop/source_ocr/module7/Cars_Plates/car_plate_" + ss.str() +".jpg";
//string imageToSave_convert1 = "/home/rohit/Desktop/source_ocr/module7/"+ ss.str() +".jpg";
//string resizeImageCommand1 = "convert /home/rohit/Desktop/source_ocr/module7/Cars_Plates/car_plate_" + ss.str() +".jpg -resize 4000 /home/rohit/Desktop/source_ocr/module7/"+ ss.str() +".jpg";
//string resizeImageCommand1 = "xterm -e convert "+ inpImage1 +" -resize 4000 ../"+ ss.str() +".jpg";
string resizeImageCommand1 = "convert "+ inpImage1 +" -resize 4000 ../"+ ss.str() +".jpg";
//string resizeImageCommand1 = "convert "+ inpImage1 +" -resize 4000 ../c2.jpg";
//string resizeImageCommand1 = "./Convert "+ ss.str();
const char *command = resizeImageCommand1.c_str();

int status = 0;
bool cvt_st = true;

const char *command_check = inpImage1.c_str();


cout<<"CarCount:\t"<<CarCount<<endl;
cout<<"even:\t"<<even<<endl;
cout<<"even_fix:\t"<<even_fix<<endl;
cout<<"count_check:\t"<<count_check<<endl;
cout<<"odd_fix:\t"<<odd_fix<<endl;
cout<<"odd:\t"<<odd<<endl;

cout<<endl;
cout<<endl;


status = system(command);

if (status == -1) {
	perror("Could not fork: ");
	exit(1);
}

cout<<endl;

cout<<"status_1------: "<<status<<endl;

cout<<command<<endl;


extract = new ExtractSingleText();
detect = new RecognizeLP();

				cout<<endl<<endl;
			    check = true;


					std::vector<std::vector<cv::Point> > contours;

					int count_crop= 0;
					int count_temp = 0;
				    float conf = 0;
				    float conf_avg  = 0;
					char *outText = new char();
					char imageToSave[50];
					char imageToSave_crop[50];

					char imageToSave_convert[50];

					int letter_count  = 0;
					int const_y1 = 0;
					int const_y2  = 0;
					string dataSetPath = "/home/rohit/Desktop/source_ocr/module8";

					Mat binaryImage, grayImage, threholdImage, drawing;
					tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();


					cout<<"----------------------createFolder4CroppedText()----------------------"<<endl;
					extract->createFolder4CroppedText(dataSetPath);
					cout<<"----------------------initilizeTesseract(api)----------------------"<<endl;
					extract->initilizeTesseract(api);
					cout<<"----------------------binarizeLP----------------------"<<endl;
					//string InpImage(imageToSave);
					cout<<"---image read flag---:"<<check<<endl;

					string imageToSave_convert1 = "/home/rohit/Desktop/source_ocr/module8/"+ ss.str() +".jpg";
					check = extract->binarizeLP(imageToSave_convert1,binaryImage, grayImage , threholdImage, dataSetPath, imageToSave_convert);
					if(check == true){
					cout<<"---image read flag if---:"<<check<<endl;
					cout<<"----------------------findContours----------------------"<<endl;
					extract->findContours(binaryImage,contours);
					cout<<"----------------------recognizeTextInImg----------------------"<<endl;
					extract->recognizeTextInImg(api, binaryImage, grayImage, outText);
					cout<<"----------------------cropTextWithContourPoints----------------------"<<endl;
					extract->cropTextWithContourPoints(api, conf , conf_avg, threholdImage, imageToSave, const_y1, const_y2, letter_count);
					letter_count = 0;



					cout<<"----------------------drawRectOverSingleText----------------------"<<endl;
					extract->drawRectOverSingleText(binaryImage, contours, const_y1, const_y2, letter_count, count_crop, drawing,/* extract.contours_poly, extract.boundRect, extract.boundRectCrop, extract.center, extract.radius,*/threholdImage, count_temp, imageToSave_crop);


					cout<<"----------------------sort----------------------"<<endl;
					//extract.sort(extract.count_crop, extract.contours, extract.boundRectCrop);
					cout<<"----------------------cropRectOverSingleText----------------------"<<endl;
					//extract.cropRectOverSingleText(extract.count_crop, extract.threholdImage, extract.binaryImage, extract.count_temp, extract.drawing, extract.imageToSave_crop, extract.contours, extract.boundRectCrop);

					delete outText;
					delete api;

					cout<<"===================================================================================================="<<endl;
					cout<<"##########################################--RecognizeLP--###########################################"<<endl;
					cout<<"===================================================================================================="<<endl;
					cout<<endl<<endl;

					string lpPath;
					detect->scene_plate.release();
					detect->lpr = "";
					detect->count_letters = 0;
					VideoCapture cap;
					lpPath = "../crop/crop%d.jpg";
					cap.open(lpPath);


					detect->captrureLP(cap);
					detect->readNRecognize(cap,detect->scene_plate, detect->lpr,detect->count_letters, detect->lpFile);


			delete extract;
			delete detect;

					}
					else{

						cout<<"---image read flag else---:"<<check<<endl;
					}

}
#endif

}
		}
}


void DetectLP::showResultLPOnFrame(Mat& src_img){
#ifdef SHOW_STEPS
		if(!src_img.empty())
			imshow("Result", src_img);
		waitKey(1);
#endif

}

DetectLP::~DetectLP(){
	//destroy GUI windows
	destroyAllWindows();
}
