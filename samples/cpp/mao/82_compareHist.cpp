
#include <stdio.h>
#include <stdio.h>


//---------------------------------【頭檔案、命名空間包含部分】----------------------------
//		描述：包含程式所使用的頭檔案和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;


//-----------------------------------【ShowHelpText( )函數】-----------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第82個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//輸出一些說明訊息
	printf("\n\n歡迎來到【直條圖對比】範例程式~\n\n"); 

}


//--------------------------------------【main( )函數】-----------------------------------------
//          描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( )
{
	//【0】改變console字體顏色
	system("color 2F"); 

	//【1】顯示說明文字
	ShowHelpText();

	//【1】宣告儲存基準影像和另外兩張對比影像的矩陣( RGB 和 HSV )
	Mat srcImage_base, hsvImage_base;
	Mat srcImage_test1, hsvImage_test1;
	Mat srcImage_test2, hsvImage_test2;
	Mat hsvImage_halfDown;

	//【2】載入基準影像(srcImage_base) 和兩張測試影像srcImage_test1、srcImage_test2，並顯示
	srcImage_base = imread( "/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg",1 );
	srcImage_test1 = imread( "2.jpg", 1 );
	srcImage_test2 = imread( "3.jpg", 1 );
	//顯示載入的3張影像
	imshow("基準影像",srcImage_base);
	moveWindow("基準影像",100,100);

	imshow("測試影像1",srcImage_test1);
	moveWindow("測試影像1",1000,100);

	imshow("測試影像2",srcImage_test2);
	moveWindow("測試影像2",1000, 1000 );

	// 【3】將影像由BGR色彩空間轉換到 HSV色彩空間
	cvtColor( srcImage_base, hsvImage_base, CV_BGR2HSV );
	cvtColor( srcImage_test1, hsvImage_test1, CV_BGR2HSV );
	cvtColor( srcImage_test2, hsvImage_test2, CV_BGR2HSV );

	//【4】建立包含基準影像下半部的半身影像(HSV格式)
	hsvImage_halfDown = hsvImage_base( Range( hsvImage_base.rows/2, hsvImage_base.rows - 1 ), Range( 0, hsvImage_base.cols - 1 ) );

	//【5】初始化計算直條圖需要的實參
	// 對hue通道使用30個bin,對saturatoin通道使用32個bin
	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };
	// hue的取值范圍從0到256, saturation取值范圍從0到180
	float h_ranges[] = { 0, 256 };
	float s_ranges[] = { 0, 180 };
	const float* ranges[] = { h_ranges, s_ranges };
	// 使用第0和第1通道
	int channels[] = { 0, 1 };

	// 【6】建立儲存直條圖的 MatND 類別別別的實例:
	MatND baseHist;
	MatND halfDownHist;
	MatND testHist1;
	MatND testHist2;

	// 【7】計算基準影像，兩張測試影像，半身基準影像的HSV直條圖:
	calcHist( &hsvImage_base, 1, channels, Mat(), baseHist, 2, histSize, ranges, true, false );
	normalize( baseHist, baseHist, 0, 1, NORM_MINMAX, -1, Mat() );

	calcHist( &hsvImage_halfDown, 1, channels, Mat(), halfDownHist, 2, histSize, ranges, true, false );
	normalize( halfDownHist, halfDownHist, 0, 1, NORM_MINMAX, -1, Mat() );

	calcHist( &hsvImage_test1, 1, channels, Mat(), testHist1, 2, histSize, ranges, true, false );
	normalize( testHist1, testHist1, 0, 1, NORM_MINMAX, -1, Mat() );

	calcHist( &hsvImage_test2, 1, channels, Mat(), testHist2, 2, histSize, ranges, true, false );
	normalize( testHist2, testHist2, 0, 1, NORM_MINMAX, -1, Mat() );


	//【8】按順序使用4種對比標準將基準影像的直條圖與其余各直條圖進行對比:
	for( int i = 0; i < 4; i++ )
	{ 
		//進行影像直條圖的對比
		int compare_method = i;
		double base_base = compareHist( baseHist, baseHist, compare_method );
		double base_half = compareHist( baseHist, halfDownHist, compare_method );
		double base_test1 = compareHist( baseHist, testHist1, compare_method );
		double base_test2 = compareHist( baseHist, testHist2, compare_method );

		//輸出結果
		printf( " 方法 [%d] 的比對結果如下：\n\n 【基準圖 - 基準圖】：%f, 【基準圖 - 半身圖】：%f,【基準圖 - 測試圖1】： %f, 【基準圖 - 測試圖2】：%f \n-----------------------------------------------------------------\n", i, base_base, base_half , base_test1, base_test2 );
	}

	printf( "檢測結束。" );
	waitKey(0);
	return 0;
}
