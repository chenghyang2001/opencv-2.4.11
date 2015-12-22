#include <stdio.h>
//:read /home/peter/mao/78_inpaint.cpp
//--------------------------------------【程式說明】-------------------------------------------
//		程式說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程式78
//		程式描述：影像修補範例
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
#include "opencv2/photo/photo.hpp"
#include <iostream>
using namespace cv;
using namespace std;


//-----------------------------------【巨集定義部分】-------------------------------------------- 
//  描述：定義一些輔助巨集 
//----------------------------------------------------------------------------------------------
#define WINDOW_NAME0 "【原始圖參考】"        //為視窗標題定義的巨集 
#define WINDOW_NAME1 "【原始圖】"        //為視窗標題定義的巨集 
#define WINDOW_NAME2 "【修補後的效果圖】"        //為視窗標題定義的巨集 


//-----------------------------------【全局變數宣告部分】--------------------------------------
//          描述：全局變數宣告
//-----------------------------------------------------------------------------------------------
Mat srcImage0,srcImage1, inpaintMask;
Point previousPoint(-1,-1);//原來的點坐標


//-----------------------------------【ShowHelpText( )函數】----------------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
static void ShowHelpText( )
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第78個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//輸出一些說明訊息
	printf("\n\n\n\t歡迎來到【影像修復】範例程式~\n"); 
	printf(  "\n\t請在進行影像修復操作之前，在【原始圖】視窗中進行適量的繪製" 
		"\n\n\t按鍵操作說明: \n\n" 
		"\t\t【滑鼠左鍵】-在影像上繪製白色線條\n\n"
		"\t\t鍵盤按鍵【ESC】- 退出程式\n\n" 
		"\t\t鍵盤按鍵【1】或【SPACE】-進行影像修復操作 \n\n"   );  
}


//-----------------------------------【On_Mouse( )函數】--------------------------------
//          描述：響應滑鼠訊息的回調函數
//----------------------------------------------------------------------------------------------
static void On_Mouse( int event, int x, int y, int flags, void* )
{
	//滑鼠左鍵彈起訊息
	if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
		previousPoint = Point(-1,-1);
	//滑鼠左鍵按下訊息
	else if( event == CV_EVENT_LBUTTONDOWN )
		previousPoint = Point(x,y);
	//滑鼠按下並移動，進行繪製
	else if( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) )
	{
		Point pt(x,y);
		if( previousPoint.x < 0 )
			previousPoint = pt;
		//繪製白色線條
		line( inpaintMask, previousPoint, pt, Scalar::all(255), 5, 8, 0 );
		line( srcImage1, previousPoint, pt, Scalar::all(255), 5, 8, 0 );
		previousPoint = pt;
		imshow(WINDOW_NAME1, srcImage1);
		moveWindow(WINDOW_NAME1, 1000,1000 );
	}
}


//--------------------------------------【main( )函數】-----------------------------------------
//          描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//改變console字體顏色
	system("color 2F"); 

	//顯示說明文字
	ShowHelpText();

	//載入原始圖並進行掩膜的初始化
	Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", -1);
	if(!srcImage.data ) { printf("讀取圖形錯誤，請確定目錄下是否有imread函數指定圖形存在~！ \n"); return false; } 
	srcImage0 = srcImage.clone();
	srcImage1 = srcImage.clone();
	inpaintMask = Mat::zeros(srcImage1.size(), CV_8U);

	//顯示原始圖參考
	imshow(WINDOW_NAME0, srcImage0);
	moveWindow(WINDOW_NAME0, 100,100);

	//顯示原始圖
	imshow(WINDOW_NAME1, srcImage1);
	moveWindow(WINDOW_NAME1, 1000,100);

	//設定滑鼠回調訊息
	setMouseCallback( WINDOW_NAME1, On_Mouse, 0 );

	//輪詢按鍵，根據不同的按鍵進行處理
	while (1)
	{
		//取得按鍵鍵值
		char c = (char)waitKey();

		//鍵值為ESC，程式退出
		if( c == 27 )
			break;

		//鍵值為2，恢復成原始影像
		if( c == '2' )
		{
			inpaintMask = Scalar::all(0);
			srcImage.copyTo(srcImage1);
			imshow(WINDOW_NAME1, srcImage1);
		}

		//鍵值為1或者空格，進行影像修補操作
		if( c == '1' || c == ' ' )
		{
			Mat inpaintedImage;
			inpaint(srcImage1, inpaintMask, inpaintedImage, 3, CV_INPAINT_TELEA);
			imshow(WINDOW_NAME2, inpaintedImage);
		}
	}

	return 0;
}
