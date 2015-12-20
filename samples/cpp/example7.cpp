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

    cout <<" example4  " << endl;

#if 1
    // comment out to try "Example 2-7"
    cout <<" Example2 7 " << endl;

    Mat img_rgb = cv::imread("lena.jpg"); 

    if( img_rgb.empty() ) {
	cout << " missing parameter. " << endl;
	return -1; 
    }

    Mat img_gry, img_cny; 
    cvtColor( img_rgb, img_gry, CV_BGR2GRAY); 

    Mat img_pyr; 
    pyrDown( img_gry, img_pyr ); 

    Mat img_pyr2; 
    pyrDown( img_pyr, img_pyr2 ); 

    namedWindow( "Example Gray", cv::WINDOW_AUTOSIZE ); 
    namedWindow( "Example Canny", cv::WINDOW_AUTOSIZE ); 
    imshow( "Example Gray", img_gry ); 

//    Canny( img_gry, img_cny, 10, 100, 3, true ); 
    Canny( img_pyr2, img_cny, 10, 100, 3, true ); 

    imshow( "Example Canny", img_cny ); 

    // Example 2-9 show values. >>
    int x = 16, y = 32; 
    Vec3b intensity = img_rgb.at< cv::Vec3b >(y, x); 
    uchar blue  = intensity.val[0]; // We could write img_rgb.at< cv::Vec3b >(x,y)[0] 
    uchar green = intensity.val[1]; 
    uchar red   = intensity.val[2]; 

    cout << "At (x,y) = (" << x << ", " << y << "): (blue, green, red) = (" << (unsigned int)blue << ", " << (unsigned int)green << ", " << (unsigned int)red << ")" << std::endl; 

    cout << "Gray pixel there is: " << (unsigned int)img_gry.at<uchar>(x, y) << std::endl; 

    x /= 4; y /= 4; 

    cout << "Pyramid2 pixel there is: " << (unsigned int)img_pyr2.at<uchar>(x, y) << std::endl; 

    // Example 2-9 show values. <<



    waitKey(0); 
    destroyWindow( "Example Gray" ); 
    destroyWindow( "Example Canny" ); 

#endif 

}
