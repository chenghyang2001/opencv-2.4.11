
#include <stdio.h>
#include <stdio.h>

//---------------------------------【頭文件、命名空間包含部分】-------------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


//-----------------------------------【全局變數宣告部分】--------------------------------------
//	描述：全局變數宣告
//-----------------------------------------------------------------------------------------------
Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3;//存儲圖形的Mat類別型
int g_nBoxFilterValue=3;  //方框濾波參數值
int g_nMeanBlurValue=3;  //均值濾波參數值
int g_nGaussianBlurValue=3;  //高斯濾波參數值


//-----------------------------------【全局函數宣告部分】--------------------------------------
//	描述：全局函數宣告
//-----------------------------------------------------------------------------------------------
//四個軌跡條的回調函數
static void on_BoxFilter(int, void *);		//均值濾波
static void on_MeanBlur(int, void *);		//均值濾波
static void on_GaussianBlur(int, void *);			//高斯濾波
void ShowHelpText();


//-----------------------------------【main( )函數】--------------------------------------------
//	描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main(   )
{
	//改變console字體顏色
	system("color 5F");  

	//輸出說明文字
	ShowHelpText();

	// 載入原圖
	g_srcImage = imread( "/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", 1 );
	if( !g_srcImage.data ) { printf("Oh，no，讀取srcImage錯誤~！ \n"); return false; }

	//克隆原圖到三個Mat類別型中
	g_dstImage1 = g_srcImage.clone( );
	g_dstImage2 = g_srcImage.clone( );
	g_dstImage3 = g_srcImage.clone( );

	//顯示原圖
	namedWindow("【<0>原圖視窗】", 1);
	imshow("【<0>原圖視窗】",g_srcImage);
	moveWindow("【<0>原圖視窗】",100, 100);


	//=================【<1>方框濾波】==================
	//建立視窗
	namedWindow("【<1>方框濾波】", 1);
	//建立軌跡條
	createTrackbar("核心值：", "【<1>方框濾波】",&g_nBoxFilterValue, 40,on_BoxFilter );
	on_MeanBlur(g_nBoxFilterValue,0);
	imshow("【<1>方框濾波】", g_dstImage1);
	moveWindow("【<1>方框濾波】", 1000,100);
	//================================================

	//=================【<2>均值濾波】==================
	//建立視窗
	namedWindow("【<2>均值濾波】", 1);
	//建立軌跡條
	createTrackbar("核心值：", "【<2>均值濾波】",&g_nMeanBlurValue, 40,on_MeanBlur );
	on_MeanBlur(g_nMeanBlurValue,0);
	//================================================

	//=================【<3>高斯濾波】=====================
	//建立視窗
	namedWindow("【<3>高斯濾波】", 1);
	//建立軌跡條
	createTrackbar("核心值：", "【<3>高斯濾波】",&g_nGaussianBlurValue, 40,on_GaussianBlur );
	on_GaussianBlur(g_nGaussianBlurValue,0);
	//================================================


	//輸出一些說明訊息
	cout<<endl<<"\t執行成功，請調整捲軸觀察圖像效果~\n\n"
		<<"\t按下“q”鍵時，程序退出。\n";

	//按下“q”鍵時，程序退出
	while(char(waitKey(1)) != 'q') {}

	return 0;
}


//-----------------------------【on_BoxFilter( )函數】------------------------------------
//	描述：方框濾波操作的回調函數
//-----------------------------------------------------------------------------------------------
static void on_BoxFilter(int, void *)
{
	//方框濾波操作
	boxFilter( g_srcImage, g_dstImage1, -1,Size( g_nBoxFilterValue+1, g_nBoxFilterValue+1));
	//顯示視窗
	imshow("【<1>方框濾波】", g_dstImage1);
}


//-----------------------------【on_MeanBlur( )函數】------------------------------------
//	描述：均值濾波操作的回調函數
//-----------------------------------------------------------------------------------------------
static void on_MeanBlur(int, void *)
{
	//均值濾波操作
	blur( g_srcImage, g_dstImage2, Size( g_nMeanBlurValue+1, g_nMeanBlurValue+1), Point(-1,-1));
	//顯示視窗
	imshow("【<2>均值濾波】", g_dstImage2);
}


//-----------------------------【ContrastAndBright( )函數】------------------------------------
//	描述：高斯濾波操作的回調函數
//-----------------------------------------------------------------------------------------------
static void on_GaussianBlur(int, void *)
{
	//高斯濾波操作
	GaussianBlur( g_srcImage, g_dstImage3, Size( g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1 ), 0, 0);
	//顯示視窗
	imshow("【<3>高斯濾波】", g_dstImage3);
}


//-----------------------------------【ShowHelpText( )函數】----------------------------------
//		 描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第34個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}
