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
	dataSetPath = "/home/rohit/Desktop/source_ocr/module4/";


}

ExtractSingleText::~ExtractSingleText(){
	delete this;
}



void ExtractSingleText::createFolder4CroppedText(){

	string folderName = "crop";
	string folderRemoveCommand = "rm -rf ../" + folderName;
	system(folderRemoveCommand.c_str());	//Remove the folder if already present
	string folderCreateCommand = "mkdir ../" + folderName;
	system(folderCreateCommand.c_str());	//Create the folder if not present.
}





void ExtractSingleText::initilizeTesseract(){
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


void ExtractSingleText::binarizeLP(string inpImage){
	Mat gray, imgThresh;

	string removeImg = "../Cars_Plates";
    string removeImgCommand = "rm " + dataSetPath + "c2.jpg";
	string resizeImageCommand = "convert " + inpImage + " -resize 4000 ../c2.jpg";
	system(resizeImageCommand.c_str());
	cout<<resizeImageCommand<<endl;

	string resizeImage = dataSetPath + "c2.jpg";

	Mat img_src = imread(resizeImage);

	//resize(img_src, img_src,Size(img_src.size().width*35, img_src.size().height*35));
	//resize(img_src, img_src,Size(4500, 1777),0,0,CV_INTER_LINEAR);
	float conf = 0;
	float conf_avg = 0;
	//do{
	cvtColor(img_src,gray,CV_BGR2GRAY);
	imshow("gray",gray);
	cv::GaussianBlur(gray, gray, cv::Size(3, 3), 0);
	imshow("blur",gray);
	cv::threshold(gray, imgThresh, 70, 255,CV_THRESH_BINARY);

	cv::Mat imgThreshCopy = imgThresh.clone();
	//adaptiveThreshold(gray,imgThreshCopy,255,CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,75,10);

	cv::bitwise_not(imgThreshCopy,imgThreshCopy);
	imshow("thrash",imgThreshCopy);




	Mat imgThresh_output;
	//Canny( gray, imgThresh, 60, 60*3, 3 );
	//imshow("canny",imgThresh);
	////imgThresh = gray.clone();
	cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));


	for (unsigned int i = 0; i < 13; i++) {
		cv::dilate(imgThreshCopy, imgThreshCopy, structuringElement5x5);
		cv::dilate(imgThreshCopy, imgThreshCopy, structuringElement5x5);
		cv::erode(imgThreshCopy, imgThreshCopy, structuringElement5x5);
	}

	binaryImage = imgThreshCopy.clone();
	grayImage = gray.clone();
	threholdImage = imgThresh.clone();

}















