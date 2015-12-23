#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/55_threshold.cpp




//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程式所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

//-----------------------------------【巨集定義部分】-------------------------------------------- 
//		描述：定義一些輔助巨集 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME "【程式視窗】"        //為視窗標題定義的巨集 


//-----------------------------------【全局變數宣告部分】--------------------------------------
//		描述：全局變數的宣告
//-----------------------------------------------------------------------------------------------
int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;

//-----------------------------------【全局函數宣告部分】--------------------------------------
//		描述：全局函數的宣告
//-----------------------------------------------------------------------------------------------
static void ShowHelpText( );//輸出說明文字
void on_Threshold( int, void* );//回調函數


//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( )
{
	//【0】改變console字體顏色
	system("color 1F"); 

	//【0】顯示歡迎和說明文字
	ShowHelpText( );

	//【1】讀入源圖形
	g_srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");
	if(!g_srcImage.data ) { printf("讀取圖形錯誤，請確定目錄下是否有imread函數指定的圖形存在~！ \n"); return false; }  
	imshow("原始圖",g_srcImage);

	//【2】存留一份原圖的灰度圖
	cvtColor( g_srcImage, g_grayImage, CV_RGB2GRAY );

	//【3】建立視窗並顯示原始圖
	namedWindow( WINDOW_NAME, CV_WINDOW_AUTOSIZE );

	//【4】建立滑動條來控制閾值
	createTrackbar( "模式",
		WINDOW_NAME, &g_nThresholdType,
		4, on_Threshold );

	createTrackbar( "參數值",
		WINDOW_NAME, &g_nThresholdValue,
		255, on_Threshold );

	//【5】初始化自定義的閾值回調函數
	on_Threshold( 0, 0 );

	// 【6】輪詢等待用戶按鍵，如果ESC鍵按下則退出程式
	while(1)
	{
		int key;
		key = waitKey( 20 );
		if( (char)key == 27 ){ break; }
	}

}

//-----------------------------------【on_Threshold( )函數】------------------------------------
//		描述：自定義的閾值回調函數
//-----------------------------------------------------------------------------------------------
void on_Threshold( int, void* )
{
	//使用閾值函數
	threshold(g_grayImage,g_dstImage,g_nThresholdValue,255,g_nThresholdType);

	//更新效果圖
	imshow( WINDOW_NAME, g_dstImage );
}

//-----------------------------------【ShowHelpText( )函數】----------------------------------  
//      描述：輸出一些說明訊息  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第55個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//輸出一些說明訊息  
	printf(	"\n\t歡迎來到【基本閾值操作】範例程式~\n\n");  
	printf(	"\n\t按鍵操作說明: \n\n"  
		"\t\t鍵盤按鍵【ESC】- 退出程式\n"  
		"\t\t捲軸模式0- 二進制閾值\n"  
		"\t\t捲軸模式1- 反二進制閾值\n"  
		"\t\t捲軸模式2- 截斷閾值\n"  
		"\t\t捲軸模式3- 反閾值化為0\n"  
		"\t\t捲軸模式4- 閾值化為0\n"  );  
}  
