#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/72_convexHull2.cpp




//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;


//-----------------------------------【巨集定義部分】-------------------------------------------- 
//  描述：定義一些輔助巨集 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "【原始圖視窗】"					//為視窗標題定義的巨集 
#define WINDOW_NAME2 "【效果圖視窗】"					//為視窗標題定義的巨集 



//-----------------------------------【全局變數宣告部分】--------------------------------------
//  描述：全局變數的宣告
//-----------------------------------------------------------------------------------------------
Mat g_srcImage; Mat g_grayImage;
int g_nThresh = 50;
int g_maxThresh = 255;
RNG g_rng(12345);
Mat srcImage_copy = g_srcImage.clone();
Mat g_thresholdImage_output;
vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;


//-----------------------------------【全局函數宣告部分】--------------------------------------
//   描述：全局函數的宣告
//-----------------------------------------------------------------------------------------------
static void ShowHelpText( );
void on_ThreshChange(int, void* );
void ShowHelpText();

//-----------------------------------【main( )函數】------------------------------------------
//   描述：控制臺應用程序的入口函數，我們的程序從這里開始執行
//-----------------------------------------------------------------------------------------------
int main(  )
{
	system("color 3F");
	ShowHelpText();

	// 加載源圖像
	g_srcImage = imread( "/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", 1 );

	// 將原圖轉換成灰度圖並進行模糊降噪
	cvtColor( g_srcImage, g_grayImage, CV_BGR2GRAY );
	blur( g_grayImage, g_grayImage, Size(3,3) );

	// 建立原圖視窗並顯示
	namedWindow( WINDOW_NAME1, CV_WINDOW_AUTOSIZE );
	imshow( WINDOW_NAME1, g_srcImage );
	moveWindow( WINDOW_NAME1, 100,100 );

	//建立捲軸
	createTrackbar( " 閾值:", WINDOW_NAME1, &g_nThresh, g_maxThresh, on_ThreshChange );
	on_ThreshChange( 0, 0 );//使用一次進行初始化

	waitKey(0);
	return(0);
}

//-----------------------------------【thresh_callback( )函數】----------------------------------  
//      描述：回調函數
//----------------------------------------------------------------------------------------------  
void on_ThreshChange(int, void* )
{
	// 對圖像進行二值化，控制閾值
	threshold( g_grayImage, g_thresholdImage_output, g_nThresh, 255, THRESH_BINARY );

	// 尋找輪廓
	findContours( g_thresholdImage_output, g_vContours, g_vHierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	// 瀏覽每個輪廓，尋找其凸包
	vector<vector<Point> >hull( g_vContours.size() );
	for( unsigned int i = 0; i < g_vContours.size(); i++ )
	{  
		convexHull( Mat(g_vContours[i]), hull[i], false );
	}

	// 繪出輪廓及其凸包
	Mat drawing = Mat::zeros( g_thresholdImage_output.size(), CV_8UC3 );
	for(unsigned  int i = 0; i< g_vContours.size(); i++ )
	{
		Scalar color = Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );
		drawContours( drawing, g_vContours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
		drawContours( drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
	}

	// 顯示效果圖
	imshow( WINDOW_NAME2, drawing );
	moveWindow( WINDOW_NAME2, 1000,100 );
}


//-----------------------------------【ShowHelpText( )函數】-----------------------------
//		 描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第72個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}
