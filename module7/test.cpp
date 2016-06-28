/*
 * test.cpp
 *
 *  Created on: 21-Jun-2016
 *      Author: rohit
 */
#include "DetectLP.h"

///#define SHOW_STEPS

int main( int argc, char** argv ){

	DetectLP detectLP;
	VideoCapture capture(argv[1]);
	string cascadeFile = argv[2];
	int ldcascade = detectLP.loadCascade(cascadeFile);
	if(ldcascade){
		detectLP.createCapturer(capture);
		cout<<"working 1"<<endl;

			detectLP.createFolderToSvCroppedLP();
			cout<<"working 2"<<endl;
			while(capture.isOpened()){
				cout<<"working 3"<<endl;
				detectLP.detectLPUseCascadeFile(capture);
				cout<<"working 4"<<endl;
				detectLP.saveCroppedLP();
				//cout<<"working 5"<<endl;
				//detectLP.saveCroppedLP();
				cout<<"working 6"<<endl;
				detectLP.showResultLPOnFrame();
				cout<<"working 7"<<endl;
			}

	}
}
