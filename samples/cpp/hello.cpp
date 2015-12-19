//file:    /home/peter/opencv-2.4.11/samples/cpp/hello.cpp   03:26  20151220 

#include <opencv2/opencv.hpp>  // full path ~/opencv-2.4.11/include/opencv2/opencv.hpp
#include <iostream>
#include <fstream> 
#include <sys/timeb.h>
#include <sys/time.h>


#define aaa cout << "MO: [aaaaaaaaa] FILE=%s " <<  __FILE__  <<  " FUNCTION=%s " <<  __FUNCTION__ <<  " LINE=%d" <<  __LINE__ << endl ;

using namespace cv; 
using namespace std;


int g_slider_position = 0; 
int g_run = 1, g_dontset = 0; //start out in single step mode 
cv::VideoCapture g_cap; 

void onTrackbarSlide( int pos, void *) { 
 g_cap.set( CV_CAP_PROP_POS_FRAMES, pos ); 
 if( !g_dontset ) 
 g_run = 1; 
 g_dontset = 0; 
} 

int getMilliCount(){
    timeb tb;
    ftime(&tb);
    int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}

int getMilliSpan(int nTimeStart){
    int nSpan = getMilliCount() - nTimeStart;
    if(nSpan < 0)
	nSpan += 0x100000 * 1000;
    return nSpan;
}


long long getMilliCount2(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long long mslong = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000; //get current timestamp in milliseconds
    return mslong ;
}




int main( int argc, char** argv )
{

#if 1

    struct timeval tp;
    gettimeofday(&tp, NULL);
    long long mslong = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000; //get current timestamp in milliseconds
    
    long long ms_start = getMilliCount2() ;    

    std::cout << "ms_start = "  << ms_start << std::endl;


    cout <<" try milliseconds example " << endl;

    printf("\n\nStarting timer...");


    // CODE YOU WANT TO TIME
    for(int i = 0; i < 1000000; i++){
	int a = 55/16 ;
    }


    long long ms_end = getMilliCount2() ;    

    std::cout << "ms_end = "  << ms_end << std::endl;

    printf("\n\nElapsed time = %u milliseconds", ms_end - ms_start);

    printf("\n\n");


#endif 

#if 0
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

    resizeWindow( "Example2", 500, 200 ); 
    waitKey( 0 ); 

    resizeWindow( "Example2", 1024, 720 ); 
    waitKey( 0 ); 

    resizeWindow( "Example2", 500, 200 ); 
    waitKey( 0 ); 

    resizeWindow( "Example2", 1024, 720 ); 
    waitKey( 0 ); 

//    moveWindow( "Example2", 300, 300 ); 
//    waitKey( 0 ); 

//    moveWindow( "Example2", 700, 300 ); 
//    waitKey( 0 ); 

    destroyWindow( "Example2" ); 
#endif 


#if 0
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

#endif 


#if 0
 cv::namedWindow( "Example2_4", cv::WINDOW_AUTOSIZE ); 
// g_cap.open( "cube4.avi"  ); 
 g_cap.open( "/home/peter/cube4.avi"  ); 

 int frames = (int) g_cap.get(CV_CAP_PROP_FRAME_COUNT); 
 int tmpw   = (int) g_cap.get(CV_CAP_PROP_FRAME_WIDTH); 
 int tmph   = (int) g_cap.get(CV_CAP_PROP_FRAME_HEIGHT); 
 cout << "Video has " << frames << " frames of dimensions(" << tmpw << ", " << tmph << ")." << endl; 

// g_cap.set( 1024);  // peter. 01:41  20151219  not work.

 cv::createTrackbar("Position", "Example2_4", &g_slider_position, frames, onTrackbarSlide); 

 cv::Mat frame; 

 while(1) { 
     if( g_run != 0 ) { 
	 g_cap >> frame; if(!frame.data) break; 
	 int current_pos = (int)g_cap.get(CV_CAP_PROP_POS_FRAMES); 
	 g_dontset = 1; 
	 cv::setTrackbarPos("Position", "Example2_4", current_pos); 
	 cv::imshow( "Example2_4", frame ); 
	 g_run-=1; 
     } 

     char c = (char) cv::waitKey(10); 
     if(c == 's') // single step 
     {g_run = 1; cout << "Single step, run = " << g_run << endl;} 
     if(c == 'r') // run mode 
     {g_run = -1; cout << "Run mode, run = " << g_run <<endl;} 
     if( (c == 27) || ( c=='q') ) // ESC key or q key
	 break; 
 }
#endif 



#if 0
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
#endif 

#if 0
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

#if 0
    // Example 2-10
    cout <<" Example2-10 " << endl;

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

#endif 



    return 0;
}


/* 
 * ===============================================================
   20151220

   1. Say create a new souce file example2.cpp, 
      then in build, enter "cmake .." -> "make -j8". 
      example2.cpp will be built and generate cpp-example-example2

   2. there is time esclipsed calculation sample code in file 
       /home/peter/opencv-2.4.11/samples/cpp/tutorial_code/core/how_to_scan_images/how_to_scan_images.cpp

	t = (double)getTickCount();
	for (int i = 0; i < times; ++i) {
	    LUT(I, lookUpTable, J);
	}
	t = 1000*((double)getTickCount() - t)/getTickFrequency();
	t /= times;
	cout << "Time of reducing with the LUT function (averaged for " << times << " runs): " << t << " milliseconds."<< endl;

 * ===============================================================
   20151219 
   
   1. install qt-sdk
      sudo apt-get install qt-sdk

   2. in buildqt, 
	  cmake -D WITH_QT=ON ..
	  make -j8
	  
3. try drawing api and code in 
    ~/opencv-2.4.11/samples/cpp/drawing.cpp
 
 
 */
