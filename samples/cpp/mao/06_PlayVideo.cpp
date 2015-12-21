#include <stdio.h>
//:read /home/peter/mao/06_PlayVideo.cpp

//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序06
//		程序描述：使用VideoCapture類別進行視訊讀取和播放
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年03月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------


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
//        VideoCapture capture("1.avi");
	VideoCapture capture("/home/peter/1.avi");

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
