#include <stdio.h>
//:read /home/peter/mao/EdgeDetection.cpp

//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序60
//		程序描述：邊緣檢測綜合範例——Canny算子,Sobel算子,Laplace算子,Scharr濾波器合輯
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;


//-----------------------------------【全局變數宣告部分】--------------------------------------
//		描述：全局變數宣告
//-----------------------------------------------------------------------------------------------
//原圖，原圖的灰度版，目標圖
Mat g_srcImage, g_srcGrayImage,g_dstImage;

//Canny邊緣檢測相關變數
Mat g_cannyDetectedEdges;
int g_cannyLowThreshold=1;//TrackBar位置參數  

//Sobel邊緣檢測相關變數
Mat g_sobelGradient_X, g_sobelGradient_Y;
Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;
int g_sobelKernelSize=1;//TrackBar位置參數  

//Scharr濾波器相關變數
Mat g_scharrGradient_X, g_scharrGradient_Y;
Mat g_scharrAbsGradient_X, g_scharrAbsGradient_Y;


//-----------------------------------【全局函數宣告部分】--------------------------------------
//		描述：全局函數宣告
//-----------------------------------------------------------------------------------------------
static void ShowHelpText( );
static void on_Canny(int, void*);//Canny邊緣檢測視窗捲軸的回調函數
static void on_Sobel(int, void*);//Sobel邊緣檢測視窗捲軸的回調函數
void Scharr( );//封裝了Scharr邊緣檢測相關程式碼的函數


//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//改變console字體顏色
	system("color 2F");  

	//顯示歡迎語
	ShowHelpText();

	//載入原圖
	g_srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");
	if( !g_srcImage.data ) { printf("Oh，no，讀取srcImage錯誤~！ \n"); return false; }

	//顯示原始圖
	namedWindow("【原始圖】");
	imshow("【原始圖】", g_srcImage);

	// 建立與src同類別型和大小的矩陣(dst)
	g_dstImage.create( g_srcImage.size(), g_srcImage.type() );

	// 將原圖像轉換為灰度圖像
	cvtColor( g_srcImage, g_srcGrayImage, CV_BGR2GRAY );

	// 建立顯示視窗
	namedWindow( "【效果圖】Canny邊緣檢測", CV_WINDOW_AUTOSIZE );
	namedWindow( "【效果圖】Sobel邊緣檢測", CV_WINDOW_AUTOSIZE );

	// 建立trackbar
	createTrackbar( "參數值：", "【效果圖】Canny邊緣檢測", &g_cannyLowThreshold, 120, on_Canny );
	createTrackbar( "參數值：", "【效果圖】Sobel邊緣檢測", &g_sobelKernelSize, 3, on_Sobel );

	// 使用回調函數
	on_Canny(0, 0);
	on_Sobel(0, 0);

	//使用封裝了Scharr邊緣檢測程式碼的函數
	Scharr( );

	//輪詢取得按鍵訊息，若按下Q，程序退出
	while((char(waitKey(1)) != 'q')) {}

	return 0;
}


//-----------------------------------【ShowHelpText( )函數】----------------------------------
//		描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第60個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//輸出一些說明訊息
	printf( "\n\n\t執行成功，請調整捲軸觀察圖像效果~\n\n"
		"\t按下“q”鍵時，程序退出。\n");
}


//-----------------------------------【on_Canny( )函數】----------------------------------
//		描述：Canny邊緣檢測視窗捲軸的回調函數
//-----------------------------------------------------------------------------------------------
void on_Canny(int, void*)
{
	// 先使用 3x3核心來降噪
	blur( g_srcGrayImage, g_cannyDetectedEdges, Size(3,3) );

	// 執行我們的Canny算子
	Canny( g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold*3, 3 );

	//先將g_dstImage內的所有元素設定為0 
	g_dstImage = Scalar::all(0);

	//使用Canny算子輸出的邊緣圖g_cannyDetectedEdges作為掩碼，來將原圖g_srcImage拷到目標圖g_dstImage中
	g_srcImage.copyTo( g_dstImage, g_cannyDetectedEdges);

	//顯示效果圖
	imshow( "【效果圖】Canny邊緣檢測", g_dstImage );
}



//-----------------------------------【on_Sobel( )函數】----------------------------------
//		描述：Sobel邊緣檢測視窗捲軸的回調函數
//-----------------------------------------------------------------------------------------
void on_Sobel(int, void*)
{
	// 求 X方向梯度
	Sobel( g_srcImage, g_sobelGradient_X, CV_16S, 1, 0, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );
	convertScaleAbs( g_sobelGradient_X, g_sobelAbsGradient_X );//計算絕對值，並將結果轉換成8位

	// 求Y方向梯度
	Sobel( g_srcImage, g_sobelGradient_Y, CV_16S, 0, 1, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );
	convertScaleAbs( g_sobelGradient_Y, g_sobelAbsGradient_Y );//計算絕對值，並將結果轉換成8位

	// 合並梯度
	addWeighted( g_sobelAbsGradient_X, 0.5, g_sobelAbsGradient_Y, 0.5, 0, g_dstImage );

	//顯示效果圖
	imshow("【效果圖】Sobel邊緣檢測", g_dstImage); 

}


//-----------------------------------【Scharr( )函數】----------------------------------
//		描述：封裝了Scharr邊緣檢測相關程式碼的函數
//-----------------------------------------------------------------------------------------
void Scharr( )
{
	// 求 X方向梯度
	Scharr( g_srcImage, g_scharrGradient_X, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( g_scharrGradient_X, g_scharrAbsGradient_X );//計算絕對值，並將結果轉換成8位

	// 求Y方向梯度
	Scharr( g_srcImage, g_scharrGradient_Y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( g_scharrGradient_Y, g_scharrAbsGradient_Y );//計算絕對值，並將結果轉換成8位

	// 合並梯度
	addWeighted( g_scharrAbsGradient_X, 0.5, g_scharrAbsGradient_Y, 0.5, 0, g_dstImage );

	//顯示效果圖
	imshow("【效果圖】Scharr濾波器", g_dstImage); 
}
