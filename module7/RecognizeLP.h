#ifndef RecognizeLP_H
#define RecognizeLP_H
#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#include <fstream>

using namespace std;
using namespace cv;


class RecognizeLP
{
	//	int result;
	public:

		//        Mat scene_plate;
		//        string lpr = "";
		//        int count_letters = 0;
		int count_non_letters;
		ofstream lpFile;

		Mat scene_plate;
		string lpr;
		int count_letters;

	//	myFile.open ("example.txt");

		RecognizeLP();
		~RecognizeLP();
		void read_image(int width, int height, char *image,Mat& scene_plate, string& lpr, int& count_letters);
		void captrureLP(VideoCapture& cap);
		void readNRecognize(VideoCapture& cap, Mat& scene_plate, string& lpr, int& count_letters, ofstream& lpFile);
};
#endif
