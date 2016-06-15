#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/nonfree/features2d.hpp"
using namespace std;
using namespace cv;


void read_image(int width, int height, char *image);
Mat scene_plate;
string lpr = "";
int count_letters = 0;
int count_non_letters = 0;

int main( int argc, char** argv )
{
	VideoCapture cap("/home/rohit/Desktop/source_ocr/module1/crop/crop%d.jpg"); // would work with: "/my/folder/p00013.jpg", etc
	cout << "OCR: starts" << endl;
	while(cap.read(scene_plate)){

		//cap.read(scene_plate);
		//  cout << "OCR: starts" << endl;
		//scene_plate = imread(argv[1], CV_LOAD_IMAGE_COLOR );
		read_image(scene_plate.cols, scene_plate.rows, (char*)scene_plate.ptr());
	}
	lpr.erase(std::remove(lpr.begin(), lpr.end(), '\n'), lpr.end());
	lpr.erase(std::remove(lpr.begin(), lpr.end(), ' '), lpr.end());
	cout<<lpr<<endl;
}


void read_image(int width, int height, char *image)

{
	cv::Mat Image(height, width, CV_8UC3, image);
	// you may need to define the area of interest, where the test is found

	// initializing Tesseract API
	char *outText;
	double confidence = 0;
	//do{
	tesseract::TessBaseAPI *tess_api = new tesseract::TessBaseAPI();
	if (tess_api->Init(NULL, "eng"))  // eng is a flag of which trained language you use, if you just train your own language, you gave "XYZ" as a falge, you have to use it here
	{
		cout<<"Could not initialize tesseract.\n";
		exit(1);
	}
	//tess_api->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345789");
	//tess_api->SetVariable("tessedit_char_whitelist", "0123456789");
//	if(count_letters <= 4)
//	tess_api->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"/*0123456789X"*/);
//	if(count_letters >=4 && count_letters <=12)
//	tess_api->SetVariable("tessedit_char_whitelist", /*"ABCDEFGHIJKLMNOPQRSTUVWXYZ"*/"0123456789");
//	if(count_letters>=12  && count_letters < 18)
//	tess_api->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"/*0123456789X"*/);
//	if(count_letters>=18)
        tess_api->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
//	else
//	tess_api->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789X");

	tess_api->SetVariable("classify_font_name", "Arial.ttf");
	tess_api->SetVariable("segment_penalty_garbage", "0");
	tess_api->SetVariable("segment_penalty_dict_nonword", "0");
	tess_api->SetVariable("segment_penalty_dict_frequent_word", "0");
	tess_api->SetVariable("segment_penalty_dict_case_ok", "0");
	tess_api->SetVariable("segment_penalty_dict_case_bad", "0");


	if(!tess_api->SetVariable("tessedit_enable_doc_dict", "0"))
	{
		cout << "Unable to enable dictionary" << endl;
	}
	tess_api->SetPageSegMode(tesseract::PSM_SINGLE_WORD);
	tess_api->SetImage((uchar*)scene_plate.data, scene_plate.size().width,scene_plate.size().height,scene_plate.channels(),scene_plate.step1());
	tess_api->Recognize(0);
	//char* out =tess_api->GetUTF8Text();
	string temp = tess_api->GetUTF8Text();
	confidence = tess_api->MeanTextConf();
	//cout<<"OCR output:"<< out<< "  with confidence "<<confidence<<endl;
	//lpr << out; 
	//cout<<temp.length()<<endl;

	if(temp.length() <= 5){
		lpr +=temp;
		count_letters +=temp.length();
		cout<<count_letters<<" | "<<lpr<<endl;
	}
	else{
		count_non_letters +=temp.length();
	}
	//lpr.append(out);
	//cout<<lpr;

	//}while(confidence < 90);
}
