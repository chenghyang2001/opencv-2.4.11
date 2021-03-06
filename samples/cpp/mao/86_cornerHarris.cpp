
#include <stdio.h>


//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程式所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;


//-----------------------------------【巨集定義部分】--------------------------------------------  
//  描述：定義一些輔助巨集  
//------------------------------------------------------------------------------------------------  
#define WINDOW_NAME1 "【程式視窗1】"        //為視窗標題定義的巨集  
#define WINDOW_NAME2 "【程式視窗2】"        //為視窗標題定義的巨集  

//-----------------------------------【全局變數宣告部分】--------------------------------------
//		描述：全局變數宣告
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_srcImage1,g_grayImage;
int thresh = 30; //現在閾值
int max_thresh = 175; //最大閾值


//-----------------------------------【全局函數宣告部分】--------------------------------------
//		描述：全局函數宣告
//-----------------------------------------------------------------------------------------------
void on_CornerHarris( int, void* );//回調函數
static void ShowHelpText();

//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//【0】改變console字體顏色
	system("color 3F");  

	//【0】顯示說明文字
	ShowHelpText();

	//【1】載入原始圖並進行克隆儲存
	g_srcImage = imread( "/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", 1 );
	if(!g_srcImage.data ) { printf("讀取圖形錯誤，請確定目錄下是否有imread函數指定的圖形存在~！ \n"); return false; }  
	imshow("原始圖",g_srcImage);
	moveWindow("原始圖",100,100);
	g_srcImage1=g_srcImage.clone( );

	//【2】存留一張灰度圖
	cvtColor( g_srcImage1, g_grayImage, CV_BGR2GRAY );

	//【3】建立視窗和捲軸
	namedWindow( WINDOW_NAME1, CV_WINDOW_AUTOSIZE );
	createTrackbar( "閾值: ", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris );

	//【4】使用一次回調函數，進行初始化
	on_CornerHarris( 0, 0 );

	waitKey(0);
	return(0);
}

//-----------------------------------【on_HoughLines( )函數】--------------------------------
//		描述：回調函數
//----------------------------------------------------------------------------------------------

void on_CornerHarris( int, void* )
{
	//---------------------------【1】定義一些局部變數-----------------------------
	Mat dstImage;//目標圖
	Mat normImage;//歸一化後的圖
	Mat scaledImage;//線性變換後的八位無表號整型的圖

	//---------------------------【2】初始化---------------------------------------
	//置零現在需要顯示的兩幅圖，即清除上一次使用此函數時他們的值
	dstImage = Mat::zeros( g_srcImage.size(), CV_32FC1 );
	g_srcImage1=g_srcImage.clone( );

	//---------------------------【3】正式檢測-------------------------------------
	//進行角點檢測
	cornerHarris( g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT );

	// 歸一化與轉換
	normalize( dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
	convertScaleAbs( normImage, scaledImage );//將歸一化後的圖線性變換成8位無表號整型 

	//---------------------------【4】進行繪製-------------------------------------
	// 將檢測到的，且表合閾值條件的角點繪製出來
	for( int j = 0; j < normImage.rows ; j++ )
	{ for( int i = 0; i < normImage.cols; i++ )
	{
		if( (int) normImage.at<float>(j,i) > thresh+80 )
		{
			circle( g_srcImage1, Point( i, j ), 5,  Scalar(10,10,255), 2, 8, 0 );
			circle( scaledImage, Point( i, j ), 5,  Scalar(0,10,255), 2, 8, 0 );
		}
	}
	}
	//---------------------------【4】顯示最終效果---------------------------------
	imshow( WINDOW_NAME1, g_srcImage1 );
	moveWindow( WINDOW_NAME1, 1000,100 );

	imshow( WINDOW_NAME2, scaledImage );
	moveWindow( WINDOW_NAME2, 500,500 );
	moveWindow( WINDOW_NAME2, 500,500 );

}

//-----------------------------------【ShowHelpText( )函數】----------------------------------
//		描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
//static void ShowHelpText()
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第86個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//輸出一些說明訊息
	printf("\n\n\n\t【歡迎來到Harris角點檢測範例程式~】\n\n");  
	printf("\n\t請調整捲軸觀察圖像效果~\n\n");
}
