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
//#include <baseapi.h>
//
//#include <tesseract/baseapi.h>
//#include <leptonica/allheaders.h>
//
//using namespace std;
//using namespace cv;
//
//RNG rng(12345);
////void sort(vector<Rect> &boundRectCrop);
//int count_crop = 0;
//int count_temp = 0;
////int main(int argc, char* argv[])
////{
#include "ExtractSingleText.h"


ExtractSingleText::ExtractSingleText(){

	count_crop = 0;
	count_temp = 0;
	conf = 0;
	conf_avg = 0;


	letter_count = 0;
	const_y1 = 0;
	const_y2 = 0;
	api = new tesseract::TessBaseAPI();
	dataSetPath = "/home/rohit/Desktop/source_ocr/module7/";
	folderName = "crop";
    resizeImageCommand = "";// = "convert " + inpImage + " -resize 4000 ../../module1/dataset/c2.jpg";
    folderRemoveCommand = "";
    folderCreateCommand ="";
    removeImgCommand ="";
    count_convert = 0;
    outText = new char();
    resizeImage = "";


    imageToSave[50] = {0};
	imageToSave_crop[50] = {0};
	imageToSave_convert[50] = {0};
}

void ExtractSingleText::createFolder4CroppedText(string& folderName,string& dataSetPath, string& folderRemoveCommand, string& folderCreateCommand,string& removeImgCommand){

	folderName = "crop";
	folderRemoveCommand = "rm -rf ../" + folderName;
	system(folderRemoveCommand.c_str());	//Remove the folder if already present
	folderCreateCommand = "mkdir ../" + folderName;
	system(folderCreateCommand.c_str());	//Create the folder if not present.

//	string folderRemoveCommand1 = "rm -rf ../converted";
//	system(folderRemoveCommand1.c_str());	//Remove the folder if already present
	string folderCreateCommand1 = "mkdir ../converted";
	system(folderCreateCommand1.c_str());	//Create the folder if not present.

//    removeImgCommand = "rm " + dataSetPath + "c2.jpg";
//    system(removeImgCommand.c_str());
//    cout<<removeImgCommand<<endl;

}





