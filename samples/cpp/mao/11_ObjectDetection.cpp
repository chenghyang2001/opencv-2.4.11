#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f11
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u4f86\u81eaOpenCV\u5b89\u88dd\u76ee\u9304\u4e0bSamples\u6587\u4ef6\u593e\u4e2d\u7684\u5b98\u65b9\u7bc4\u4f8b\u7a0b\u5e8f-\u4eba\u81c9\u8b58\u5225
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------


/**
 * @file ObjectDetection.cpp
 * @author A. Huaman ( based in the classic facedetect.cpp in samples/c )
 * @brief A simplified version of facedetect.cpp, show how to load a cascade classifier and how to find objects (Face + eyes) in a video stream
 */

//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//-------------------------------------------------------------------------------------------------
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;




void detectAndDisplay( Mat frame );

//--------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u3011----------------------------------------------
//		\u63cf\u8ff0\uff1a\u5ba3\u544a\u5168\u5c40\u8b8a\u6578
//-------------------------------------------------------------------------------------------------
//\u6ce8\u610f\uff0c\u9700\u8981\u628a"haarcascade_frontalface_alt.xml"\u548c"haarcascade_eye_tree_eyeglasses.xml"\u9019\u5169\u500b\u6587\u4ef6\u5fa9\u5236\u5230\u5c08\u6848\u8def\u5f91\u4e0b
String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
string window_name = "Capture - Face detection";
RNG rng(12345);


//--------------------------------\u3010help( )\u51fd\u6578\u3011----------------------------------------------
//		\u63cf\u8ff0\uff1a\u8f38\u51fa\u8aaa\u660e\u8a0a\u606f
//-------------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	cout <<"\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n"
		<<"\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c11\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n"
		<<	"\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" << CV_VERSION 
		<<"\n\n  ----------------------------------------------------------------------------" ;
}


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-------------------------------------------------------------------------------------------------
int main( void )
{
  VideoCapture capture;
  Mat frame;


  //-- 1. \u52a0\u8f09\u7d1a\u806f\uff08cascades\uff09
  if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
  if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

  //-- 2. \u8b80\u53d6\u8996\u8a0a
  capture.open(0);
  ShowHelpText();
  if( capture.isOpened() )
  {
    for(;;)
    {
      capture >> frame;

      //-- 3. \u5c0d\u73fe\u5728\u5e45\u4f7f\u7528\u5206\u985e\u5225\u5668\uff08Apply the classifier to the frame\uff09
      if( !frame.empty() )
       { detectAndDisplay( frame ); }
      else
       { printf(" --(!) No captured frame -- Break!"); break; }

      int c = waitKey(10);
      if( (char)c == 'c' ) { break; }

    }
  }
  return 0;
}


void detectAndDisplay( Mat frame )
{
   std::vector<Rect> faces;
   Mat frame_gray;

   cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
   equalizeHist( frame_gray, frame_gray );
   //-- \u4eba\u81c9\u6aa2\u6e2c
   face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

   for( size_t i = 0; i < faces.size(); i++ )
    {
      Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
      ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );

      Mat faceROI = frame_gray( faces[i] );
      std::vector<Rect> eyes;

      //-- \u5728\u81c9\u4e2d\u6aa2\u6e2c\u773c\u775b
      eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

      for( size_t j = 0; j < eyes.size(); j++ )
       {
         Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
         int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
         circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 3, 8, 0 );
       }
    }
   //-- \u986f\u793a\u6700\u7d42\u6548\u679c\u5716
   imshow( window_name, frame );
}
