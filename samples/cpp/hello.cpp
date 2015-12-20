//file:    /home/peter/opencv-2.4.11/samples/cpp/hello.cpp   03:26  20151220 

#include <opencv2/opencv.hpp>  // full path ~/opencv-2.4.11/include/opencv2/opencv.hpp
#include <iostream>
#include <fstream> 
#include <sys/timeb.h>
#include <sys/time.h>


#define aaa cout << "MO: [aaaaaaaaa] FILE=%s " <<  __FILE__  <<  " FUNCTION=%s " <<  __FUNCTION__ <<  " LINE=%d" <<  __LINE__ << endl ;

using namespace cv; 
using namespace std;



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

    // 1. load image example,    see /home/peter/opencv-2.4.11/samples/cpp/example2.cpp
    // 2. load video example,    see /home/peter/opencv-2.4.11/samples/cpp/example3.cpp
    // 3. add trackbar  example, see /home/peter/opencv-2.4.11/samples/cpp/example4.cpp
    // 4. image process example, see /home/peter/opencv-2.4.11/samples/cpp/example5.cpp
    // 5. image process example, see /home/peter/opencv-2.4.11/samples/cpp/example7.cpp

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
	  cmake -D WITH_QT=ON WITH_OPENGL=ON ..
	  make -j8
	  
3. try drawing api and code in 
    ~/opencv-2.4.11/samples/cpp/drawing.cpp
 
 
 */
