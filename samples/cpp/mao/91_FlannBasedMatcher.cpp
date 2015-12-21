#include <stdio.h>
//:read /home/peter/mao/91_FlannBasedMatcher.cpp
//--------------------------------------【程式說明】-------------------------------------------
//		程式說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程式91
//		程式描述：使用FLANN進行特徵點比對
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程式所使用的頭文件和命名空間
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
//      描述：全局函數宣告    
//----------------------------------------------------------------------------------------------- 
static void ShowHelpText( );


//-----------------------------------【main( )函數】--------------------------------------------
//   描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//【0】改變console字體顏色    
	system("color 4F");    

	//【0】顯示說明文字  
	ShowHelpText();  

	//【1】載入源圖形
	Mat img_1 = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", 1 );
	Mat img_2 = imread( "2.jpg", 1 );
	if( !img_1.data || !img_2.data ) { printf("讀取圖形image0錯誤~！ \n"); return false; }  

	//【2】利用SURF檢測器檢測的關鍵點
	int minHessian = 300;
	SURF detector( minHessian );
	std::vector<KeyPoint> keypoints_1, keypoints_2;
	detector.detect( img_1, keypoints_1 );
	detector.detect( img_2, keypoints_2 );

	//【3】計算描述表（特徵向量）
	SURF extractor;
	Mat descriptors_1, descriptors_2;
	extractor.compute( img_1, keypoints_1, descriptors_1 );
	extractor.compute( img_2, keypoints_2, descriptors_2 );

	//【4】采用FLANN算法比對描述表向量
	FlannBasedMatcher matcher;
	std::vector< DMatch > matches;
	matcher.match( descriptors_1, descriptors_2, matches );
	double max_dist = 0; double min_dist = 100;

	//【5】快速計算關鍵點之間的最大和最小距離
	for( int i = 0; i < descriptors_1.rows; i++ )
	{
		double dist = matches[i].distance;
		if( dist < min_dist ) min_dist = dist;
		if( dist > max_dist ) max_dist = dist;
	}
	//輸出距離訊息
	printf("> 最大距離（Max dist） : %f \n", max_dist );
	printf("> 最小距離（Min dist） : %f \n", min_dist );

	//【6】存下表合條件的比對結果（即其距離小于2* min_dist的），使用radiusMatch同樣可行
	std::vector< DMatch > good_matches;
	for( int i = 0; i < descriptors_1.rows; i++ )
	{ 
		if( matches[i].distance < 2*min_dist )
		{ good_matches.push_back( matches[i]); }
	}

	//【7】繪製出表合條件的比對點
	Mat img_matches;
	drawMatches( img_1, keypoints_1, img_2, keypoints_2,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

	//【8】輸出相關比對點訊息
	for( int i = 0; i < good_matches.size(); i++ )
	{ printf( ">表合條件的比對點 [%d] 特徵點1: %d  -- 特徵點2: %d  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx ); }

	//【9】顯示效果圖
	imshow( "比對效果圖", img_matches );

	//按任意鍵退出程式
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
	printf("\n\n\t\t\t此為本書OpenCV2版的第91個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//輸出一些說明訊息  
	printf("\n\t歡迎來到【FLNN特徵比對】範例程式\n\n");    
	printf( "\n\n\t按鍵操作說明: \n\n"     
		"\t\t鍵盤按鍵任意鍵- 退出程式\n\n" );

}
