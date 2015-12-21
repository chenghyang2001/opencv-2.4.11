#include <stdio.h>
//:read /home/peter/mao/17_CreateTrackbar.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序17
//		程序描述：為程序界面新增滑動條
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年6月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------


//---------------------------------【頭文件、命名空間包含部分】-------------------------------
//		描述：包含程序所使用的頭文件和命名空間
//-------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

//-----------------------------------【巨集定義部分】-------------------------------------------- 
//  描述：定義一些輔助巨集 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME "【滑動條的建立&線性混合範例】"        //為視窗標題定義的巨集 


//-----------------------------------【全局變數宣告部分】--------------------------------------
//		描述：全局變數宣告
//-----------------------------------------------------------------------------------------------
const int g_nMaxAlphaValue = 100;//Alpha值的最大值
int g_nAlphaValueSlider;//滑動條對應的變數
double g_dAlphaValue;
double g_dBetaValue;

//宣告存儲圖像的變數
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;


//-----------------------------------【on_Trackbar( )函數】--------------------------------
//		描述：響應滑動條的回調函數
//------------------------------------------------------------------------------------------
void on_Trackbar( int, void* )
{
	//求出現在alpha值相對於最大值的比例
	g_dAlphaValue = (double) g_nAlphaValueSlider/g_nMaxAlphaValue ;
	//則beta值為1減去alpha值
	g_dBetaValue = ( 1.0 - g_dAlphaValue );

	//根據alpha和beta值進行線性混合
	addWeighted( g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

	//顯示效果圖
	imshow( WINDOW_NAME, g_dstImage );
}


//-----------------------------【ShowHelpText( )函數】--------------------------------------
//		描述：輸出說明訊息
//-------------------------------------------------------------------------------------------------
//-----------------------------------【ShowHelpText( )函數】----------------------------------
//		描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第17個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


//--------------------------------------【main( )函數】-----------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{

	//顯示說明訊息
	ShowHelpText();

	//加載圖像 (兩圖像的尺寸需相同)
	g_srcImage1 = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");
	g_srcImage2 = imread("2.jpg");
	if( !g_srcImage1.data ) { printf("讀取第一幅圖形錯誤，請確定目錄下是否有imread函數指定圖形存在~！ \n"); return -1; }
	if( !g_srcImage2.data ) { printf("讀取第二幅圖形錯誤，請確定目錄下是否有imread函數指定圖形存在~！\n"); return -1; }

	//設定滑動條初值為70
	g_nAlphaValueSlider = 70;

	//建立視窗
	namedWindow(WINDOW_NAME, 1);

	//在建立的視窗中建立一個滑動條控制項
	char TrackbarName[50];
	sprintf( TrackbarName, "透明值 %d", g_nMaxAlphaValue );

	createTrackbar( TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar );

	//結果在回調函數中顯示
	on_Trackbar( g_nAlphaValueSlider, 0 );

	//按任意鍵退出
	waitKey(0);

	return 0;
}
