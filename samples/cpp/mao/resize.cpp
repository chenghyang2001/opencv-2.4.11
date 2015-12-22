#include <stdio.h>
//:read /home/peter/mao/resize.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序51
//		程序描述：resize函數用法範例
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main( )
{
	//載入原始圖   
	Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");  //專案目錄下應該有一張名為1.jpg的素材圖
	Mat tmpImage,dstImage1,dstImage2;//臨時變數和目標圖的定義
	tmpImage=srcImage;//將原始圖賦給臨時變數

	//顯示原始圖  
	imshow("【原始圖】", srcImage);  
	moveWindow("【原始圖】", 100,100);  

	//進行尺寸調整操作
	resize(tmpImage,dstImage1,Size( tmpImage.cols/2, tmpImage.rows/2 ),(0,0),(0,0),3);
	resize(tmpImage,dstImage2,Size( tmpImage.cols*2, tmpImage.rows*2 ),(0,0),(0,0),3);

	//顯示效果圖  
	imshow("【效果圖】之一", dstImage1);  
	moveWindow("【效果圖】之一", 1000,100);  

	imshow("【效果圖】之二", dstImage2);  
	moveWindow("【效果圖】之二", 100,1000);  

	waitKey(0);  
	return 0;  
}
