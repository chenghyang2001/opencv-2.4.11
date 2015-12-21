#include <stdio.h>
//:read /home/peter/mao/84_matchTemplate.cpp
//--------------------------------------【程式說明】-------------------------------------------
//		程式說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程式84
//		程式描述：範本比對範例
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭檔案、命名空間包含部分】----------------------------
//		描述：包含程式所使用的頭檔案和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;


//-----------------------------------【巨集定義部分】-------------------------------------------- 
//  描述：定義一些輔助巨集 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "【原始圖形】"        //為視窗標題定義的巨集 
#define WINDOW_NAME2 "【比對視窗】"        //為視窗標題定義的巨集 

//-----------------------------------【全局變數宣告部分】------------------------------------
//          描述：全局變數的宣告
//-----------------------------------------------------------------------------------------------
Mat g_srcImage; Mat g_templateImage; Mat g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;

//-----------------------------------【全局函數宣告部分】--------------------------------------
//          描述：全局函數的宣告
//-----------------------------------------------------------------------------------------------
void on_Matching( int, void* );
static void ShowHelpText( );


//-----------------------------------【main( )函數】--------------------------------------------
//          描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main(  )
{
	//【0】改變console字體顏色
	system("color 1F"); 

	//【0】顯示說明文字
	ShowHelpText();

	//【1】載入原影像和範本塊
	g_srcImage = imread( "/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", 1 );
	g_templateImage = imread( "2.jpg", 1 );

	//【2】建立視窗
	namedWindow( WINDOW_NAME1, CV_WINDOW_AUTOSIZE );
	namedWindow( WINDOW_NAME2, CV_WINDOW_AUTOSIZE );

	//【3】建立滑動條並進行一次初始化
	createTrackbar( "方法", WINDOW_NAME1, &g_nMatchMethod, g_nMaxTrackbarNum, on_Matching );
	on_Matching( 0, 0 );

	waitKey(0);
	return 0;

}

//-----------------------------------【on_Matching( )函數】--------------------------------
//          描述：回調函數
//-------------------------------------------------------------------------------------------
void on_Matching( int, void* )
{
	//【1】給局部變數初始化
	Mat srcImage;
	g_srcImage.copyTo( srcImage );

	//【2】初始化用于結果輸出的矩陣
	int resultImage_cols =  g_srcImage.cols - g_templateImage.cols + 1;
	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	g_resultImage.create( resultImage_cols, resultImage_rows, CV_32FC1 );

	//【3】進行比對和標準化
	matchTemplate( g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod );
	normalize( g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat() );

	//【4】通過函數 minMaxLoc 定位最比對的位置
	double minValue; double maxValue; Point minLocation; Point maxLocation;
	Point matchLocation;
	minMaxLoc( g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat() );

	//【5】對於方法 SQDIFF 和 SQDIFF_NORMED, 越小的數值有著更高的比對結果. 而其余的方法, 數值越大比對效果越好
	if( g_nMatchMethod  == CV_TM_SQDIFF || g_nMatchMethod == CV_TM_SQDIFF_NORMED )
	{ matchLocation = minLocation; }
	else
	{ matchLocation = maxLocation; }

	//【6】繪製出矩形，並顯示最終結果
	rectangle( srcImage, matchLocation, Point( matchLocation.x + g_templateImage.cols , matchLocation.y + g_templateImage.rows ), Scalar(0,0,255), 2, 8, 0 );
	rectangle( g_resultImage, matchLocation, Point( matchLocation.x + g_templateImage.cols , matchLocation.y + g_templateImage.rows ), Scalar(0,0,255), 2, 8, 0 );

	imshow( WINDOW_NAME1, srcImage );
	imshow( WINDOW_NAME2, g_resultImage );

}



//-----------------------------------【ShowHelpText( )函數】----------------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第84個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//輸出一些說明訊息
	printf("\t歡迎來到【範本比對】範例程式~\n"); 
	printf("\n\n\t請調整滑動條觀察影像效果\n\n");
	printf(  "\n\t滑動條對應的方法數值說明: \n\n" 
		"\t\t方法【0】- 平方差比對法(SQDIFF)\n" 
		"\t\t方法【1】- 正規化平方差比對法(SQDIFF NORMED)\n" 
		"\t\t方法【2】- 相關比對法(TM CCORR)\n" 
		"\t\t方法【3】- 正規化相關比對法(TM CCORR NORMED)\n" 
		"\t\t方法【4】- 相關系數比對法(TM COEFF)\n" 
		"\t\t方法【5】- 正規化相關系數比對法(TM COEFF NORMED)\n" );  
}
