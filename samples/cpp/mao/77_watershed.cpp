#include <stdio.h>
//:read /home/peter/mao/77_watershed.cpp
//--------------------------------------【程式說明】-------------------------------------------
//		程式說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程式77
//		程式描述：分水嶺演算法綜合範例
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程式所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

//-----------------------------------【巨集定義部分】-------------------------------------------- 
//  描述：定義一些輔助巨集 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "【程式視窗1】"        //為視窗標題定義的巨集 
#define WINDOW_NAME2 "【分水嶺演算法效果圖】"        //為視窗標題定義的巨集

//-----------------------------------【全局函變數宣告部分】--------------------------------------
//		描述：全局變數的宣告
//-----------------------------------------------------------------------------------------------
Mat g_maskImage, g_srcImage;
Point prevPt(-1, -1);

//-----------------------------------【全局函數宣告部分】--------------------------------------
//		描述：全局函數的宣告
//-----------------------------------------------------------------------------------------------
static void ShowHelpText();
static void on_Mouse( int event, int x, int y, int flags, void* );


//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{	
	//【0】改變console字體顏色
	system("color 6F"); 

	//【0】顯示說明文字
	ShowHelpText( );

	//【1】載入原圖並顯示，初始化掩膜和灰度圖
	g_srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", 1);
	imshow( WINDOW_NAME1, g_srcImage );
	Mat srcImage,grayImage;
	g_srcImage.copyTo(srcImage);
	cvtColor(g_srcImage, g_maskImage, COLOR_BGR2GRAY);
	cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
	g_maskImage = Scalar::all(0);

	//【2】設定滑鼠回調函數
	setMouseCallback( WINDOW_NAME1, on_Mouse, 0 );

	//【3】輪詢按鍵，進行處理
	while(1)
	{
		//取得鍵值
		int c = waitKey(0);

		//若按鍵鍵值為ESC時，退出
		if( (char)c == 27 )
			break;

		//按鍵鍵值為2時，恢復源圖
		if( (char)c == '2' )
		{
			g_maskImage = Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			imshow( "image", g_srcImage );
		}

		//若檢測到按鍵值為1或者空格，則進行處理
		if( (char)c == '1' || (char)c == ' ' )
		{
			//定義一些參數
			int i, j, compCount = 0;
			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;

			//尋找輪廓
			findContours(g_maskImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

			//輪廓為空時的處理
			if( contours.empty() )
				continue;

			//拷貝掩膜
			Mat maskImage(g_maskImage.size(), CV_32S);
			maskImage = Scalar::all(0);

			//循環繪製出輪廓
			for( int index = 0; index >= 0; index = hierarchy[index][0], compCount++ )
				drawContours(maskImage, contours, index, Scalar::all(compCount+1), -1, 8, hierarchy, INT_MAX);

			//compCount為零時的處理
			if( compCount == 0 )
				continue;

			//產生隨機顏色
			vector<Vec3b> colorTab;
			for( i = 0; i < compCount; i++ )
			{
				int b = theRNG().uniform(0, 255);
				int g = theRNG().uniform(0, 255);
				int r = theRNG().uniform(0, 255);

				colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
			}

			//計算處理時間並輸出到視窗中
			double dTime = (double)getTickCount();
			watershed( srcImage, maskImage );
			dTime = (double)getTickCount() - dTime;
			printf( "\t處理時間 = %gms\n", dTime*1000./getTickFrequency() );

			//雙層循環，將分水嶺圖像瀏覽存入watershedImage中
			Mat watershedImage(maskImage.size(), CV_8UC3);
			for( i = 0; i < maskImage.rows; i++ )
				for( j = 0; j < maskImage.cols; j++ )
				{
					int index = maskImage.at<int>(i,j);
					if( index == -1 )
						watershedImage.at<Vec3b>(i,j) = Vec3b(255,255,255);
					else if( index <= 0 || index > compCount )
						watershedImage.at<Vec3b>(i,j) = Vec3b(0,0,0);
					else
						watershedImage.at<Vec3b>(i,j) = colorTab[index - 1];
				}

				//混合灰度圖和分水嶺效果圖並顯示最終的視窗
				watershedImage = watershedImage*0.5 + grayImage*0.5;
				imshow( WINDOW_NAME2, watershedImage );
		}
	}

	return 0;
}


//-----------------------------------【onMouse( )函數】---------------------------------------
//		描述：滑鼠訊息回調函數
//-----------------------------------------------------------------------------------------------
static void on_Mouse( int event, int x, int y, int flags, void* )
{
	//處理滑鼠不在視窗中的情況
	if( x < 0 || x >= g_srcImage.cols || y < 0 || y >= g_srcImage.rows )
		return;

	//處理滑鼠左鍵相關訊息
	if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
		prevPt = Point(-1,-1);
	else if( event == CV_EVENT_LBUTTONDOWN )
		prevPt = Point(x,y);

	//滑鼠左鍵按下並移動，繪製出白色線條
	else if( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) )
	{
		Point pt(x, y);
		if( prevPt.x < 0 )
			prevPt = pt;
		line( g_maskImage, prevPt, pt, Scalar::all(255), 5, 8, 0 );
		line( g_srcImage, prevPt, pt, Scalar::all(255), 5, 8, 0 );
		prevPt = pt;
		imshow(WINDOW_NAME1, g_srcImage);
	}
}


//-----------------------------------【ShowHelpText( )函數】----------------------------------  
//      描述：輸出一些說明訊息  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第77個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//輸出一些說明訊息  
	printf(  "\n\n\n\t歡迎來到【分水嶺演算法】範例程式~\n\n");  
	printf(  "\t請先用滑鼠在圖形視窗中標記出大致的區域，\n\n\t然後再按鍵【1】或者【SPACE】啟動算法。"
		"\n\n\t按鍵操作說明: \n\n"  
		"\t\t鍵盤按鍵【1】或者【SPACE】- 執行的分水嶺分割算法\n"  
		"\t\t鍵盤按鍵【2】- 恢復原始圖形\n"  
		"\t\t鍵盤按鍵【ESC】- 退出程式\n\n\n");  
}  
