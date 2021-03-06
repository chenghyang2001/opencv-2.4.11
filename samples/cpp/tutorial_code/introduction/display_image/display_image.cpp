// error in this file could be caught while do make in ~/opencv-2.4.11/build
// since path is set within vim, thus gf is working.

// case 2. Include file for specific function for fast compile time
// full path ~/opencv-2.4.11/modules/core/include/opencv2/core/core.hpp
//#include <opencv2/core/core.hpp>   
//#include <opencv2/highgui/highgui.hpp>

// case 1. Include file for every supported OpenCV function 
#include <opencv2/opencv.hpp>  // full path ~/opencv-2.4.11/include/opencv2/opencv.hpp
#include <iostream>

using namespace cv;
using namespace std;

//#define aaa cout << "MO: [aaaaaaaaa] FILE= " <<  __FILE__  <<  " FUNCTION= " <<  __FUNCTION__ <<  " LINE=" <<  __LINE__ << endl ;
#define aaa cout << "MO: [aaaaaaaaa]  " <<    " FUNCTION= " <<  __FUNCTION__ <<  " LINE=" <<  __LINE__ << endl ;

int main( int argc, char** argv )
{

#if 0
    if( argc != 2)
    {
	aaa;
	aaa;
	cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
	return -1;
    }
    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);	// Read the file
#endif

//  Peter. 20151217  for quickly testing
    Mat image;
    image = imread("./lena.jpg", CV_LOAD_IMAGE_COLOR);	// Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow( "1111 Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "22222 Display window", image );                   // Show our image inside it.

    waitKey(0);   // Wait for a keystroke in the window
//    waitKey(5000);  // Wait for 5 seconds
    return 0;
}
