#include <stdio.h>
//:read /home/peter/mao/40_dilate_And_erode.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序40
//		程序描述：圖像腐蝕與膨脹綜合範例
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】-----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;


//-----------------------------------【全局變數宣告部分】--------------------------------------
//		描述：全局變數宣告
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage;//原始圖和效果圖
int g_nTrackbarNumer = 0;//0表示腐蝕erode, 1表示膨脹dilate
int g_nStructElementSize = 3; //結構元素(核心矩陣)的尺寸


//-----------------------------------【全局函數宣告部分】--------------------------------------
//		描述：全局函數宣告
//-----------------------------------------------------------------------------------------------
void Process();//膨脹和腐蝕的處理函數
void on_TrackbarNumChange(int, void *);//回調函數
void on_ElementSizeChange(int, void *);//回調函數
void ShowHelpText();

//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main( )
{
	//改變console字體顏色
	system("color 2F");  

	//載入原圖
	g_srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");
	if( !g_srcImage.data ) { printf("讀取srcImage錯誤~！ \n"); return false; }

	ShowHelpText();

	//顯示原始圖
	namedWindow("【原始圖】");
	imshow("【原始圖】", g_srcImage);

	//進行初次腐蝕操作並顯示效果圖
	namedWindow("【效果圖】");
	//取得自定義核
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));
	erode(g_srcImage, g_dstImage, element);
	imshow("【效果圖】", g_dstImage);

	//建立軌跡條
	createTrackbar("腐蝕/膨脹", "【效果圖】", &g_nTrackbarNumer, 1, on_TrackbarNumChange);
	createTrackbar("核心尺寸", "【效果圖】", &g_nStructElementSize, 21, on_ElementSizeChange);

	//輸出一些說明訊息
	cout<<endl<<"\t執行成功，請調整捲軸觀察圖像效果~\n\n"
		<<"\t按下“q”鍵時，程序退出。\n";

	//輪詢取得按鍵訊息，若下q鍵，程序退出
	while(char(waitKey(1)) != 'q') {}

	return 0;
}

//-----------------------------【Process( )函數】------------------------------------
//		描述：進行自定義的腐蝕和膨脹操作
//-----------------------------------------------------------------------------------------
void Process() 
{
	//取得自定義核
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));

	//進行腐蝕或膨脹操作
	if(g_nTrackbarNumer == 0) {    
		erode(g_srcImage, g_dstImage, element);
	}
	else {
		dilate(g_srcImage, g_dstImage, element);
	}

	//顯示效果圖
	imshow("【效果圖】", g_dstImage);
}


//-----------------------------【on_TrackbarNumChange( )函數】------------------------------------
//		描述：腐蝕和膨脹之間切換開關的回調函數
//-----------------------------------------------------------------------------------------------------
void on_TrackbarNumChange(int, void *) 
{
	//腐蝕和膨脹之間效果已經切換，回調函數體內需使用一次Process函數，使改變後的效果立即生效並顯示出來
	Process();
}


//-----------------------------【on_ElementSizeChange( )函數】-------------------------------------
//		描述：腐蝕和膨脹操作核心改變時的回調函數
//-----------------------------------------------------------------------------------------------------
void on_ElementSizeChange(int, void *)
{
	//核心尺寸已改變，回調函數體內需使用一次Process函數，使改變後的效果立即生效並顯示出來
	Process();
}


//-----------------------------------【ShowHelpText( )函數】-----------------------------
//		 描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第40個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}
