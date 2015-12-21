#include <stdio.h>
//:read /home/peter/mao/75_approxPolyDP.cpp

//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序75
//		程序描述：建立輪廓邊界框
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

//-----------------------------------【命名空間宣告部分】--------------------------------------
//          描述：包含程序所使用的命名空間
//-----------------------------------------------------------------------------------------------
using namespace cv;

//-----------------------------------【巨集定義部分】-------------------------------------------- 
//  描述：定義一些輔助巨集 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "【原始圖視窗】"        //為視窗標題定義的巨集 
#define WINDOW_NAME2 "【效果圖視窗】"        //為視窗標題定義的巨集 

//-----------------------------------【全局變數宣告部分】--------------------------------------
//  描述：全局變數的宣告
//-----------------------------------------------------------------------------------------------
Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 50;//閾值
int g_nMaxThresh = 255;//閾值最大值
RNG g_rng(12345);//隨機數產生器

//-----------------------------------【全局函數宣告部分】--------------------------------------
//   描述：全局函數的宣告
//-----------------------------------------------------------------------------------------------
void on_ContoursChange(int, void* );
static void ShowHelpText( );

//-----------------------------------【main( )函數】--------------------------------------------
//   描述：控制臺應用程序的入口函數，我們的程序從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( )
{
	//【0】改變console字體顏色
	system("color 1F"); 

	//【0】顯示歡迎和說明文字
	ShowHelpText( );

	//【1】載入3通道的原圖像
	g_srcImage = imread( "1.jpg", 1 );
	if(!g_srcImage.data ) { printf("讀取圖形錯誤，請確定目錄下是否有imread函數指定的圖形存在~！ \n"); return false; }  

	//【2】得到原圖的灰度圖像並進行平滑
	cvtColor( g_srcImage, g_grayImage, CV_BGR2GRAY );
	blur( g_grayImage, g_grayImage, Size(3,3) );

	//【3】建立原始圖視窗並顯示
	namedWindow( WINDOW_NAME1, CV_WINDOW_AUTOSIZE );
	imshow( WINDOW_NAME1, g_srcImage );

	//【4】設定捲軸並使用一次回調函數
	createTrackbar( " 閾值:", WINDOW_NAME1, &g_nThresh, g_nMaxThresh, on_ContoursChange );
	on_ContoursChange( 0, 0 );

	waitKey(0);

	return(0);
}

//----------------------------【on_ContoursChange( )函數】---------------------------------
//      描述：回調函數
//-------------------------------------------------------------------------------------------------  
void on_ContoursChange(int, void* )
{
	//定義一些參數
	
#if 0
	Mat threshold_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	// 使用Threshold檢測邊緣
	threshold( g_grayImage, threshold_output, g_nThresh, 255, THRESH_BINARY );

	// 找出輪廓
	findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	// 多邊形逼近輪廓 + 取得矩形和圓形邊界框
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );
	vector<Point2f>center( contours.size() );
	vector<float>radius( contours.size() );

	//一個循環，瀏覽所有部分，進行本程序最核心的操作
	for( unsigned int i = 0; i < contours.size(); i++ )
	{ 
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );//用指定精度逼近多邊形曲線 
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );//計算點集的最外面（up-right）矩形邊界
		minEnclosingCircle( contours_poly[i], center[i], radius[i] );//對給定的 2D點集，尋找最小面積的包圍圓形 
	}

	// 繪製多邊形輪廓 + 包圍的矩形框 + 圓形框
	Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
	for( int unsigned i = 0; i<contours.size( ); i++ )
	{
		Scalar color = Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//隨機設定顏色
		drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );//繪製輪廓
		rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );//繪製矩形
		circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );//繪製圓
	}

	// 顯示效果圖視窗
	namedWindow( WINDOW_NAME2, CV_WINDOW_AUTOSIZE );
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
	printf("\n\n\t\t\t此為本書OpenCV2版的第75個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//輸出一些說明訊息  
	printf("\n\n\n\t歡迎來到【建立包圍輪廓的矩形和圓形邊界框】範例程序~\n\n");  
	printf( "\n\n\t按鍵操作說明: \n\n"  
		"\t\t鍵盤按鍵【ESC】- 退出程序\n\n"  
		"\t\t滑動捲軸 - 改變閾值\n\n");  
}  

