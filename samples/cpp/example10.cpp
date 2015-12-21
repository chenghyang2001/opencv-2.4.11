//  file : /home/peter/opencv-2.4.11/samples/cpp/example10.cpp

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

    cout <<" example10  " << endl;

    namedWindow( "Example2_10", cv::WINDOW_AUTOSIZE ); 
    VideoCapture cap; 

    if (argc==1) { 
	cout <<" open the default camera " << endl;
	cap.open(0); // open the default camera 

    } else { 
	cout <<" open the non-default camera " << endl;
	cap.open(argv[1]); 
    } 

    if( !cap.isOpened() ) { // check if we succeeded 

	std::cerr << "Couldn't open capture." << std::endl; 
	cout <<" Couldn't open capture. " << endl;
	return -1; 
    } 
    else {
	cout <<" Succeed in opening capture. " << endl;
    }

    cv::Mat frame; 
    while( 1 ) { 

	cap >> frame; 

	if( !frame.data ) break; // Ran out of film 

	cv::imshow( "Example3", frame ); 

	if( cv::waitKey(33) >= 0 ) break; 
    }




}
