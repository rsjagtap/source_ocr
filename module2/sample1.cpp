#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/nonfree/features2d.hpp"
using namespace std;
using namespace cv;


void read_image(int width, int height, char *image);
Mat scene_plate;

int main( int argc, char** argv )
{

  cout << "OCR: starts" << endl;
  scene_plate = imread(argv[1], CV_LOAD_IMAGE_COLOR );
  read_image(scene_plate.cols, scene_plate.rows, (char*)scene_plate.ptr());
}


 void read_image(int width, int height, char *image)

 {
    cv::Mat Image(height, width, CV_8UC3, image);
    // you may need to define the area of interest, where the test is found

// initializing Tesseract API
 char *outText;
double confidence = 0;
do{
tesseract::TessBaseAPI *tess_api = new tesseract::TessBaseAPI();
if (tess_api->Init(NULL, "eng"))  // eng is a flag of which trained language you use, if you just train your own language, you gave "XYZ" as a falge, you have to use it here
   {
    cout<<"Could not initialize tesseract.\n";
    exit(1);
}
//tess_api->SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz012345789");
//tess_api->SetVariable("tessedit_char_whitelist", "0123456789");
tess_api->SetVariable("tessedit_char_whitelist", /*"ABCDEFGHIJKLMNOPQRSTUVWXYZ*/"0123456789");
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
tess_api->SetPageSegMode(tesseract::PSM_SINGLE_CHAR);
tess_api->SetImage((uchar*)scene_plate.data, scene_plate.size().width,scene_plate.size().height,scene_plate.channels(),scene_plate.step1());
tess_api->Recognize(0);
char* out =tess_api->GetUTF8Text();
confidence = tess_api->MeanTextConf();
cout<<"OCR output:"<< out<< "  with confidence "<<confidence<<endl;
}while(confidence < 90);
 }
