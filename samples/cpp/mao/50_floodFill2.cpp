#include <stdio.h>
//:read /home/peter/mao/50_floodFill2.cpp

//--------------------------------------【程式說明】-------------------------------------------
//		程式說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程式50
//		程式描述：漫水填充算法綜合範例
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


//-----------------------------------【全局變數宣告部分】--------------------------------------  
//      描述：全局變數宣告  
//-----------------------------------------------------------------------------------------------  
Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;//定義原始圖、目標圖、灰階圖、掩模圖
int g_nFillMode = 1;//漫水填充的模式
int g_nLowDifference = 20, g_nUpDifference = 20;//負差最大值、正差最大值
int g_nConnectivity = 4;//表示floodFill函數標識表低八位的連通值
int g_bIsColor = true;//是否為彩色圖的標識表布爾值
bool g_bUseMask = false;//是否顯示掩膜視窗的布爾值
int g_nNewMaskVal = 255;//新的重新繪製的像素值


//-----------------------------------【ShowHelpText( )函數】----------------------------------  
//      描述：輸出一些說明訊息  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第50個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//輸出一些說明訊息  
	printf("\n\n\t歡迎來到漫水填充範例程式~");  
	printf("\n\n\t本範例根據滑鼠選取的點搜索影像中與之顏色相近的點，並用不同顏色標註。");  
	
	printf( "\n\n\t按鍵操作說明: \n\n"  
		"\t\t滑鼠點擊圖中區域- 進行漫水填充操作\n"  
		"\t\t鍵盤按鍵【ESC】- 退出程式\n"  
		"\t\t鍵盤按鍵【1】-  切換彩色圖/灰階圖模式\n"  
		"\t\t鍵盤按鍵【2】- 顯示/隱藏掩膜視窗\n"  
		"\t\t鍵盤按鍵【3】- 恢復原始影像\n"  
		"\t\t鍵盤按鍵【4】- 使用空範圍的漫水填充\n"  
		"\t\t鍵盤按鍵【5】- 使用漸變、固定範圍的漫水填充\n"  
		"\t\t鍵盤按鍵【6】- 使用漸變、浮動範圍的漫水填充\n"  
		"\t\t鍵盤按鍵【7】- 操作標誌符號的低八位元使用4 位元的連接模式\n"  
		"\t\t鍵盤按鍵【8】- 操作標誌符號的低八位元使用8 位元的連接模式\n\n" 	);  
}  


//-----------------------------------【onMouse( )函數】--------------------------------------  
//      描述：滑鼠訊息onMouse回調函數
//---------------------------------------------------------------------------------------------
static void onMouse( int event, int x, int y, int, void* )
{
	// 若滑鼠左鍵沒有按下，便返回
	if( event != CV_EVENT_LBUTTONDOWN )
		return;

	//-------------------【<1>使用floodFill函數之前的參數準備部分】---------------
	Point seed = Point(x,y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;//空範圍的漫水填充，此值設為0，否則設為全局的g_nLowDifference
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;//空範圍的漫水填充，此值設為0，否則設為全局的g_nUpDifference
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) +
		(g_nFillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);//標識表的0~7位為g_nConnectivity，8~15位為g_nNewMaskVal左移8位的值，16~23位為CV_FLOODFILL_FIXED_RANGE或者0。

	//隨機產生bgr值
	int b = (unsigned)theRNG() & 255;//隨機返回一個0~255之間的值
	int g = (unsigned)theRNG() & 255;//隨機返回一個0~255之間的值
	int r = (unsigned)theRNG() & 255;//隨機返回一個0~255之間的值
	Rect ccomp;//定義重繪區域的最小邊界矩形區域

	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.114);//在重繪區域像素的新值，若是彩色圖模式，取Scalar(b, g, r)；若是灰階圖模式，取Scalar(r*0.299 + g*0.587 + b*0.114)

	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;//目標圖的賦值
	int area;

	//--------------------【<2>正式使用floodFill函數】-----------------------------
	if( g_bUseMask )
	{
		threshold(g_maskImage, g_maskImage, 1, 128, CV_THRESH_BINARY);
		area = floodFill(dst, g_maskImage, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
		imshow( "mask", g_maskImage );
	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
	}

	imshow("效果圖", dst);
	cout << area << " 個像素被重繪\n";
}


