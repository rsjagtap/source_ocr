/*
 * test.cpp
 *
 *  Created on: 21-Jun-2016
 *      Author: rohit
 */
#include "DetectLP.h"

#define SHOW_STEPS

int main( int argc, char** argv ){

	DetectLP detectLP;
	ExtractSingleText extract;
	RecognizeLP detect;

	VideoCapture capture(argv[1]);
	capture.set(CV_CAP_PROP_BUFFERSIZE, 1000);
	string cascadeFile = argv[2];
	int ldcascade = detectLP.loadCascade(cascadeFile);
	if(ldcascade){
		detectLP.createCapturer(capture);
		cout<<"working 1"<<endl;

			detectLP.createFolderToSvCroppedLP(detectLP.folderName);
			cout<<"working 2"<<endl;
			while(capture.isOpened()){
				cout<<"working 3"<<endl;
				detectLP.detectLPUseCascadeFile(capture,detectLP.src_img, detectLP.gray_img, detectLP.cars, detectLP.car_cascade);
				cout<<"working 4"<<endl;
				detectLP.saveCroppedLP(detectLP.folderName, detectLP.check, detectLP.cars, detectLP.src_img, detectLP.CarCount, detectLP.imageToSave, extract, detect, detectLP.even, detectLP.odd, detectLP.even_fix, detectLP.odd_fix,detectLP.count_check);
				//cout<<"working 5"<<endl;
				//detectLP.saveCroppedLP();
				cout<<"working 6"<<endl;
				detectLP.showResultLPOnFrame(detectLP.src_img);
				cout<<"working 7"<<endl;
			}

	}
}
