#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/06_PlayVideo.cpp



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//-------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>  
using namespace cv;  

//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-------------------------------------------------------------------------------------------------
int main( )  
{  
	//【1】讀入視訊
	VideoCapture capture("/home/peter/opencv-2.4.11/samples/cpp/mao/1.avi");
//        VideoCapture capture("/home/peter/opencv-2.4.11/samples/cpp/mao/cube4.avi");

	//【2】循環顯示每一幅
	while(1)  
	{  
		Mat frame;//定義一個Mat變數，用于存儲每一幅的圖像
		capture>>frame;  //讀取現在幅
		imshow("讀取視訊",frame);  //顯示現在幅
		moveWindow("讀取視訊",100,100);  //顯示現在幅
		waitKey(30);  //延時30ms
	}  
	return 0;     
}  
