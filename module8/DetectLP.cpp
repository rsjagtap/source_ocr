/*
 * DetectLP.cpp
 *
 *  Created on: 21-Jun-2016
 *      Author: rohit
 */


#include "DetectLP.h"


DetectLP::DetectLP(){
//	namedWindow("Result");	//To show resulatnt image in this window.
//	namedWindow("Crop");	//To show cropped image in this window.



	//count
	CarCount = 0;

  	//folderName = "../Cars_Plates/";
//	check = true;
//	even = 1;
//	odd = 2;
//	even_fix = 20;
//	odd_fix = 20;
//	count_check = 0;
//
//	imageToSave[50] = {0};


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



void DetectLP::detectLPUseCascadeFile(VideoCapture& capture, CascadeClassifier& car_cascade, ExtractSingleText* extract, RecognizeLP* detect,int& CarCount){

		Mat src_img, gray_img;
		string folderName = "../Cars_Plates/";

		capture.read(src_img);
//cout<<"width "<< src_img.size().width << endl;
//cout<<"height "<< src_img.size().height << endl;

		vector<Rect> cars;
		cvtColor(src_img,gray_img,CV_BGR2GRAY);
		equalizeHist(gray_img,gray_img);
		car_cascade.detectMultiScale(gray_img, cars, 1.11, 2, 0 | CASCADE_SCALE_IMAGE, Size(0,0));


		saveCroppedLP(folderName, cars, src_img, extract, detect,CarCount);

		showResultLPOnFrame(src_img);

		destroyAllWindows();

		cars.clear();
		src_img.release();
		gray_img.release();

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

void DetectLP::saveCroppedLP(string& folderName, vector<Rect>& cars, Mat& src_img , ExtractSingleText* extract, RecognizeLP* detect,int& CarCount){
	bool check = true;
//	/int CarCount = 0;
	char imageToSave[50] = {0};
	int even = 1;
	int odd = 2;
	int even_fix = 20;
	int odd_fix = 20;
	int count_check = 0;

//	FILE *file = NULL;

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

#if 1
//if(CarCount > 79)
{
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
//string resizeImageCommand1 = "convert "+ inpImage1 +" -resize 4000 ../c2.jpg";
//string resizeImageCommand1 = "./Convert "+ ss.str();
const char *command = resizeImageCommand1.c_str();
//resizeImageCommand1 = "";
int status = 0;
bool cvt_st = true;
//do{

///string check_file = "../Cars_Plates/car_plate_" + ss.str() +".jpg";
const char *command_check = inpImage1.c_str();

//ifstream file1(command_check);
//if(!file1){            // If the file was not found, then file is 0, i.e. !file=1 or true.
//	cout<<"Image is --- False"<<endl;
//    //return false;    // The file was not found.
//}
//else{                 // If the file was found, then file is non-0.
//	cout<<"Image is --- True"<<endl;
//    //return true;
//}





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






extract = new ExtractSingleText();
detect = new RecognizeLP();

				cout<<endl<<endl;
			    check = true;

					//string inpImage = argv[1];

				//	string resizeImageCommand = "convert " + inpImage + " -resize 4500 ../../module1/dataset/c2.jpg";
				//	system(resizeImageCommand.c_str());
				//	cout<<resizeImageCommand<<endl;
				//
				//	string resizeImage = dataSetPath + "c2.jpg";


					std::vector<std::vector<cv::Point> > contours;

					int count_crop= 0;
					int count_temp = 0;
				    float conf = 0;
				    float conf_avg  = 0;
					char *outText = new char();
					char imageToSave[50];
					char imageToSave_crop[50];
				//	int count_convert;
					char imageToSave_convert[50];

					int letter_count  = 0;
					int const_y1 = 0;
					int const_y2  = 0;
					string dataSetPath = "/home/rohit/Desktop/source_ocr/module8";
					//string folderName;
					Mat binaryImage, grayImage, threholdImage, drawing;
					tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();


					cout<<"----------------------createFolder4CroppedText()----------------------"<<endl;
					extract->createFolder4CroppedText(dataSetPath);
					cout<<"----------------------initilizeTesseract(api)----------------------"<<endl;
					extract->initilizeTesseract(api);
					cout<<"----------------------binarizeLP----------------------"<<endl;
					//string InpImage(imageToSave);
					cout<<"---image read flag---:"<<check<<endl;
					//stringstream ss;
					//ss << CarCount;
					//string imageToSave11 = "/home/rohit/Desktop/source_ocr/module7/Cars_Plates/car_plate_" + ss.str() +".jpg";

					string imageToSave_convert1 = "/home/rohit/Desktop/source_ocr/module8/"+ ss.str() +".jpg";
					//string imageToSave_convert1 = "/home/rohit/Desktop/source_ocr/module8/c2.jpg";
					check = extract->binarizeLP(imageToSave_convert1,binaryImage, grayImage , threholdImage, dataSetPath, imageToSave_convert);
					if(check == true){
					cout<<"---image read flag if---:"<<check<<endl;
					//InpImage = "";
					cout<<"----------------------findContours----------------------"<<endl;
					extract->findContours(binaryImage,contours);
					cout<<"----------------------recognizeTextInImg----------------------"<<endl;
					extract->recognizeTextInImg(api, binaryImage, grayImage, outText);
					cout<<"----------------------cropTextWithContourPoints----------------------"<<endl;
					extract->cropTextWithContourPoints(api, conf , conf_avg, threholdImage, imageToSave, const_y1, const_y2, letter_count);
					letter_count = 0;



					cout<<"----------------------drawRectOverSingleText----------------------"<<endl;
//					vector<vector<Point> > contours_poly( contours.size());
//					vector<Rect> boundRect( contours.size());
//					vector<Point2f>center( contours.size());
//					vector<Rect> boundRectCrop(contours.size());
//					vector<float>radius( contours.size());

//					extract.contours_poly.resize(extract.contours.size());
//					extract.boundRect.resize(extract.contours.size());
//					extract.center.resize(extract.contours.size());
//					extract.boundRectCrop.resize(extract.contours.size());
//					extract.radius.resize(extract.contours.size());


					extract->drawRectOverSingleText(binaryImage, contours, const_y1, const_y2, letter_count, count_crop, drawing,/* extract.contours_poly, extract.boundRect, extract.boundRectCrop, extract.center, extract.radius,*/threholdImage, count_temp, imageToSave_crop);


					cout<<"----------------------sort----------------------"<<endl;
					//extract.sort(extract.count_crop, extract.contours, extract.boundRectCrop);
					cout<<"----------------------cropRectOverSingleText----------------------"<<endl;
					//extract.count_temp = 0;
					//extract.cropRectOverSingleText(extract.count_crop, extract.threholdImage, extract.binaryImage, extract.count_temp, extract.drawing, extract.imageToSave_crop, extract.contours, extract.boundRectCrop);

					delete outText;
					delete api;
//					delete command;
//					delete command_check;
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


//					delete command;
//					delete command_check;
			delete extract;
			delete detect;
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

//															vector<vector<Point> > contours_poly(0);
//															vector<Rect> boundRect(0);
//															vector<Point2f>center(0);
//															vector<Rect> boundRectCrop(0);
//															vector<float>radius(0);
//
//															extract.contours_poly.swap(contours_poly);
//															extract.boundRect.swap(boundRect);
//															extract.center.swap(center);
//															extract.boundRectCrop.swap(boundRectCrop);
//															extract.radius.swap(radius);


//										extract.const_y1 = 0;
//										extract.const_y2 = 0;
//										extract.count_crop = 0;
//										extract.count_temp = 0;
//										extract.letter_count = 0;
//										extract.binaryImage.release();
//										extract.grayImage.release();
//										extract.threholdImage.release();
//										extract.drawing.release();
//										extract.folderCreateCommand = "";
//										extract.folderRemoveCommand = "";
//										extract.removeImgCommand = "";
//										extract.resizeImageCommand = "";
//										extract.resizeImage = "";
					}
					else{

						cout<<"---image read flag else---:"<<check<<endl;
						//check =true;
						//continue;
						//break;
					}


//					boundRect.clear();
//					boundRectCrop.clear();
////outText
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
#endif
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
