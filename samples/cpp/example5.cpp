//  file : /home/peter/opencv-2.4.11/samples/cpp/example4.cpp

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

    cout <<" Example2_5 and 2_6" << endl;
    namedWindow( "Example2_5-in", cv::WINDOW_AUTOSIZE ); 
    namedWindow( "Example2_5-out", cv::WINDOW_AUTOSIZE ); 

    Mat img = imread( "lena.jpg", -1 ); 

    if( img.empty() ) {
	cout << " missing parameter. " << endl;
	return -1; 
    }

    imshow( "Example2_5-in", img ); 

    Mat out; 

    out = img ; 

    // comment out to try "A Not-So-Simple Transformation"
    pyrDown( img, out ); 

    // comment out to try "A Simple Transformation" 
//    GaussianBlur( img, out, cv::Size(5,5), 3, 3); 
//    GaussianBlur( out, out, cv::Size(5,5), 3, 3); 

    imshow( "Example2_5-out", out ); 

    waitKey( 0 ); 
    destroyWindow( "Example2_5-in" ); 
    destroyWindow( "Example2_5-out" ); 


}
