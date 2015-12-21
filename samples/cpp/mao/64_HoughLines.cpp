#include <stdio.h>
//:read /home/peter/mao/64_HoughLines.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序64
//		程序描述：霍夫線變換綜合範例
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;


//-----------------------------------【全局變數宣告部分】--------------------------------------
//		描述：全局變數宣告
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage,g_midImage;//原始圖、中間圖和效果圖
vector<Vec4i> g_lines;//定義一個矢量結構g_lines用于存放得到的線段矢量集合
//變數接收的TrackBar位置參數
int g_nthreshold=100;

//-----------------------------------【全局函數宣告部分】--------------------------------------
//		描述：全局函數宣告
//-----------------------------------------------------------------------------------------------

static void on_HoughLines(int, void*);//回調函數
static void ShowHelpText();


//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main( )
{
	//改變console字體顏色
	system("color 4F");  

	ShowHelpText();

	//載入原始圖和Mat變數定義   
	Mat g_srcImage = imread("/home/peter/1.jpg");  //專案目錄下應該有一張名為1.jpg的素材圖

	//顯示原始圖  
	imshow("【原始圖】", g_srcImage);  

	//建立捲軸
	namedWindow("【效果圖】",1);
	createTrackbar("值", "【效果圖】",&g_nthreshold,200,on_HoughLines);

	//進行邊緣檢測和轉化為灰度圖
	Canny(g_srcImage, g_midImage, 50, 200, 3);//進行一次canny邊緣檢測
	cvtColor(g_midImage,g_dstImage, CV_GRAY2BGR);//轉化邊緣檢測後的圖為灰度圖

	//使用一次回調函數，使用一次HoughLinesP函數
	on_HoughLines(g_nthreshold,0);
	HoughLinesP(g_midImage, g_lines, 1, CV_PI/180, 80, 50, 10 );

	//顯示效果圖  
	imshow("【效果圖】", g_dstImage);  


	waitKey(0);  

	return 0;  

}


//-----------------------------------【on_HoughLines( )函數】--------------------------------
//		描述：【頂帽運算/黑帽運算】視窗的回調函數
//----------------------------------------------------------------------------------------------
static void on_HoughLines(int, void*)
{
	//定義局部變數儲存全局變數
	Mat dstImage=g_dstImage.clone();
	Mat midImage=g_midImage.clone();

	//使用HoughLinesP函數
	vector<Vec4i> mylines;
	HoughLinesP(midImage, mylines, 1, CV_PI/180, g_nthreshold+1, 50, 10 );

	//循環瀏覽繪製每一條線段
	for( size_t i = 0; i < mylines.size(); i++ )
	{
		Vec4i l = mylines[i];
		line( dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23,180,55), 1, CV_AA);
	}
	//顯示圖像
	imshow("【效果圖】",dstImage);
}

//-----------------------------------【ShowHelpText( )函數】----------------------------------
//		描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第64個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//輸出一些說明訊息
	printf("\n\n\n\t請調整捲軸觀察圖像效果~\n\n");


}
