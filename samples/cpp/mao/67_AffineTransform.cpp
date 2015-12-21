#include <stdio.h>
//:read /home/peter/mao/67_AffineTransform.cpp

//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序67
//		程序描述：仿射變換綜合範例
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
#include <iostream>
using namespace cv;
using namespace std;


//-----------------------------------【巨集定義部分】-------------------------------------------- 
//		描述：定義一些輔助巨集 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "【原始圖視窗】"					//為視窗標題定義的巨集 
#define WINDOW_NAME2 "【經過Warp後的圖像】"        //為視窗標題定義的巨集 
#define WINDOW_NAME3 "【經過Warp和Rotate後的圖像】"        //為視窗標題定義的巨集 



//-----------------------------------【全局函數宣告部分】--------------------------------------
//		描述：全局函數的宣告
//-----------------------------------------------------------------------------------------------
static void ShowHelpText( );


//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始執行
//-----------------------------------------------------------------------------------------------
int main(  )
{
	//【0】改變console字體顏色
	system("color 1F"); 

	//【0】顯示歡迎和說明文字
	ShowHelpText( );

	//【1】參數準備
	//定義兩組點，代表兩個三角形
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];
	//定義一些Mat變數
	Mat rotMat( 2, 3, CV_32FC1 );
	Mat warpMat( 2, 3, CV_32FC1 );
	Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	//【2】加載源圖像並作一些初始化
	srcImage = imread( "/home/peter/1.jpg", 1 );
	if(!srcImage.data ) { printf("讀取圖形錯誤，請確定目錄下是否有imread函數指定的圖形存在~！ \n"); return false; } 
	// 設定目標圖像的大小和類別型與源圖像一致
	dstImage_warp = Mat::zeros( srcImage.rows, srcImage.cols, srcImage.type() );

	//【3】設定源圖像和目標圖像上的三組點以計算仿射變換
	srcTriangle[0] = Point2f( 0,0 );
	srcTriangle[1] = Point2f( static_cast<float>(srcImage.cols - 1), 0 );
	srcTriangle[2] = Point2f( 0, static_cast<float>(srcImage.rows - 1 ));

	dstTriangle[0] = Point2f( static_cast<float>(srcImage.cols*0.0), static_cast<float>(srcImage.rows*0.33));
	dstTriangle[1] = Point2f( static_cast<float>(srcImage.cols*0.65), static_cast<float>(srcImage.rows*0.35));
	dstTriangle[2] = Point2f( static_cast<float>(srcImage.cols*0.15), static_cast<float>(srcImage.rows*0.6));

	//【4】求得仿射變換
	warpMat = getAffineTransform( srcTriangle, dstTriangle );

	//【5】對源圖像應用剛剛求得的仿射變換
	warpAffine( srcImage, dstImage_warp, warpMat, dstImage_warp.size() );

	//【6】對圖像進行縮放後再旋轉
	// 計算繞圖像中點順時針旋轉50度縮放因子為0.6的旋轉矩陣
	Point center = Point( dstImage_warp.cols/2, dstImage_warp.rows/2 );
	double angle = -50.0;
	double scale = 0.6;
	// 通過上面的旋轉細節訊息求得旋轉矩陣
	rotMat = getRotationMatrix2D( center, angle, scale );
	// 旋轉已縮放後的圖像
	warpAffine( dstImage_warp, dstImage_warp_rotate, rotMat, dstImage_warp.size() );


	//【7】顯示結果
	imshow( WINDOW_NAME1, srcImage );
	imshow( WINDOW_NAME2, dstImage_warp );
	imshow( WINDOW_NAME3, dstImage_warp_rotate );

	// 等待用戶按任意按鍵退出程序
	waitKey(0);

	return 0;
}


//-----------------------------------【ShowHelpText( )函數】----------------------------------  
//      描述：輸出一些說明訊息  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  

	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第67個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//輸出一些說明訊息  
	printf(   "\n\n\t\t歡迎來到仿射變換綜合範例程序.\n\n");  
	printf(  "\t\t鍵盤按鍵【ESC】- 退出程序\n"  );  
}  

