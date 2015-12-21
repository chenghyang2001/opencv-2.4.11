#include <stdio.h>
//:read /home/peter/mao/37_ImageFiltering.cpp

//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序37
//		程序描述：五種圖像濾波綜合範例
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------

//-----------------------------------【頭文件包含部分】---------------------------------------
//		描述：包含程序所依賴的頭文件
//---------------------------------------------------------------------------------------------- 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

//-----------------------------------【命名空間宣告部分】---------------------------------------
//		描述：包含程序所使用的命名空間
//-----------------------------------------------------------------------------------------------  
using namespace std;
using namespace cv;


//-----------------------------------【全局變數宣告部分】--------------------------------------
//		描述：全局變數宣告
//-----------------------------------------------------------------------------------------------
Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3,g_dstImage4,g_dstImage5;
int g_nBoxFilterValue=6;  //方框濾波核心值
int g_nMeanBlurValue=10;  //均值濾波核心值
int g_nGaussianBlurValue=6;  //高斯濾波核心值
int g_nMedianBlurValue=10;  //中值濾波參數值
int g_nBilateralFilterValue=10;  //雙邊濾波參數值


//-----------------------------------【全局函數宣告部分】--------------------------------------
//		描述：全局函數宣告
//-----------------------------------------------------------------------------------------------
//軌跡條回調函數
static void on_BoxFilter(int, void *);		//方框濾波
static void on_MeanBlur(int, void *);		//均值塊濾波器
static void on_GaussianBlur(int, void *);			//高斯濾波器
static void on_MedianBlur(int, void *);			//中值濾波器
static void on_BilateralFilter(int, void *);			//雙邊濾波器
void ShowHelpText();


//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main(   )
{
	system("color 4F");  

	ShowHelpText();	

	// 載入原圖
	g_srcImage = imread( "/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", 1 );
	if( !g_srcImage.data ) { printf("讀取srcImage錯誤~！ \n"); return false; }

	//克隆原圖到四個Mat類別型中
	g_dstImage1 = g_srcImage.clone( );
	g_dstImage2 = g_srcImage.clone( );
	g_dstImage3 = g_srcImage.clone( );
	g_dstImage4 = g_srcImage.clone( );
	g_dstImage5 = g_srcImage.clone( );

	//顯示原圖
	namedWindow("【<0>原圖視窗】", 1);
	imshow("【<0>原圖視窗】",g_srcImage);


	//=================【<1>方框濾波】=========================
	//建立視窗
	namedWindow("【<1>方框濾波】", 1);
	//建立軌跡條
	createTrackbar("核心值：", "【<1>方框濾波】",&g_nBoxFilterValue, 50,on_BoxFilter );
	on_MeanBlur(g_nBoxFilterValue,0);
	imshow("【<1>方框濾波】", g_dstImage1);
	//=====================================================


	//=================【<2>均值濾波】==========================
	//建立視窗
	namedWindow("【<2>均值濾波】", 1);
	//建立軌跡條
	createTrackbar("核心值：", "【<2>均值濾波】",&g_nMeanBlurValue, 50,on_MeanBlur );
	on_MeanBlur(g_nMeanBlurValue,0);
	//======================================================


	//=================【<3>高斯濾波】===========================
	//建立視窗
	namedWindow("【<3>高斯濾波】", 1);
	//建立軌跡條
	createTrackbar("核心值：", "【<3>高斯濾波】",&g_nGaussianBlurValue, 50,on_GaussianBlur );
	on_GaussianBlur(g_nGaussianBlurValue,0);
	//=======================================================


	//=================【<4>中值濾波】===========================
	//建立視窗
	namedWindow("【<4>中值濾波】", 1);
	//建立軌跡條
	createTrackbar("參數值：", "【<4>中值濾波】",&g_nMedianBlurValue, 50,on_MedianBlur );
	on_MedianBlur(g_nMedianBlurValue,0);
	//=======================================================


	//=================【<5>雙邊濾波】===========================
	//建立視窗
	namedWindow("【<5>雙邊濾波】", 1);
	//建立軌跡條
	createTrackbar("參數值：", "【<5>雙邊濾波】",&g_nBilateralFilterValue, 50,on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue,0);
	//=======================================================


	//輸出一些說明訊息
	cout<<endl<<"\t執行成功，請調整捲軸觀察圖像效果~\n\n"
		<<"\t按下“q”鍵時，程序退出。\n";
	while(char(waitKey(1)) != 'q') {}

	return 0;
}

//-----------------------------【on_BoxFilter( )函數】------------------------------------
//		描述：方框濾波操作的回調函數
//-----------------------------------------------------------------------------------------------
static void on_BoxFilter(int, void *)
{
	//方框濾波操作
	boxFilter( g_srcImage, g_dstImage1, -1,Size( g_nBoxFilterValue+1, g_nBoxFilterValue+1));
	//顯示視窗
	imshow("【<1>方框濾波】", g_dstImage1);
}

//-----------------------------【on_MeanBlur( )函數】------------------------------------
//		描述：均值濾波操作的回調函數
//-----------------------------------------------------------------------------------------------
static void on_MeanBlur(int, void *)
{
	blur( g_srcImage, g_dstImage2, Size( g_nMeanBlurValue+1, g_nMeanBlurValue+1), Point(-1,-1));
	imshow("【<2>均值濾波】", g_dstImage2);

}

//-----------------------------【on_GaussianBlur( )函數】------------------------------------
//		描述：高斯濾波操作的回調函數
//-----------------------------------------------------------------------------------------------
static void on_GaussianBlur(int, void *)
{
	GaussianBlur( g_srcImage, g_dstImage3, Size( g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1 ), 0, 0);
	imshow("【<3>高斯濾波】", g_dstImage3);
}


//-----------------------------【on_MedianBlur( )函數】------------------------------------
//		描述：中值濾波操作的回調函數
//-----------------------------------------------------------------------------------------------
static void on_MedianBlur(int, void *)
{
	medianBlur ( g_srcImage, g_dstImage4, g_nMedianBlurValue*2+1 );
	imshow("【<4>中值濾波】", g_dstImage4);
}


//-----------------------------【on_BilateralFilter( )函數】------------------------------------
//		描述：雙邊濾波操作的回調函數
//-----------------------------------------------------------------------------------------------
static void on_BilateralFilter(int, void *)
{
	bilateralFilter ( g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue*2, g_nBilateralFilterValue/2 );
	imshow("【<5>雙邊濾波】", g_dstImage5);
}

//-----------------------------------【ShowHelpText( )函數】-----------------------------
//		 描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第37個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


