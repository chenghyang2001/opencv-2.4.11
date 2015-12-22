#include <stdio.h>
//:read /home/peter/mao/68_equalizeHist.cpp
//--------------------------------------【程式說明】-------------------------------------------
//		程式說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程式68
//		程式描述：直條圖均衡化
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------


//---------------------------------【頭檔案、命名空間包含部分】---------------------------
//          描述：包含程式所使用的頭檔案和命名空間
//-----------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;


//--------------------------------------【main( )函數】-----------------------------------------
//          描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( )
{
	// 【1】加載源圖像
	Mat srcImage, dstImage;
	srcImage = imread( "/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", 1 );
	if(!srcImage.data ) { printf("讀取圖形錯誤，請確定目錄下是否有imread函數指定圖形存在~！ \n"); return false; } 

	// 【2】轉為灰度圖並顯示出來
	cvtColor( srcImage, srcImage, CV_BGR2GRAY );
	imshow( "原始圖", srcImage );
	moveWindow( "原始圖", 100,100 );

	// 【3】進行直條圖均衡化
	equalizeHist( srcImage, dstImage );

	// 【4】顯示結果
	imshow( "經過直條圖均衡化後的圖", dstImage );
	moveWindow( "經過直條圖均衡化後的圖", 1000,100 );

	// 等待用戶按鍵退出程式
	waitKey(0);
	return 0;

}
