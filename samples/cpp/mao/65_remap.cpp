#include <stdio.h>
//:read /home/peter/mao/65_remap.cpp
//--------------------------------------【程式說明】-------------------------------------------
//		程式說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程式65
//		程式描述：remap函數用法範例
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程式所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;


//-----------------------------------【main( )函數】--------------------------------------------
//          描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main(  )
{
	//【0】變數定義
	Mat srcImage, dstImage;
	Mat map_x, map_y;

	//【1】載入原始圖
	srcImage = imread( "1.jpg", 1 );
	if(!srcImage.data ) { printf("讀取圖形錯誤，請確定目錄下是否有imread函數指定的圖形存在~！ \n"); return false; }  
	imshow("原始圖",srcImage);

	//【2】建立和原始圖一樣的效果圖，x重映射圖，y重映射圖
	dstImage.create( srcImage.size(), srcImage.type() );
	map_x.create( srcImage.size(), CV_32FC1 );
	map_y.create( srcImage.size(), CV_32FC1 );

	//【3】雙層循環，瀏覽每一個像素點，改變map_x & map_y的值
	for( int j = 0; j < srcImage.rows;j++)
	{ 
		for( int i = 0; i < srcImage.cols;i++)
		{
			//改變map_x & map_y的值. 
			map_x.at<float>(j,i) = static_cast<float>(i);
			map_y.at<float>(j,i) = static_cast<float>(srcImage.rows - j);
		} 
	}

	//【4】進行重映射操作
	remap( srcImage, dstImage, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0, 0) );

	//【5】顯示效果圖
	imshow( "【程式視窗】", dstImage );
	waitKey();

	return 0;
}

