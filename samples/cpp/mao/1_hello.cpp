#include <stdio.h>
//:read /home/peter/mao/1_hello.cpp
////  file : /home/peter/opencv-2.4.11/samples/cpp/example2.cpp

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

    cout <<" example 2-1 and example 2-2" << endl;

    // must use absolute path, can not use relative path ~/lena.jpg. will not work.
    Mat img = imread( "/home/peter/lena.jpg", -1 ); 

    if( img.empty() ) {

	cout << " missing parameter. " << endl;
	return -1; 
    }

//    namedWindow( "Example2", WINDOW_AUTOSIZE ); 
    namedWindow( "Example2", WINDOW_NORMAL ); 
//    namedWindow( "Example2", WINDOW_OPENGL ); 
    imshow( "Example2", img ); 

//    moveWindow( "Example2", 100, 100 ); 
//    waitKey( 0 ); 

    resizeWindow( "Example2", 500, 200 );  
    waitKey( 0 ); 

    resizeWindow( "Example2", 1024, 720 ); 
    waitKey( 0 ); 

    resizeWindow( "Example2", 500, 200 ); 
    waitKey( 0 ); 

    resizeWindow( "Example2", 1024, 720 ); 
    waitKey( 0 ); 

//    resizeWindow( "Example2", 500, 200 ); 
//    waitKey( 0 ); 

//    resizeWindow( "Example2", 1024, 720 ); 
//    waitKey( 0 ); 

//    resizeWindow( "Example2", 500, 200 ); 
//    waitKey( 0 ); 

//    resizeWindow( "Example2", 1024, 720 ); 
//    waitKey( 0 ); 

//    moveWindow( "Example2", 300, 300 ); 
//    waitKey( 0 ); 

//    moveWindow( "Example2", 700, 300 ); 
//    waitKey( 0 ); 

    destroyWindow( "Example2" ); 
}