void ExtractSingleText::initilizeTesseract(tesseract::TessBaseAPI* api){
	api->SetVariable("tessedit_char_whitelist", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	api->SetVariable("classify_font_name", "Arial.ttf");

	/*

	   Font names

	   Andale_Mono.ttf
	   Arial_Black.ttf
	   Arial_Bold.ttf
	   Arial.ttf
	   buttf
	   Comic_Sans_MS_Bold.ttf
	   Comic_Sans_MS.ttf
	   Courier_New_Bold.ttf
	   Courier_New.ttf
	   Georgia_Bold.ttf
	   Georgia.ttf
	   Gottf
	   Impact.ttf
	   Times_New_Roman_Bold.ttf
	   Times_New_Roman.ttf
	   Trebuchet_MS_Bold.ttf
	   Trebuchet_MS.ttf
	   ttf
	   Verdana_Bold.ttf
	   Verdana.ttf
	 */












	api->SetVariable("segment_penalty_garbage", "0");
	api->SetVariable("segment_penalty_dict_nonword", "0");
	api->SetVariable("segment_penalty_dict_frequent_word", "0");
	api->SetVariable("segment_penalty_dict_case_ok", "0");
	api->SetVariable("segment_penalty_dict_case_bad", "0");


	api->Init("", "eng", tesseract::OEM_DEFAULT);


	if(!api->SetVariable("tessedit_enable_doc_dict", "0"))
	{
		cout << "Unable to enable dictionary" << endl;
	}

	//api->SetVariable("segment_penalty_garbage", "0");
	//api->SetVariable("segment_penalty_dict_nonword", "0");
	//api->SetVariable("segment_penalty_dict_ExtractSingleText::frequent_word", "0");
	//api->SetVariable("segment_penalty_dict_case_ok", "0");
	//api->SetVariable("segment_penalty_dict_case_bad", "0");
	// api->SetPageSegMode(static_cast<tesseract::PageSegMode>(7));
	// api->SetOutputName("out");

	// Initialize tesseract-ocr with English, without specifying tessdata path
	//    if (api->Init(NULL, "eng")) {
	//        fprintf(stderr, "Could not initialize tesseract.\n");
	//        exit(1);
	//    }



	// Open input image with leptonica library
	//    Pix *image = pixRead("../../helloworld.jpg");
	//
	// api->SetPageSegMode(static_cast<tesseract::PageSegMode>(7));
	// api->SetOutputName("out");
}


bool ExtractSingleText::binarizeLP(string& imageToSave, Mat& binaryImage, Mat& grayImage , Mat& threholdImage, string& dataSetPath, string& resizeImageCommand,string& resizeImage, int& count_convert, char* imageToSave_convert){
	//Mat gray, imgThresh;

	//string removeImg = "../Cars_Plates";
//    string removeImgCommand = "rm " + dataSetPath + "c2.jpg";
//    system(removeImgCommand.c_str());
//    cout<<removeImgCommand<<endl;
	//Mat src_img = imread(imageToSave, 1);
    //if(src_img.data)

        //printf( " No image data \n " );
        //return -1;
    //}

	//if(!src_img.empty())

//	char imageToSave_convert1[100];
	count_convert +=1;
//	sprintf(imageToSave_convert1,"../%d.jpg",count_convert);
//	imwrite(imageToSave_convert, src_img(cars[i]));

//	resizeImageCommand = "";
	//string inpImage(imageToSave);

	int count_loop = 0;
//do{

//count_loop +=1;
//
//	sleep(2);
//	string resizeImageCommand1 = "convert " + imageToSave + " -resize 4000 "+ imageToSave_convert1;
//	system(resizeImageCommand1.c_str());
//	cout<<resizeImageCommand1<<endl;



	//resizeImage = "";
	string resizeImage1 = imageToSave;


	//usleep(30000);
	//Mat image(Size(4500, 2000), CV_8UC1);
	//grayImage = image.clone();

	grayImage = imread(resizeImage1,0);
	//resizeImageCommand = " ";
//	if(count_loop == 20)
//		return false;
//}while(grayImage.empty());
//imageToSave_convert1 = "";

	//imshow("Test",grayImage);
	//waitKey(30);
if(!grayImage.empty())
{
/*	cout << "!!! Failed imread(): image not found" << endl;
	return false;
}
else{*/
	Mat gray_img;
//	cout<<"###"<<resizeImage<<endl;
//	cout<<"###"<<imageToSave_convert1<<endl;



        //resize(img_src, img_src,Size(img_src.size().width*35, img_src.size().height*35));
	//resize(img_src, img_src,Size(4500, 1777),0,0,CV_INTER_LINEAR);
	float conf = 0;
	float conf_avg = 0;
	//do{
/*	gray_img = grayImage.clone();

		cvtColor(grayImage,gray_img,CV_BGR2GRAY);
		//gray_img.convertTo(gray_img, CV_8U);
	//else grayImage = src_img.clone();


		grayImage = gray_img.clone();*/
#ifdef SHOW_STEPS
	imshow("gray",grayImage);
#endif
	cv::GaussianBlur(grayImage, grayImage, cv::Size(3, 3), 0);
#ifdef SHOW_STEPS
	imshow("blur",grayImage);
#endif
	cv::threshold(grayImage, threholdImage, 70, 255,CV_THRESH_BINARY);

	//cv::Mat imgThreshCopy = imgThresh.clone();
	binaryImage = threholdImage.clone();;
	//adaptiveThreshold(gray,imgThreshCopy,255,CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,75,10);

	cv::bitwise_not(binaryImage,binaryImage);
#ifdef SHOW_STEPS
	imshow("thrash",binaryImage);
#endif




	Mat imgThresh_output;
	//Canny( gray, imgThresh, 60, 60*3, 3 );
	//imshow("canny",imgThresh);
	////imgThresh = gray.clone();
	cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));


	for (unsigned int i = 0; i < 13; i++) {
		cv::dilate(binaryImage, binaryImage, structuringElement5x5);
		cv::dilate(binaryImage, binaryImage, structuringElement5x5);
		cv::erode(binaryImage, binaryImage, structuringElement5x5);
	}

	//binaryImage = imgThreshCopy.clone();
	//grayImage = gray.clone();
	//threholdImage = imgThresh.clone();
	return true;
}
else{

  //  return false;
    return false;
}
}
















