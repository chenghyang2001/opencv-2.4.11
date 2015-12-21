#include <stdio.h>
//:read /home/peter/mao/02_ShowImage.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序02
//		程序描述：簡單的OpenCV圖像顯示
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年03月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------


#include <opencv2/opencv.hpp>  //頭文件
using namespace cv;  //包含cv命名空間

int main( )
{    
	// 【1】讀入一張圖形，載入圖像
	Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");
	// 【2】顯示載入的圖形
	imshow("【原始圖】",srcImage);
	moveWindow("【原始圖】",100,100);
	// 【3】等待任意按鍵按下
	waitKey(0);
}  
