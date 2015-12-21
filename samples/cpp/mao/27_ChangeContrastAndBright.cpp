#include <stdio.h>
//:read /home/peter/mao/27_ChangeContrastAndBright.cpp


//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序27
//		程序描述：圖像對比度、亮度值調整
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//-----------------------------------【頭文件包含部分】---------------------------------------
//	描述：包含程序所依賴的頭文件
//---------------------------------------------------------------------------------------------- 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

//-----------------------------------【命名空間宣告部分】---------------------------------------
//	描述：包含程序所使用的命名空間
//-----------------------------------------------------------------------------------------------   
using namespace std;
using namespace cv;


//-----------------------------------【全局函數宣告部分】--------------------------------------
//	描述：全局函數宣告
//-----------------------------------------------------------------------------------------------
static void ContrastAndBright(int, void *);
void   ShowHelpText();

//-----------------------------------【全局變數宣告部分】--------------------------------------
//	描述：全局變數宣告
//-----------------------------------------------------------------------------------------------
int g_nContrastValue; //對比度值
int g_nBrightValue;  //亮度值
Mat g_srcImage,g_dstImage;
//-----------------------------------【main( )函數】--------------------------------------------
//	描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main(   )
{
	//改變控制臺前景色和背景色
	system("color 2F");  

	ShowHelpText();
	// 讀入用戶提供的圖像
	g_srcImage = imread( "/home/peter/1.jpg");
	if( !g_srcImage.data ) { printf("Oh，no，讀取g_srcImage圖形錯誤~！ \n"); return false; }
	g_dstImage = Mat::zeros( g_srcImage.size(), g_srcImage.type() );

	//設定對比度和亮度的初值
	g_nContrastValue=80;
	g_nBrightValue=80;

	//建立視窗
	namedWindow("【效果圖視窗】", 1);

	//建立軌跡條
	createTrackbar("對比度：", "【效果圖視窗】",&g_nContrastValue, 300,ContrastAndBright );
	createTrackbar("亮   度：", "【效果圖視窗】",&g_nBrightValue, 200,ContrastAndBright );

	//使用回調函數
	ContrastAndBright(g_nContrastValue,0);
	ContrastAndBright(g_nBrightValue,0);

	//輸出一些說明訊息
	cout<<endl<<"\t執行成功，請調整捲軸觀察圖像效果\n\n"
		<<"\t按下“q”鍵時，程序退出\n";

	//按下“q”鍵時，程序退出
	while(char(waitKey(1)) != 'q') {}
	return 0;
}




//-----------------------------------【ShowHelpText( )函數】----------------------------------
//		 描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第27個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


//-----------------------------【ContrastAndBright( )函數】------------------------------------
//	描述：改變圖像對比度和亮度值的回調函數
//-----------------------------------------------------------------------------------------------
static void ContrastAndBright(int, void *)
{

	// 建立視窗
	namedWindow("【原始圖視窗】", 1);

	// 三個for循環，執行運算 g_dstImage(i,j) = a*g_srcImage(i,j) + b
	for( int y = 0; y < g_srcImage.rows; y++ )
	{
		for( int x = 0; x < g_srcImage.cols; x++ )
		{
			for( int c = 0; c < 3; c++ )
			{
				g_dstImage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( (g_nContrastValue*0.01)*( g_srcImage.at<Vec3b>(y,x)[c] ) + g_nBrightValue );
			}
		}
	}

	// 顯示圖像
	imshow("【原始圖視窗】", g_srcImage);
	imshow("【效果圖視窗】", g_dstImage);
}


