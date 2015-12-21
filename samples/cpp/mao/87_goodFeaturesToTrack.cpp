#include <stdio.h>
//:read /home/peter/mao/87_goodFeaturesToTrack.cpp
//--------------------------------------【程式說明】-------------------------------------------
//		程式說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程式87
//		程式描述：Shi-Tomasi角點檢測範例
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
using namespace std;

//-----------------------------------【巨集定義部分】-------------------------------------------- 
//  描述：定義一些輔助巨集 
//----------------------------------------------------------------------------------------------
#define WINDOW_NAME "【Shi-Tomasi角點檢測】"        //為視窗標題定義的巨集 



//-----------------------------------【全局變數宣告部分】--------------------------------------
//          描述：全局變數宣告
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_grayImage;
int g_maxCornerNumber = 33;
int g_maxTrackbarNumber = 500;
RNG g_rng(12345);//初始化隨機數產生器


//-----------------------------【on_GoodFeaturesToTrack( )函數】----------------------------
//          描述：響應滑動條移動訊息的回調函數
//----------------------------------------------------------------------------------------------
void on_GoodFeaturesToTrack( int, void* )
{
	//【1】對變數小于等于1時的處理
	if( g_maxCornerNumber <= 1 ) { g_maxCornerNumber = 1; }

	//【2】Shi-Tomasi算法（goodFeaturesToTrack函數）的參數準備
	vector<Point2f> corners;
	double qualityLevel = 0.01;//角點檢測可接受的最小特征值
	double minDistance = 10;//角點之間的最小距離
	int blockSize = 3;//計算導數自相關矩陣時指定的鄰域范圍
	double k = 0.04;//權重系數
	Mat copy = g_srcImage.clone();	//復制源影像到一個臨時變數中，作為感興趣區域

	//【3】進行Shi-Tomasi角點檢測
	goodFeaturesToTrack( g_grayImage,//輸入影像
		corners,//檢測到的角點的輸出向量
		g_maxCornerNumber,//角點的最大數量
		qualityLevel,//角點檢測可接受的最小特征值
		minDistance,//角點之間的最小距離
		Mat(),//感興趣區域
		blockSize,//計算導數自相關矩陣時指定的鄰域范圍
		false,//不使用Harris角點檢測
		k );//權重系數


	//【4】輸出文字訊息
	cout<<"\t>此次檢測到的角點數量為："<<corners.size()<<endl;

	//【5】繪製檢測到的角點
	int r = 4;
	for( int i = 0; i < corners.size(); i++ )
	{ 
		//以隨機的顏色繪製出角點
		circle( copy, corners[i], r, Scalar(g_rng.uniform(0,255), g_rng.uniform(0,255),
			g_rng.uniform(0,255)), -1, 8, 0 ); 
	}

	//【6】顯示（更新）視窗
	imshow( WINDOW_NAME, copy );
}


//-----------------------------------【ShowHelpText( )函數】----------------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
static void ShowHelpText( )
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第87個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//輸出一些說明訊息
	printf("\n\n\n\t歡迎來到【Shi-Tomasi角點檢測】範例程式\n"); 
	printf("\n\t請調整滑動條觀察影像效果\n\n");

}


//--------------------------------------【main( )函數】-----------------------------------------
//          描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main(  )
{
	//【0】改變console字體顏色
	system("color 2F"); 

	//【0】顯示說明文字
	ShowHelpText();

	//【1】載入源影像並將其轉換為灰度圖
	g_srcImage = imread("1.jpg", 1 );
	cvtColor( g_srcImage, g_grayImage, CV_BGR2GRAY );

	//【2】建立視窗和滑動條，並進行顯示和回調函數初始化
	namedWindow( WINDOW_NAME, CV_WINDOW_AUTOSIZE );
	createTrackbar( "最大角點數", WINDOW_NAME, &g_maxCornerNumber, g_maxTrackbarNumber, on_GoodFeaturesToTrack );
	imshow( WINDOW_NAME, g_srcImage );
	on_GoodFeaturesToTrack( 0, 0 );

	waitKey(0);
	return(0);
}