void ExtractSingleText::findContours(Mat& binaryImage, std::vector<std::vector<cv::Point> > &contours){
	//            cv::Mat imgThreshCopy = imgThresh.clone();

//	Mat imgThreshCopy = binaryImage.clone();
	//std::vector<std::vector<cv::Point> > contours;

	//cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL,CV_CHAIN_APPROX_TC89_KCOS, Point(0, 0));
	cv::findContours(binaryImage, contours, /*cv::RETR_CCOMP CV_RETR_TREE*/ CV_RETR_LIST , cv::CHAIN_APPROX_SIMPLE);

	//                                cv::drawContours(imgThreshCopy, contours, -1,cv::Scalar(255.0, 255.0, 255.0), 4);
	//                                cv::imshow("contours", imgThreshCopy);
//	vector<vector<Point> > contours_poly( contours.size() );
//	vector<Rect> boundRect( contours.size() );
//	vector<Rect> boundRectCrop(contours.size());
//	vector<Point2f>center( contours.size() );
//	vector<float>radius( contours.size() );
//
//	for( int i = 0; i < contours.size(); i++ )
//	{ approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
//		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
//		boundRectCrop[i] = boundingRect( Mat(contours_poly[i]) );
//		minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
//	}

	//binaryImage = imgThreshCopy.clone();

}
	//  /// Draw polygonal contour + bonding rects + circles
	//  Mat drawing = Mat::zeros(imgThreshCopy.size(), CV_8UC3 );
	//  for( int i = 0; i< contours.size(); i++ )
	//     {
	//       Scalar color = Scalar(255,123,0);
	//       drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
	//       rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
	//	cout<<"p1: "<<boundRect[i].tl() << " p2: "<<boundRect[i].br()<<endl;
	////       circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
	//     }
	//cout<<endl<<endl;
	//
	//cv::imshow("drawings", drawing);










	//
	//
	//
	//
	////    Pix *image = pixRead("../../helloworld.jpg");
	//imgThresh = imgThreshCopy.clone();

void ExtractSingleText::recognizeTextInImg(tesseract::TessBaseAPI* api, Mat& binaryImage, Mat& grayImage, char *outText){

	//Mat imgThreshCopy = binaryImage.clone();
	//Mat gray = grayImage.clone();
	api->TesseractRect(binaryImage.data, 1, binaryImage.step1(), 0, 0, binaryImage.cols, binaryImage.rows);


	Pix *image = pixCreate(binaryImage.size().width, binaryImage.size().height, 8);

	for(int i=0; i<binaryImage.rows; i++)
		for(int j=0; j<binaryImage.cols; j++)
			pixSetPixel(image, j,i, (l_uint32) grayImage.at<uchar>(i,j));

	api->SetPageSegMode(static_cast<tesseract::PageSegMode>(6));
	api->SetOutputName("out");



	//api->TesseractRect(image->data, 1, image->step1(), 0, 0, image->cols, image->rows); 

	api->SetImage(image);
	api->Recognize(0);
	//tesseract::PageIteratorLevel level1 = tesseract:: RIL_SYMBOL;
	// Get OCR result
	outText = api->GetUTF8Text();
	printf("OCR output:\n%s", outText);
}


