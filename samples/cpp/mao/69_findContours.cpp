#include <stdio.h>
//:read /home/peter/mao/69_findContours.cpp

//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序69
//		程序描述：基礎輪廓查詢——findContours+drawContours
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
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;


//-----------------------------------【main( )函數】--------------------------------------------

//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-------------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	// 【1】載入原始圖，且必須以二值圖模式載入
	Mat srcImage=imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", 0);
	imshow("原始圖",srcImage);
	moveWindow("原始圖",100,100);

	//【2】初始化結果圖
	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

	//【3】srcImage取大于閾值119的那部分
	srcImage = srcImage > 119;
	imshow( "取閾值後的原始圖", srcImage );
	moveWindow( "取閾值後的原始圖", 1000,100 );

	//【4】定義輪廓和層次結構
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//【5】查詢輪廓
	findContours( srcImage, contours, hierarchy,
		CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

	// 【6】瀏覽所有頂層的輪廓， 以隨機顏色繪製出每個連接組件顏色
	int index = 0;
	for( ; index >= 0; index = hierarchy[index][0] )
	{
		Scalar color( rand()&255, rand()&255, rand()&255 );
		drawContours( dstImage, contours, index, color, CV_FILLED, 8, hierarchy );
	}

	//【7】顯示最後的輪廓圖
	imshow( "輪廓圖", dstImage );
	moveWindow( "輪廓圖", 1000,1000 );

	waitKey(0);

}
