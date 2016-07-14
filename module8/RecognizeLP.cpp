
#include "RecognizeLP.h"


RecognizeLP::RecognizeLP(){

	count_non_letters = 0;

	lpr = "";
	count_letters = 0;



}

void RecognizeLP::captrureLP(VideoCapture& cap){

	if (!cap.isOpened()) {
		cout<<"Error while opening camera"<<endl;

	}
}

void RecognizeLP::read_image(int width, int height, char *image, Mat& scene_plate, string& lpr,int& count_letters)
{
	cv::Mat Image(height, width, CV_8UC3, image);
	// you may need to define the area of interest, where the test is found
	cout<<"count_letters: "<<count_letters<<endl;
	// initializing Tesseract API
	//char *outText;
	double confidence = 0;
	//do{
	tesseract::TessBaseAPI *tess_api = new tesseract::TessBaseAPI();
	if (tess_api->Init(NULL, "eng"))  // eng is a flag of which trained language you use, if you just train your own language, you gave "XYZ" as a falge, you have to use it here
	{
		cout<<"Could not initialize tesseract.\n";
		exit(1);
	}

	if(count_letters < 2)
		tess_api->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	if(count_letters >=2 && count_letters < 4)
		tess_api->SetVariable("tessedit_char_whitelist", /*"ABCDEFGHIJKLMNOPQRSTUVWXYZ"*/"0123456789");
	if(count_letters>=4  && count_letters < 6)
		tess_api->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	if(count_letters>=6 && count_letters < 10)
		tess_api->SetVariable("tessedit_char_whitelist", /*"ABCDEFGHIJKLMNOPQRSTUVWXYZ"*/"0123456789");


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

	string temp = tess_api->GetUTF8Text();

	temp.erase(std::remove(temp.begin(), temp.end(), '\n'), temp.end());
	temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
	confidence = tess_api->MeanTextConf();

	lpr.append(temp);
	count_letters +=temp.length();

	cout<<count_letters - 1<<"\t|\t"<<lpr<<endl;

	delete tess_api;
}





void RecognizeLP::readNRecognize(VideoCapture& cap, Mat& scene_plate, string& lpr,int& count_letters, ofstream& lpFile){
	cout << "OCR: starts" << endl;
	while(cap.read(scene_plate)){


		read_image(scene_plate.cols, scene_plate.rows, (char*)scene_plate.ptr(),scene_plate,lpr,count_letters);
	}

	cout<<endl<<endl;
	lpFile.open("../lpNumbers.txt", std::ofstream::app);
	non_lpFile.open("../non_lpNumbers.txt", std::ofstream::app);
	cout<<"##################################################################"<<endl;
	cout<<"##--Length: "<<lpr.length()<<"\t--##";
	if(lpr.length() == 7 || lpr.length() ==10){	
		cout<<"\t\t##--License Plate No: "<<lpr<<"--##"<<endl;
		if (lpFile.is_open())
		{
			lpFile <<lpr<<"\n";
		}
		else cout << "Unable to open file";

	}
	else{
		cout<<"License Plate not detected"<<endl;
		cout<<"\t\t##--License Plate No: "<<lpr<<"--##"<<endl;
		if (non_lpFile.is_open())
		{
			non_lpFile <<lpr<<"\n";
		}
		else cout << "Unable to open file";
	}

	cout<<"##################################################################"<<endl;
	lpFile.close();
	non_lpFile.close();

}


RecognizeLP::~RecognizeLP(){
	//lpFile.close();
}