void ExtractSingleText::findContours(std::vector<std::vector<cv::Point> > &contours){
	//            cv::Mat imgThreshCopy = imgThresh.clone();

	Mat imgThreshCopy = binaryImage.clone();
	//std::vector<std::vector<cv::Point> > contours;

	//cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL,CV_CHAIN_APPROX_TC89_KCOS, Point(0, 0));
	cv::findContours(imgThreshCopy, contours, /*cv::RETR_CCOMP CV_RETR_TREE*/ CV_RETR_LIST , cv::CHAIN_APPROX_SIMPLE);

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

	binaryImage = imgThreshCopy.clone();

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

void ExtractSingleText::recognizeTextInImg(){

	Mat imgThreshCopy = binaryImage.clone();
	Mat gray = grayImage.clone();
	api->TesseractRect(imgThreshCopy.data, 1, imgThreshCopy.step1(), 0, 0, imgThreshCopy.cols, imgThreshCopy.rows);


	Pix *image = pixCreate(imgThreshCopy.size().width, imgThreshCopy.size().height, 8);

	for(int i=0; i<imgThreshCopy.rows; i++) 
		for(int j=0; j<imgThreshCopy.cols; j++) 
			pixSetPixel(image, j,i, (l_uint32) gray.at<uchar>(i,j));

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


void ExtractSingleText::cropTextWithContourPoints(){
	//float conf = 0;
	//float conf_avg = 0;
	//int letter_count = 0;
	//int const_y1 = 0;
	//int const_y2 = 0;
	Mat imgThresh =  threholdImage.clone();
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
			//if((x1-5) >= 0 && (const_y1-5) >=0  && ((x2+5)-(x1-5)) <= imgThresh.size().width && ((const_y2+5)-(const_y1-5)) << imgThresh.size().height){
			Rect roi(x1-5, const_y1-5,(x2+5)-(x1-5),(const_y2+5)-(const_y1-5));
			cout<<"woking 2"<<endl;
			//			Mat imgThreshClone = imgThresh.clone();
			cout<<"roi.height: "<< roi.height <<" | "<< imgThresh.rows<<endl;
			cout<<"roi.width: "<< roi.width <<" | "<< imgThresh.cols<<endl;
			//			if((roi.height <= imgThresh.rows) && (roi.width <= imgThresh.cols) ){
			if(roi.x >= 0 && roi.y >= 0 && roi.width + roi.x < imgThresh.cols && roi.height + roi.y < imgThresh.rows){
				Mat crop_img = imgThresh(roi);
				cout<<"woking 3"<<endl;
				sprintf(imageToSave,"%s//face%d.jpg","..",letter_count);
				cout<<"woking 4"<<endl;
				imwrite(imageToSave, crop_img);
				cout<<"woking 5"<<endl;
				cv::imshow("crop", crop_img);
				cout<<"woking 6"<<endl;

				printf("word: '%s';  \tconf: %.2f; BoundingBox: %d,%d,%d,%d;\n",
						word, conf, x1, y1, x2, y2);
			}
			delete[] word;
			//}
		} while (ri->Next(level));
			conf_avg = conf_avg/letter_count;
			std::cout<<"avg conf is: "<<conf_avg<<std::endl;
		}
		}

		void ExtractSingleText::drawRectOverSingleText(std::vector<std::vector<cv::Point> > &contours, vector<vector<Point> > &contours_poly, vector<Rect> &boundRect, vector<Rect> &boundRectCrop, vector<Point2f> &center, vector<float> &radius){


			Mat imgThreshCopy = binaryImage.clone();
			/// Draw polygonal contour + bonding rects + circles
			drawing = Mat::zeros(imgThreshCopy.size(), CV_8UC3 );


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
				if(boundRect[i].width < (boundRect[i].height + boundRect[i].height/2)){

					if(/*(const_y1-20) <= boundRect[i].y && (const_y2+20) >= (boundRect[i].y + boundRect[i].height) &&*/ (boundRect[i].height >= (((const_y2)- (const_y1))/5 + ((const_y2)- (const_y1))/6))) {

						cout<<"bheight: "<<boundRect[i].height << " y2-y1: "<<(const_y2)- (const_y1)<<endl;
						rectangle(imgThreshCopy, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
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

		void ExtractSingleText::cropRectOverSingleText(std::vector<std::vector<cv::Point> > &contours, vector<Rect> &boundRectCrop){

			Mat imgThresh = threholdImage.clone();
			Mat imgThreshCopy = binaryImage.clone();

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

			//count_temp = 0;
			for( int i = 0; i< count_crop; i++ )
			{
				cout<<"p1: "<<boundRectCrop[i].tl() << " p2: "<<boundRectCrop[i].br()<<endl;
				Rect roi_crop(boundRectCrop[i].x, boundRectCrop[i].y,boundRectCrop[i].width,boundRectCrop[i].height);

				Mat crop_img_text = imgThresh(roi_crop);
				double nonZero = countNonZero(crop_img_text);
				cout<<"NonZero: "<<nonZero<<endl;
				double nPixels = (crop_img_text.cols*crop_img_text.channels())*crop_img_text.rows;
				cout<<"Total: "<<nPixels<<endl;
				cout<<"White Pixels: "<<(nonZero/nPixels)<<endl;

				if((nonZero/nPixels)*100 < 90 && (minboundRectCropHeight-100) < boundRectCrop[i].height){
					sprintf(imageToSave_crop,"%s//crop%d.jpg","../crop/",count_temp);
					imwrite(imageToSave_crop, crop_img_text);
					cv::imshow("crop_text", crop_img_text);
					count_temp +=1;
				}

			}

			cout<<endl<<endl;
			cv::imshow("contours_rect", imgThreshCopy);
			cv::imshow("drawings", drawing);










			//}while(conf_avg < 90);

			cv::imshow("rect", imgThresh);
			//waitKey(0);

			// Destroy used object and release memory
			//    api->End();
			//    delete [] outText;
			//    pixDestroy(&image);

			//    return 0;
	}



	void ExtractSingleText::sort(std::vector<std::vector<cv::Point> > &contours, vector<Rect> &boundRectCrop){

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
