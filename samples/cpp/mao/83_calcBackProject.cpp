#include <stdio.h>
//:read /home/peter/mao/83_calcBackProject.cpp
//--------------------------------------【程式說明】-------------------------------------------
//		程式說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程式83
//		程式描述：反向投影範例程式
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭檔案、命名空間包含部分】----------------------------
//		描述：包含程式所使用的頭檔案和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;


//-----------------------------------【巨集定義部分】-------------------------------------------- 
//  描述：定義一些輔助巨集 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "【原始圖】"        //為視窗標題定義的巨集 


//-----------------------------------【全局變數宣告部分】--------------------------------------
//          描述：全局變數宣告
//-----------------------------------------------------------------------------------------------
Mat g_srcImage; Mat g_hsvImage; Mat g_hueImage;
int g_bins = 30;//直條圖組距

//-----------------------------------【全局函數宣告部分】--------------------------------------
//          描述：全局函數宣告
//-----------------------------------------------------------------------------------------------
static void ShowHelpText();
void on_BinChange(int, void* );

//--------------------------------------【main( )函數】-----------------------------------------
//          描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( )
{
	//【0】改變console字體顏色
	system("color 6F"); 

	//【0】顯示說明文字
	ShowHelpText();

	//【1】讀取源圖像，並轉換到 HSV 空間
	g_srcImage = imread( "1.jpg", 1 );
	if(!g_srcImage.data ) { printf("讀取圖形錯誤，請確定目錄下是否有imread函數指定圖形存在~！ \n"); return false; } 
	cvtColor( g_srcImage, g_hsvImage, CV_BGR2HSV );

	//【2】分離 Hue 色調通道
	g_hueImage.create( g_hsvImage.size(), g_hsvImage.depth() );
	int ch[ ] = { 0, 0 };
	mixChannels( &g_hsvImage, 1, &g_hueImage, 1, ch, 1 );

	//【3】建立 Trackbar 來輸入bin的數目
	namedWindow( WINDOW_NAME1 , CV_WINDOW_AUTOSIZE );
	createTrackbar("色調組距 ", WINDOW_NAME1 , &g_bins, 180, on_BinChange );
	on_BinChange(0, 0);//進行一次初始化

	//【4】顯示效果圖
	imshow( WINDOW_NAME1 , g_srcImage );

	// 等待用戶按鍵
	waitKey(0);
	return 0;
}


//-----------------------------------【on_HoughLines( )函數】--------------------------------
//          描述：響應滑動條移動訊息的回調函數
//---------------------------------------------------------------------------------------------
void on_BinChange(int, void* )
{
	//【1】參數準備
	MatND hist;
	int histSize = MAX( g_bins, 2 );
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };

	//【2】計算直條圖並歸一化
	calcHist( &g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false );
	normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );

	//【3】計算反向投影
	MatND backproj;
	calcBackProject( &g_hueImage, 1, 0, hist, backproj, &ranges, 1, true );

	//【4】顯示反向投影
	imshow( "反向投影圖", backproj );

	//【5】繪製直條圖的參數準備
	int w = 400; int h = 400;
	int bin_w = cvRound( (double) w / histSize );
	Mat histImg = Mat::zeros( w, h, CV_8UC3 );

	//【6】繪製直條圖
	for( int i = 0; i < g_bins; i ++ )
	{ rectangle( histImg, Point( i*bin_w, h ), Point( (i+1)*bin_w, h - cvRound( hist.at<float>(i)*h/255.0 ) ), Scalar( 100, 123, 255 ), -1 ); }

	//【7】顯示直條圖視窗
	imshow( "直條圖", histImg );
}


//-----------------------------------【ShowHelpText( )函數】----------------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第83個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//輸出一些說明訊息
	printf("\n\n\t歡迎來到【反向投影】範例程式\n\n"); 
	printf("\n\t請調整滑動條觀察圖像效果\n\n");

}
