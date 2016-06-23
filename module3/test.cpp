#include "RecognizeLP.h"

int main( int argc, char** argv ){

	RecognizeLP detect;

	Mat scene_plate;
	string lpr = "";
	int count_letters = 0;
	//        int count_non_letters = 0;
	string lpPath = "/home/rohit/Desktop/source_ocr/module1/crop/crop%d.jpg";
	VideoCapture cap(lpPath);
	detect.captrureLP(cap);
	detect.readNRecognize(cap,scene_plate, lpr,count_letters);

}