void ExtractSingleText::cropTextWithContourPoints(tesseract::TessBaseAPI* api, float& conf , float& conf_avg, Mat& threholdImage, char imageToSave[], int& const_y1, int& const_y2, int& letter_count){
	//float conf = 0;
	//float conf_avg = 0;
//	letter_count = 0;
	//const_y1 = 0;
	//const_y2 = 0;
	//Mat imgThresh =  threholdImage.clone();
	// To crop text with counter points

	tesseract::ResultIterator* ri = api->GetIterator();
	tesseract::PageIteratorLevel level = tesseract:: RIL_SYMBOL;//RIL_WORD;
	if (ri != 0) {
		do {
			const char* word = ri->GetUTF8Text(level);
			conf = ri->Confidence(level);
			conf_avg += conf;
			letter_count += 1;
			int x1, y1, x2, y2;
			ri->BoundingBox(level, &x1, &y1, &x2, &y2);
			if(letter_count == 1){
				const_y1 = y1;
				const_y2 = y2;
			}

			if(const_y2 < y2)
				const_y2 = y2;

			std::cout<<"const_y1: "<<const_y1<<" | const_y2: "<<const_y2<<std::endl;
cout<<"woking 1"<<endl;
			//rectangle(imgThresh,Point(x1-20, const_y1-20),Point(x2+20, const_y2+20), Scalar(0,0,0), 2, 8, 0 );
			//if((x1-20) >= 0 && (const_y1-20) >=0  && ((x2+20)-(x1-20)) <= imgThresh.width && ((const_y2+20)-(const_y1-20)) << imgThresh.height){
			Rect roi(x1-5, const_y1-5,(x2+5)-(x1-5),(const_y2+5)-(const_y1-5));
cout<<"woking 2"<<endl;
//			Mat imgThreshClone = imgThresh.clone();
cout<<"roi.height: "<< roi.height <<" | "<< threholdImage.rows<<endl;
cout<<"roi.width: "<< roi.width <<" | "<< threholdImage.cols<<endl;
//			if((roi.height <= imgThresh.rows) && (roi.width <= imgThresh.cols) ){
if(roi.x >= 0 && roi.y >= 0 && roi.width + roi.x < threholdImage.cols && roi.height + roi.y < threholdImage.rows){
			Mat crop_img = threholdImage(roi);
cout<<"woking 3"<<endl;
			sprintf(imageToSave,"%s//face%d.jpg","..",letter_count);
cout<<"woking 4"<<endl;
			imwrite(imageToSave, crop_img);
cout<<"woking 5"<<endl;
#ifdef SHOW_STEPS
			cv::imshow("crop", crop_img);
#endif
cout<<"woking 6"<<endl;

			printf("word: '%s';  \tconf: %.2f; BoundingBox: %d,%d,%d,%d;\n",
					word, conf, x1, y1, x2, y2);
			}
			delete[] word;
		} while (ri->Next(level));
		conf_avg = conf_avg/letter_count;
		std::cout<<"avg conf is: "<<conf_avg<<std::endl;
	}
}

void ExtractSingleText::drawRectOverSingleText(Mat& binaryImage, std::vector<std::vector<cv::Point> > &contours,int& const_y1,int& const_y2,int& letter_count, int& count_crop, Mat& drawing, vector<vector<Point> > &contours_poly, vector<Rect> &boundRect, vector<Rect> &boundRectCrop, vector<Point2f> &center, vector<float> &radius){


	//Mat imgThreshCopy = binaryImage.clone();
	/// Draw polygonal contour + bonding rects + circles
	drawing = Mat::zeros(binaryImage.size(), CV_8UC3 );


//for( int i = 0; i < contours.size(); i++ )
//{
//cout<<" boundRect[i]"<< boundRect[i];
//}



//	vector<vector<Point> > contours_poly( contours.size() );
//	vector<Rect> boundRect( contours.size() );
//	vector<Rect> boundRectCrop(contours.size());
//	vector<Point2f>center( contours.size() );
//	vector<float>radius( contours.size() );
	

	for( int i = 0; i < contours.size(); i++ )
	{ approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );
		boundRectCrop[i] = boundingRect( Mat(contours_poly[i]) );
		minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
	}






	for( int i = 0; i< contours.size(); i++ )
	{
		Scalar color = Scalar(255,123,0);
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );

		cout<<" width is: "<<boundRect[i].width <<" |  height is : "<<(boundRect[i].height + boundRect[i].height/2)<<endl;
                if(boundRect[i].width < (boundRect[i].height + boundRect[i].height/3)){

		if(/*(const_y1-20) <= boundRect[i].y && (const_y2+20) >= (boundRect[i].y + boundRect[i].height) &&*/ (boundRect[i].height >= (((const_y2)- (const_y1))/5 + ((const_y2)- (const_y1))/6))) {

			cout<<"bheight: "<<boundRect[i].height << " y2-y1: "<<(const_y2)- (const_y1)<<endl;
			rectangle(binaryImage, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
			cout<<"p1: "<<boundRect[i].tl() << " p2: "<<boundRect[i].br()<<endl;
			boundRectCrop[count_crop].x = boundRect[i].x;
			boundRectCrop[count_crop].y = boundRect[i].y;
			boundRectCrop[count_crop].width = boundRect[i].width;
			boundRectCrop[count_crop].height = boundRect[i].height;
			cout<<"p1: "<<boundRectCrop[count_crop].tl() << " p2: "<<boundRectCrop[count_crop].br()<<endl;
			count_crop += 1;

			//Rect roi_crop(boundRect[i].x, boundRect[i].y,boundRect[i].width,boundRect[i].height);
			//
			//Mat crop_img_text = imgThresh(roi_crop);
			//                sprintf(imageToSave_crop,"%s//crop%d.jpg","..",i);
			//                imwrite(imageToSave_crop, crop_img_text);
			//cv::imshow("crop_text", crop_img_text);

		}
	}

		//       circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
	}
}

