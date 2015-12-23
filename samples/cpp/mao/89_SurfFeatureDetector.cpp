#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/89_SurfFeatureDetector.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序89
//		程序描述：SURF特徵點檢測範例
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <iostream>
using namespace cv;


//-----------------------------------【全局函數宣告部分】--------------------------------------
//          描述：全局函數的宣告
//-----------------------------------------------------------------------------------------------
static void ShowHelpText( );//輸出說明文字

//-----------------------------------【main( )函數】--------------------------------------------
//   描述：控制臺應用程序的入口函數，我們的程序從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//【0】改變console字體顏色    
	system("color 2F");    

	//【0】顯示說明文字  
	ShowHelpText( );  

	//【1】載入源圖形並顯示
	Mat srcImage1 = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", 1 );
	Mat srcImage2 = imread("2.jpg", 1 );
	if( !srcImage1.data || !srcImage2.data )//檢測是否讀取成功
	{ printf("讀取圖形錯誤，請確定目錄下是否有imread函數指定名稱的圖形存在~！ \n"); return false; } 
	imshow("原始圖1",srcImage1);
	moveWindow("原始圖1",100,100);

	imshow("原始圖2",srcImage2);
	moveWindow("原始圖2",1000,100);

	//【2】定義需要用到的變數和類別
	int minHessian = 400;//定義SURF中的hessian閾值特徵點檢測算子
	SurfFeatureDetector detector( minHessian );//定義一個SurfFeatureDetector（SURF） 特徵檢測類別對象
	std::vector<KeyPoint> keypoints_1, keypoints_2;//vector模板類別是能夠存放任意類別型的動態數組，能夠增加和壓縮資料

	//【3】使用detect函數檢測出SURF特徵關鍵點，儲存在vector宿主中
	detector.detect( srcImage1, keypoints_1 );
	detector.detect( srcImage2, keypoints_2 );

	//【4】繪製特徵關鍵點.
	Mat img_keypoints_1; Mat img_keypoints_2;
	drawKeypoints( srcImage1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
	drawKeypoints( srcImage2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
	//drawKeypoints( srcImage1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
	//drawKeypoints( srcImage2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

	//【5】顯示效果圖
	imshow("特徵點檢測效果圖1", img_keypoints_1 );
	moveWindow("特徵點檢測效果圖1", 1000,1000 );

	imshow("特徵點檢測效果圖2", img_keypoints_2 );
	moveWindow("特徵點檢測效果圖2", 100,700 );

	waitKey(0);
	return 0;
}


//-----------------------------------【ShowHelpText( )函數】----------------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{ 
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第89個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//輸出一些說明訊息  
	printf("\n\n\t歡迎來到【SURF特徵點檢測】範例程序\n\n");     
	printf( "\n\t按鍵操作說明: \n\n"     
		"\t\t鍵盤按鍵任意鍵- 退出程序\n\n"    );

}
