#include <stdio.h>
//:read /home/peter/mao/03_ImageErode.cpp

//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序03
//		程序描述：簡單的OpenCV圖像腐蝕操作
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年03月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------

//-----------------------------------【頭文件包含部分】---------------------------------------
//		描述：包含程序所依賴的頭文件
//---------------------------------------------------------------------------------------------- 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//-----------------------------------【命名空間宣告部分】---------------------------------------
//		描述：包含程序所使用的命名空間
//-----------------------------------------------------------------------------------------------  
using namespace cv;

//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main(   )
{
	//載入原圖  
	Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");
	//顯示原圖
	imshow("【原圖】腐蝕操作", srcImage);
	//進行腐蝕操作 
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat dstImage;
	erode(srcImage, dstImage, element);
	//顯示效果圖 
	imshow("【效果圖】腐蝕操作", dstImage);
	moveWindow("【效果圖】腐蝕操作", 100,100);
	waitKey(0); 

	return 0;
}
