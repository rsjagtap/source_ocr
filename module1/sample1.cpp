#include <stdio.h>
#include <math.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

#include <baseapi.h>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

using namespace std;
using namespace cv;

RNG rng(12345);

int main(int argc, char* argv[])
{
    char *outText;
char imageToSave[50];
char imageToSave_crop[50];
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
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
//api->SetVariable("segment_penalty_dict_frequent_word", "0");
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

Mat gray, imgThresh;
Mat img_src = imread(argv[1]);
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

















                    //            cv::Mat imgThreshCopy = imgThresh.clone();

                                std::vector<std::vector<cv::Point> > contours;

                                //cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL,CV_CHAIN_APPROX_TC89_KCOS, Point(0, 0));
				cv::findContours(imgThreshCopy, contours, cv::RETR_CCOMP /*CV_RETR_TREE*/ , cv::CHAIN_APPROX_SIMPLE);

//                                cv::drawContours(imgThreshCopy, contours, -1,cv::Scalar(255.0, 255.0, 255.0), 4);
//                                cv::imshow("contours", imgThreshCopy);
  vector<vector<Point> > contours_poly( contours.size() );
  vector<Rect> boundRect( contours.size() );
vector<Rect> boundRectCrop(contours.size());
  vector<Point2f>center( contours.size() );
  vector<float>radius( contours.size() );

  for( int i = 0; i < contours.size(); i++ )
     { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
       boundRect[i] = boundingRect( Mat(contours_poly[i]) );
       minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
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


api->TesseractRect(imgThreshCopy.data, 1, imgThreshCopy.step1(), 0, 0, imgThreshCopy.cols, imgThreshCopy.rows);


Pix *image = pixCreate(imgThreshCopy.size().width, imgThreshCopy.size().height, 8);

for(int i=0; i<imgThreshCopy.rows; i++) 
    for(int j=0; j<imgThreshCopy.cols; j++) 
        pixSetPixel(image, j,i, (l_uint32) gray.at<uchar>(i,j));

 api->SetPageSegMode(static_cast<tesseract::PageSegMode>(atoi(argv[2])));
 api->SetOutputName("out");



//api->TesseractRect(image->data, 1, image->step1(), 0, 0, image->cols, image->rows); 
 
   api->SetImage(image);
api->Recognize(0);
//tesseract::PageIteratorLevel level1 = tesseract:: RIL_SYMBOL;
    // Get OCR result
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);

//float conf = 0;
//float conf_avg = 0;
int letter_count = 0;
int const_y1 = 0;
int const_y2 = 0;
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

//rectangle(imgThresh,Point(x1-20, const_y1-20),Point(x2+20, const_y2+20), Scalar(0,0,0), 2, 8, 0 );

Rect roi(x1-20, const_y1-20,(x2+20)-(x1-20),(const_y2+20)-(const_y1-20));

Mat crop_img = imgThresh(roi);
                sprintf(imageToSave,"%s//face%d.jpg","..",letter_count);
                imwrite(imageToSave, crop_img);
cv::imshow("crop", crop_img);

      printf("word: '%s';  \tconf: %.2f; BoundingBox: %d,%d,%d,%d;\n",
               word, conf, x1, y1, x2, y2);
      delete[] word;
    } while (ri->Next(level));
conf_avg = conf_avg/letter_count;
std::cout<<"avg conf is: "<<conf_avg<<std::endl;
  }



  /// Draw polygonal contour + bonding rects + circles
Mat drawing = Mat::zeros(imgThreshCopy.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar(255,123,0);
       drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
        if((const_y1-20) <= boundRect[i].y && (const_y2+20) >= (boundRect[i].y + boundRect[i].height) && (boundRect[i].height >= ((const_y2)- (const_y1))/2) ){
        cout<<"bheight: "<<boundRect[i].height << " y2-y1: "<<(const_y2)- (const_y1)<<endl;
       rectangle(imgThreshCopy, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
        cout<<"p1: "<<boundRect[i].tl() << " p2: "<<boundRect[i].br()<<endl;
//        boundRectCrop[i].tl() = boundRect[i].tl();
//        boundRectCrop[i].br() = boundRect[i].br();
Rect roi_crop(boundRect[i].x, boundRect[i].y,boundRect[i].width,boundRect[i].height);

Mat crop_img_text = imgThresh(roi_crop);
                sprintf(imageToSave_crop,"%s//crop%d.jpg","..",i);
                imwrite(imageToSave_crop, crop_img_text);
cv::imshow("crop_text", crop_img_text);







}
//       circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
     }
cout<<endl<<endl;
cv::imshow("contours_rect", imgThreshCopy);
cv::imshow("drawings", drawing);










//}while(conf_avg < 90);

cv::imshow("rect", imgThresh);
waitKey(0);

    // Destroy used object and release memory
//    api->End();
//    delete [] outText;
//    pixDestroy(&image);

//    return 0;
}
