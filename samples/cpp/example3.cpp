//  file : /home/peter/opencv-2.4.11/samples/cpp/example3.cpp

#include <opencv2/opencv.hpp>  // full path ~/opencv-2.4.11/include/opencv2/opencv.hpp
#include <iostream>
#include <fstream> 
#include <sys/timeb.h>
#include <sys/time.h>


#define aaa cout << "MO: [aaaaaaaaa] FILE=%s " <<  __FILE__  <<  " FUNCTION=%s " <<  __FUNCTION__ <<  " LINE=%d" <<  __LINE__ << endl ;

using namespace cv; 
using namespace std;

int main( int argc, char** argv )
{

    cout <<" example3  " << endl;
//    cv::namedWindow( "example 2-3", cv::WINDOW_AUTOSIZE ); 
//
//    namedWindow( "Example3", WINDOW_AUTOSIZE ); 
    namedWindow( "Example3", WINDOW_NORMAL ); 
    resizeWindow("Example3", 1024, 768 ); 
//    resizeWindow("Example3", 800, 600 ); 

    cv::VideoCapture cap; 
    cap.open( "/home/peter/cube4.avi"  ); 

    int width = 100, height = 100;
    cv::Mat frame = Mat::zeros(height, width, CV_8UC3);
    while( 1 ) { 

	cap >> frame; 

	if( !frame.data ) break; // Ran out of film 

	cv::imshow( "Example3", frame ); 

	if( cv::waitKey(33) >= 0 ) break; 
    }

}
