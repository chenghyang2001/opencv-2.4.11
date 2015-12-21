#include <stdio.h>
//:read /home/peter/mao/70_FindAndDrawContours.cpp

//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序70
//		程序描述：查詢並繪製輪廓綜合範例
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------


//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;


//-----------------------------------【巨集定義部分】-------------------------------------------- 
//		描述：定義一些輔助巨集 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "【原始圖視窗】"			//為視窗標題定義的巨集 
#define WINDOW_NAME2 "【輪廓圖】"					//為視窗標題定義的巨集 


//-----------------------------------【全局變數宣告部分】--------------------------------------
//		描述：全局變數的宣告
//-----------------------------------------------------------------------------------------------
Mat g_srcImage; 
Mat g_grayImage;
int g_nThresh = 80;
int g_nThresh_max = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
//vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;


//-----------------------------------【全局函數宣告部分】--------------------------------------
//		描述：全局函數的宣告
//-----------------------------------------------------------------------------------------------
static void ShowHelpText( );
void on_ThreshChange(int, void* );


//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//【0】改變console字體顏色
	system("color 1F"); 

	//【0】顯示歡迎和說明文字
	ShowHelpText( );

	// 加載源圖像
	g_srcImage = imread( "1.jpg", 1 );
	if(!g_srcImage.data ) { printf("讀取圖形錯誤，請確定目錄下是否有imread函數指定的圖形存在~！ \n"); return false; } 

	// 轉成灰度並模糊化降噪
	cvtColor( g_srcImage, g_grayImage, CV_BGR2GRAY );
	blur( g_grayImage, g_grayImage, Size(3,3) );

	// 建立視窗
	namedWindow( WINDOW_NAME1, CV_WINDOW_AUTOSIZE );
	imshow( WINDOW_NAME1, g_srcImage );

	//建立捲軸並初始化
	createTrackbar( "canny閾值", WINDOW_NAME1, &g_nThresh, g_nThresh_max, on_ThreshChange );
	on_ThreshChange( 0, 0 );

	waitKey(0);
	return(0);
}

//-----------------------------------【on_ThreshChange( )函數】------------------------------  
//      描述：回調函數
//----------------------------------------------------------------------------------------------  
void on_ThreshChange(int, void* )
{

#if 0

	// 用Canny算子檢測邊緣
	Canny( g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh*2, 3 );

	// 尋找輪廓
	findContours( g_cannyMat_output, g_vContours, g_vHierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	// 繪出輪廓
	Mat drawing = Mat::zeros( g_cannyMat_output.size(), CV_8UC3 );
	for( int i = 0; i< g_vContours.size(); i++ )
	{
		Scalar color = Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//任意值
		drawContours( drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point() );
	}

	// 顯示效果圖
	imshow( WINDOW_NAME2, drawing );
#endif
}


//-----------------------------------【ShowHelpText( )函數】----------------------------------  
//      描述：輸出一些說明訊息  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第70個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//輸出一些說明訊息  
	printf(   "\n\n\t歡迎來到【在圖形中尋找輪廓】範例程序~\n\n");  
	printf(   "\n\n\t按鍵操作說明: \n\n"  
		"\t\t鍵盤按鍵任意鍵- 退出程序\n\n"  
		"\t\t滑動捲軸-改變閾值\n" );  
}  
