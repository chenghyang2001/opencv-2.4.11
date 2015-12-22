#include <stdio.h>
//:read /home/peter/mao/05_Canny.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序05
//		程序描述：使用canny函數進行灰度邊緣檢測
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
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-------------------------------------------------------------------------------------------------
int main( )
{
	//【0】載入原始圖  
	Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");  //專案目錄下應該有一張名為1.jpg的素材圖
	imshow("【原始圖】Canny邊緣檢測", srcImage); 	//顯示原始圖 
	moveWindow("【原始圖】Canny邊緣檢測", 100,100); 	//顯示原始圖 

	Mat dstImage,edge,grayImage;	//參數定義
	//【1】建立與src同類別型和大小的矩陣(dst)
	dstImage.create( srcImage.size(), srcImage.type() );

	//【2】將原圖像轉換為灰度圖像
	cvtColor( srcImage, grayImage, CV_BGR2GRAY );

	//【3】先用使用 3x3核心來降噪
	blur( grayImage, edge, Size(3,3) );

	//【4】執行Canny算子
	Canny( edge, edge, 3, 9,3 );

	//【5】顯示效果圖 
	imshow("【效果圖】Canny邊緣檢測", edge); 
	moveWindow("【效果圖】Canny邊緣檢測", 1000,100); 

	waitKey(0); 

	return 0; 
}
