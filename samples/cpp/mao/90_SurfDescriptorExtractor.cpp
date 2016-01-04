
#include <stdio.h>


//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/nonfree/nonfree.hpp>
#include<opencv2/legacy/legacy.hpp>
#include <iostream>
using namespace cv;
using namespace std;



//-----------------------------------【全局函數宣告部分】--------------------------------------
//		描述：全局函數的宣告
//-----------------------------------------------------------------------------------------------
static void ShowHelpText( );//輸出說明文字


//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始執行
//-----------------------------------------------------------------------------------------------
int main(  )
{
	//【0】改變console字體顏色
	system("color 1F"); 

	//【0】顯示歡迎和說明文字
	ShowHelpText( );

	//【1】載入素材圖
	Mat srcImage1 = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg",1);
//        Mat srcImage2 = imread("2.jpg",1);
	Mat srcImage2 = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/2.jpg",1);
	if( !srcImage1.data || !srcImage2.data )
	{ printf("讀取圖形錯誤，請確定目錄下是否有imread函數指定的圖形存在~！ \n"); return false; }  

	//【2】使用SURF算子檢測關鍵點
	int minHessian = 700;//SURF算法中的hessian閾值
	SurfFeatureDetector detector( minHessian );//定義一個SurfFeatureDetector（SURF） 特徵檢測類別對象  
	std::vector<KeyPoint> keyPoint1, keyPoints2;//vector模板類別，存放任意類別型的動態數組

	//【3】使用detect函數檢測出SURF特徵關鍵點，儲存在vector宿主中
	detector.detect( srcImage1, keyPoint1 );
	detector.detect( srcImage2, keyPoints2 );

	//【4】計算描述表（特徵向量）
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute( srcImage1, keyPoint1, descriptors1 );
	extractor.compute( srcImage2, keyPoints2, descriptors2 );

	//【5】使用BruteForce進行比對
	// 實例化一個比對器
	BruteForceMatcher< L2<float> > matcher;
	std::vector< DMatch > matches;
	//比對兩幅圖中的描述子（descriptors）
	matcher.match( descriptors1, descriptors2, matches );

	//【6】繪製從兩個圖像中比對出的關鍵點
	Mat imgMatches;
	drawMatches( srcImage1, keyPoint1, srcImage2, keyPoints2, matches, imgMatches );//進行繪製

	//【7】顯示效果圖
	imshow("比對圖", imgMatches );
	moveWindow("比對圖", 100,100 );

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
	printf("\n\n\t\t\t此為本書OpenCV2版的第90個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//輸出說明訊息  
	printf(  "\n\n\n\t歡迎來到【SURF特徵描述】範例程序\n\n");  
}  