//-----------------------------------【main( )函數】--------------------------------------------  
//      描述：控制臺應用程式的入口函數，我們的程式從這里開始  
//-----------------------------------------------------------------------------------------------  
int main( int argc, char** argv )
{
	//改變console字體顏色  
	system("color 2F");    

	//載入原圖
	g_srcImage = imread("1.jpg", 1);

	if( !g_srcImage.data ) { printf("Oh，no，讀取圖形image0錯誤~！ \n"); return false; }  

	//顯示說明文字
	ShowHelpText();

	g_srcImage.copyTo(g_dstImage);//拷貝源圖到目標圖
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//轉換三通道的image0到灰階圖
	g_maskImage.create(g_srcImage.rows+2, g_srcImage.cols+2, CV_8UC1);//利用image0的尺寸來初始化掩膜mask

	namedWindow( "效果圖",CV_WINDOW_AUTOSIZE );

	//建立Trackbar
	createTrackbar( "負差最大值", "效果圖", &g_nLowDifference, 255, 0 );
	createTrackbar( "正差最大值" ,"效果圖", &g_nUpDifference, 255, 0 );

	//滑鼠回調函數
	setMouseCallback( "效果圖", onMouse, 0 );

	//循環輪詢按鍵
	while(1)
	{
		//先顯示效果圖
		imshow("效果圖", g_bIsColor ? g_dstImage : g_grayImage);

		//取得鍵盤按鍵
		int c = waitKey(0);
		//判斷ESC是否按下，若按下便退出
		if( (c & 255) == 27 )
		{
			cout << "程式退出...........\n";
			break;
		}

		//根據按鍵的不同，進行各種操作
		switch( (char)c )
		{
			//如果鍵盤“1”被按下，效果圖在在灰階圖，彩色圖之間互換
		case '1':
			if( g_bIsColor )//若原來為彩色，轉為灰階圖，並且將掩膜mask所有元素設定為0
			{
				cout << "鍵盤“1”被按下，切換彩色/灰階模式，現在操作為將【彩色模式】切換為【灰階模式】\n";
				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
				g_maskImage = Scalar::all(0);	//將mask所有元素設定為0
				g_bIsColor = false;	//將標識表置為false，表示現在影像不為彩色，而是灰階
			}
			else//若原來為灰階圖，便將原來的彩圖image0再次拷貝給image，並且將掩膜mask所有元素設定為0
			{
				cout << "鍵盤“1”被按下，切換彩色/灰階模式，現在操作為將【彩色模式】切換為【灰階模式】\n";
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true;//將標識表置為true，表示現在影像模式為彩色
			}
			break;
			//如果鍵盤按鍵“2”被按下，顯示/隱藏掩膜視窗
		case '2':
			if( g_bUseMask )
			{
				destroyWindow( "mask" );
				g_bUseMask = false;
			}
			else
			{
				namedWindow( "mask", 0 );
				g_maskImage = Scalar::all(0);
				imshow("mask", g_maskImage);
				g_bUseMask = true;
			}
			break;
			//如果鍵盤按鍵“3”被按下，恢復原始影像
		case '3':
			cout << "按鍵“3”被按下，恢復原始影像\n";
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
			g_maskImage = Scalar::all(0);
			break;
			//如果按鍵"4" 被按下，使用空範圍的漫水填充
		case '4':
			cout << "按鍵“4“ 被按下，使用空範圍的漫水填充\n";
			g_nFillMode = 0;
			break;
			//如果按鍵"5" 被按下，使用漸變、固定範圍的漫水填充
		case '5':
			cout << "按鍵“5“ 被按下，使用漸變、固定範圍的漫水填充\n";
			g_nFillMode = 1;
			break;
			//如果按鍵"6" 被按下，使用漸變、浮動範圍的漫水填充
		case '6':
			cout << "按鍵“6“ 被按下，使用漸變、浮動範圍的漫水填充\n";
			g_nFillMode = 2;
			break;
			//如果按鍵"7" 被按下，操作標誌符號的低八位元使用4 位元的連接模式
		case '7':
			cout << "按鍵“7“ 被按下，操作標誌符號的低八位元使用4 位元的連接模式\n";
			g_nConnectivity = 4;
			break;
			//如果按鍵"8" 被按下，操作標誌符號的低八位元使用8 位元的連接模式
		case '8':
			cout << "按鍵“8“ 被按下，操作標誌符號的低八位元使用8 位元的連接模式\n";
			g_nConnectivity = 8;
			break;




		}
	}

	return 0;
}
