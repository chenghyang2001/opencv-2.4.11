#include <stdio.h>
//:read /home/peter/mao/18_UseMouse.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序18
//		程序描述：HelloOpenCV
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------

//---------------------------------【頭文件、命名空間包含部分】-----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//-------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
using namespace cv;

//-----------------------------------【巨集定義部分】--------------------------------------------
//  描述：定義一些輔助巨集 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME "【程序視窗】"        //為視窗標題定義的巨集 


//-----------------------------------【全局函數宣告部分】------------------------------------
//		描述：全局函數的宣告
//------------------------------------------------------------------------------------------------
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle( cv::Mat& img, cv::Rect box );
void ShowHelpText( );

//-----------------------------------【全局變數宣告部分】-----------------------------------
//		描述：全局變數的宣告
//-----------------------------------------------------------------------------------------------
Rect g_rectangle;
bool g_bDrawingBox = false;//是否進行繪製
RNG g_rng(12345);



//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始執行
//-------------------------------------------------------------------------------------------------
int main( int argc, char** argv ) 
{
	//【0】改變console字體顏色
//        system("color 9F"); 
	system("color 1F"); 

	//【0】顯示歡迎和說明文字
	ShowHelpText();

	//【1】準備參數
	g_rectangle = Rect(-1,-1,0,0);
	Mat srcImage(600, 800,CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1,-1,0,0);
	srcImage = Scalar::all(0);

	//【2】設定滑鼠操作回調函數
	namedWindow( WINDOW_NAME );
	setMouseCallback(WINDOW_NAME,on_MouseHandle,(void*)&srcImage);

	//【3】程序主循環，當進行繪製的標識表為真時，進行繪製
	while(1)
	{
		srcImage.copyTo(tempImage);//拷貝源圖到臨時變數
		if( g_bDrawingBox ) DrawRectangle( tempImage, g_rectangle );//當進行繪製的標識表為真，則進行繪製
		imshow( WINDOW_NAME, tempImage );
		moveWindow( WINDOW_NAME, 100,100 );
		if( waitKey( 10 ) == 27 ) break;//按下ESC鍵，程序退出
	}
	return 0;
}



//--------------------------------【on_MouseHandle( )函數】-----------------------------
//		描述：滑鼠回調函數，根據不同的滑鼠事件進行不同的操作
//-----------------------------------------------------------------------------------------------
void on_MouseHandle(int event, int x, int y, int flags, void* param)
{

	Mat& image = *(cv::Mat*) param;
	switch( event)
	{
		//滑鼠移動訊息
	case EVENT_MOUSEMOVE: 
		{
			if( g_bDrawingBox )//如果是否進行繪製的標識表為真，則記錄下長和寬到RECT型變數中
			{
				g_rectangle.width = x-g_rectangle.x;
				g_rectangle.height = y-g_rectangle.y;
			}
		}
		break;

		//左鍵按下訊息
	case EVENT_LBUTTONDOWN: 
		{
			g_bDrawingBox = true;
			g_rectangle =Rect( x, y, 0, 0 );//記錄起始點
		}
		break;

		//左鍵抬起訊息
	case EVENT_LBUTTONUP: 
		{
			g_bDrawingBox = false;//置標識表為false
			//對寬和高小于0的處理
			if( g_rectangle.width < 0 )
			{
				g_rectangle.x += g_rectangle.width;
				g_rectangle.width *= -1;
			}

			if( g_rectangle.height < 0 ) 
			{
				g_rectangle.y += g_rectangle.height;
				g_rectangle.height *= -1;
			}
			//使用函數進行繪製
			DrawRectangle( image, g_rectangle );
		}
		break;

	}
}



//-----------------------------------【DrawRectangle( )函數】------------------------------
//		描述：自定義的矩形繪製函數
//-----------------------------------------------------------------------------------------------
void DrawRectangle( cv::Mat& img, cv::Rect box )
{
	cv::rectangle(img,box.tl(),box.br(),cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255)));//隨機顏色
}


//-----------------------------------【ShowHelpText( )函數】-----------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第18個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//輸出一些說明訊息
	printf("\n\n\n\t歡迎來到【滑鼠互動示範】範例程序\n"); 
	printf("\n\n\t請在視窗中點擊滑鼠左鍵並拖動以繪製矩形\n");

}
