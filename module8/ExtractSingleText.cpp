
#include "ExtractSingleText.h"


ExtractSingleText::ExtractSingleText(){

	api = new tesseract::TessBaseAPI();
}

ExtractSingleText::~ExtractSingleText(){

	delete api;
}


void ExtractSingleText::createFolder4CroppedText(string& dataSetPath){

	string folderName = "crop";
	string folderRemoveCommand = "rm -rf ../" + folderName;
	system(folderRemoveCommand.c_str());	//Remove the folder if already present
	string folderCreateCommand = "mkdir ../" + folderName;
	system(folderCreateCommand.c_str());	//Create the folder if not present.


	string folderCreateCommand1 = "mkdir ../converted";
	system(folderCreateCommand1.c_str());	//Create the folder if not present.

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

}


bool ExtractSingleText::binarizeLP(string& imageToSave, Mat& binaryImage, Mat& grayImage , Mat& threholdImage, string& dataSetPath, char* imageToSave_convert){
	int count_loop = 0;
	string resizeImage1 = imageToSave;

	grayImage = imread(resizeImage1,0);


	if(!grayImage.empty())
	{

#ifdef SHOW_STEPS
		imshow("gray",grayImage);
#endif
		cv::GaussianBlur(grayImage, grayImage, cv::Size(3, 3), 0);
#ifdef SHOW_STEPS
		imshow("blur",grayImage);
#endif
		cv::threshold(grayImage, threholdImage, 70, 255,CV_THRESH_BINARY);

		binaryImage = threholdImage.clone();;

		cv::bitwise_not(binaryImage,binaryImage);
#ifdef SHOW_STEPS
		imshow("thrash",binaryImage);
#endif

		cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));


		for (unsigned int i = 0; i < 13; i++) {
			cv::dilate(binaryImage, binaryImage, structuringElement5x5);
			cv::dilate(binaryImage, binaryImage, structuringElement5x5);
			cv::erode(binaryImage, binaryImage, structuringElement5x5);
		}

		return true;
	}
	else{
		return false;
	}
}


void ExtractSingleText::findContours(Mat& binaryImage, std::vector<std::vector<cv::Point> > &contours){

	cv::findContours(binaryImage, contours, /*cv::RETR_CCOMP CV_RETR_TREE*/ CV_RETR_LIST , cv::CHAIN_APPROX_SIMPLE);

}


void ExtractSingleText::recognizeTextInImg(tesseract::TessBaseAPI* api, Mat& binaryImage, Mat& grayImage, char *outText){


//	api->TesseractRect(binaryImage.data, 1, binaryImage.step1(), 0, 0, binaryImage.cols, binaryImage.rows);

//	Pix *image = pixCreate(binaryImage.size().width, binaryImage.size().height, 8);
//
//	for(int i=0; i<binaryImage.rows; i++)
//		for(int j=0; j<binaryImage.cols; j++)
//			pixSetPixel(image, j,i, (l_uint32) grayImage.at<uchar>(i,j));

	api->SetPageSegMode(static_cast<tesseract::PageSegMode>(6));
	api->SetOutputName("out");


	//api->SetImage(image);
	api->SetImage((uchar*)binaryImage.data, binaryImage.size().width,binaryImage.size().height,binaryImage.channels(),binaryImage.step1());
	api->Recognize(0);

	//outText = api->GetUTF8Text();
	string outText_Test = api->GetUTF8Text();
//	/printf("OCR output:\n%s", outText_Test);

	cout<<"OCR output:\n"<<outText_Test<<endl;

	//free((Pix *)image);

}


void ExtractSingleText::cropTextWithContourPoints(tesseract::TessBaseAPI* api, float& conf , float& conf_avg, Mat& threholdImage, char imageToSave[], int& const_y1, int& const_y2, int& letter_count){


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
	delete ri;
}

void ExtractSingleText::drawRectOverSingleText(Mat& binaryImage, std::vector<std::vector<cv::Point> > &contours,int& const_y1,int& const_y2,int& letter_count, int& count_crop, Mat& drawing,/* vector<vector<Point> > &contours_poly, vector<Rect> &boundRect, vector<Rect> &boundRectCrop, vector<Point2f> &center, vector<float> &radius,*/ Mat& threholdImage, int& count_temp, char imageToSave_crop[]){



	vector<vector<Point> > contours_poly( contours.size());
	vector<Rect> boundRect( contours.size());
	vector<Point2f>center( contours.size());
	vector<Rect> boundRectCrop(contours.size());
	vector<float> radius( contours.size());


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
				rectangle(binaryImage, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
				cout<<"p1: "<<boundRect[i].tl() << " p2: "<<boundRect[i].br()<<endl;
				boundRectCrop[count_crop].x = boundRect[i].x;
				boundRectCrop[count_crop].y = boundRect[i].y;
				boundRectCrop[count_crop].width = boundRect[i].width;
				boundRectCrop[count_crop].height = boundRect[i].height;
				cout<<"p1: "<<boundRectCrop[count_crop].tl() << " p2: "<<boundRectCrop[count_crop].br()<<endl;
				count_crop += 1;


			}
		}


	}




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



}
