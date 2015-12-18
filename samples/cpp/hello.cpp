
#include <opencv2/opencv.hpp>  // full path ~/opencv-2.4.11/include/opencv2/opencv.hpp
#include <iostream>

using namespace cv;
using namespace std;

#define aaa cout << "MO: [aaaaaaaaa] FILE=%s " <<  __FILE__  <<  " FUNCTION=%s " <<  __FUNCTION__ <<  " LINE=%d" <<  __LINE__ << endl ;

using namespace cv; 
using namespace std;

int main( int argc, char** argv )
{


    cv::namedWindow( "Example3", cv::WINDOW_AUTOSIZE ); 
    cv::VideoCapture cap; 
    // cap.open( string(argv[1]) ); 
    cap.open( "cube4.avi"  ); 
    cv::Mat frame; 
    while( 1 ) { 

	cap >> frame; 

	if( !frame.data ) break; // Ran out of film 

	cv::imshow( "Example3", frame ); 

	if( cv::waitKey(33) >= 0 ) break; 
    }



#if 0
    cout <<" hello 3 1 1" << endl;

    // Mat img = imread( argv[1], -1 ); 
    Mat img = imread( "lena.jpg", -1 ); 

    if( img.empty() ) {

	cout << " missing parameter. " << endl;
	return -1; 
    }

    namedWindow( "Example2", WINDOW_AUTOSIZE ); 
    imshow( "Example2", img ); 

    waitKey( 0 ); 
    destroyWindow( "Example2" ); 
#endif 

    return 0;
}