// sort
//sort(boundRectCrop);

void ExtractSingleText::cropRectOverSingleText(int& count_crop, Mat& threholdImage, Mat& binaryImage, int& count_temp, Mat& drawing, char imageToSave_crop[], std::vector<std::vector<cv::Point> > &contours, vector<Rect> &boundRectCrop){

	//Mat imgThresh = threholdImage.clone();
	//Mat imgThreshCopy = binaryImage.clone();

//	vector<vector<Point> > contours_poly( contours.size() );
//	vector<Rect> boundRectCrop(contours.size());
//
//	for( int i = 0; i < contours.size(); i++ )
//	{
//		boundRectCrop[i] = boundingRect( Mat(contours_poly[i]) );
//	}



        int minboundRectCropHeight = 0;
        for( int i = 0; i< count_crop; i++ ){
        if(minboundRectCropHeight < boundRectCrop[i].height)
                minboundRectCropHeight = boundRectCrop[i].height;
        }

        cout<<"maximum height is: "<< minboundRectCropHeight<<endl;




	cout<<endl<<endl;

	for( int i = 0; i< count_crop; i++ )
	{
		cout<<"p1: "<<boundRectCrop[i].tl() << " p2: "<<boundRectCrop[i].br()<<endl;
		Rect roi_crop(boundRectCrop[i].x, boundRectCrop[i].y,boundRectCrop[i].width,boundRectCrop[i].height);

		Mat crop_img_text = threholdImage(roi_crop);
double nonZero = countNonZero(crop_img_text);
cout<<"NonZero: "<<nonZero<<endl;
double nPixels = (crop_img_text.cols*crop_img_text.channels())*crop_img_text.rows;
cout<<"Total: "<<nPixels<<endl;
cout<<"White Pixels: "<<(nonZero/nPixels)<<endl;

		if((nonZero/nPixels)*100 < 90 && (minboundRectCropHeight-100) < boundRectCrop[i].height){
		sprintf(imageToSave_crop,"%s//crop%d.jpg","../crop/",count_temp);
		imwrite(imageToSave_crop, crop_img_text);
#ifdef SHOW_STEPS
		cv::imshow("crop_text", crop_img_text);
#endif
		count_temp +=1; 
		}

	}

	cout<<endl<<endl;
#ifdef SHOW_STEPS
	cv::imshow("contours_rect", binaryImage);
	cv::imshow("drawings", drawing);
#endif










	//}while(conf_avg < 90);
#ifdef SHOW_STEPS
//	cv::imshow("rect", imgThresh);
#endif
	//waitKey(0);

	// Destroy used object and release memory
	//    api->End();
	//    delete [] outText;
	//    pixDestroy(&image);

	//    return 0;
}



void ExtractSingleText::sort(int& count_crop, std::vector<std::vector<cv::Point> > &contours, vector<Rect> &boundRectCrop){

//	vector<vector<Point> > contours_poly( contours.size() );
//	vector<Rect> boundRectCrop(contours.size());
//
//	for( int i = 0; i < contours.size(); i++ )
//	{
//		boundRectCrop[i] = boundingRect( Mat(contours_poly[i]) );
//	}



	for(int i = 0; i< count_crop; i++){
		for(int j = i; j< count_crop; j++){
			if(boundRectCrop[i].x > boundRectCrop[j].x){

				int tempX = boundRectCrop[i].x;
				int tempY = boundRectCrop[i].y;
				int tempWidth = boundRectCrop[i].width;
				int tempHeight = boundRectCrop[i].height;

				boundRectCrop[i].x = boundRectCrop[j].x;
				boundRectCrop[i].y = boundRectCrop[j].y;
				boundRectCrop[i].width = boundRectCrop[j].width;
				boundRectCrop[i].height = boundRectCrop[j].height;

				boundRectCrop[j].x = tempX;
				boundRectCrop[j].y = tempY;
				boundRectCrop[j].width = tempWidth;
				boundRectCrop[j].height = tempHeight;

			}

		}
		cout<<"p1: "<<boundRectCrop[i].tl() << " p2: "<<boundRectCrop[i].br()<<endl;
	}

}
