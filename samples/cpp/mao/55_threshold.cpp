#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f55
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1aOpenCV\u57fa\u672c\u95be\u503c\u64cd\u4f5c
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

//-----------------------------------\u3010\u5de8\u96c6\u5b9a\u7fa9\u90e8\u5206\u3011-------------------------------------------- 
//		\u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME "\u3010\u7a0b\u5f0f\u8996\u7a97\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;

//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
static void ShowHelpText( );//\u8f38\u51fa\u8aaa\u660e\u6587\u5b57
void on_Threshold( int, void* );//\u56de\u8abf\u51fd\u6578


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( )
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 1F"); 

	//\u30100\u3011\u986f\u793a\u6b61\u8fce\u548c\u8aaa\u660e\u6587\u5b57
	ShowHelpText( );

	//\u30101\u3011\u8b80\u5165\u6e90\u5716\u5f62
	g_srcImage = imread("1.jpg");
	if(!g_srcImage.data ) { printf("\u8b80\u53d6\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u7684\u5716\u5f62\u5b58\u5728~\uff01 \n"); return false; }  
	imshow("\u539f\u59cb\u5716",g_srcImage);

	//\u30102\u3011\u5b58\u7559\u4e00\u4efd\u539f\u5716\u7684\u7070\u5ea6\u5716
	cvtColor( g_srcImage, g_grayImage, CV_RGB2GRAY );

	//\u30103\u3011\u5efa\u7acb\u8996\u7a97\u4e26\u986f\u793a\u539f\u59cb\u5716
	namedWindow( WINDOW_NAME, CV_WINDOW_AUTOSIZE );

	//\u30104\u3011\u5efa\u7acb\u6ed1\u52d5\u689d\u4f86\u63a7\u5236\u95be\u503c
	createTrackbar( "\u6a21\u5f0f",
		WINDOW_NAME, &g_nThresholdType,
		4, on_Threshold );

	createTrackbar( "\u53c3\u6578\u503c",
		WINDOW_NAME, &g_nThresholdValue,
		255, on_Threshold );

	//\u30105\u3011\u521d\u59cb\u5316\u81ea\u5b9a\u7fa9\u7684\u95be\u503c\u56de\u8abf\u51fd\u6578
	on_Threshold( 0, 0 );

	// \u30106\u3011\u8f2a\u8a62\u7b49\u5f85\u7528\u6236\u6309\u9375\uff0c\u5982\u679cESC\u9375\u6309\u4e0b\u5247\u9000\u51fa\u7a0b\u5f0f
	while(1)
	{
		int key;
		key = waitKey( 20 );
		if( (char)key == 27 ){ break; }
	}

}

//-----------------------------------\u3010on_Threshold( )\u51fd\u6578\u3011------------------------------------
//		\u63cf\u8ff0\uff1a\u81ea\u5b9a\u7fa9\u7684\u95be\u503c\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------
void on_Threshold( int, void* )
{
	//\u4f7f\u7528\u95be\u503c\u51fd\u6578
	threshold(g_grayImage,g_dstImage,g_nThresholdValue,255,g_nThresholdType);

	//\u66f4\u65b0\u6548\u679c\u5716
	imshow( WINDOW_NAME, g_dstImage );
}

//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------  
//      \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c55\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
	printf(	"\n\t\u6b61\u8fce\u4f86\u5230\u3010\u57fa\u672c\u95be\u503c\u64cd\u4f5c\u3011\u7bc4\u4f8b\u7a0b\u5f0f~\n\n");  
	printf(	"\n\t\u6309\u9375\u64cd\u4f5c\u8aaa\u660e: \n\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u3010ESC\u3011- \u9000\u51fa\u7a0b\u5f0f\n"  
		"\t\t\u6372\u8ef8\u6a21\u5f0f0- \u4e8c\u9032\u5236\u95be\u503c\n"  
		"\t\t\u6372\u8ef8\u6a21\u5f0f1- \u53cd\u4e8c\u9032\u5236\u95be\u503c\n"  
		"\t\t\u6372\u8ef8\u6a21\u5f0f2- \u622a\u65b7\u95be\u503c\n"  
		"\t\t\u6372\u8ef8\u6a21\u5f0f3- \u53cd\u95be\u503c\u5316\u70ba0\n"  
		"\t\t\u6372\u8ef8\u6a21\u5f0f4- \u95be\u503c\u5316\u70ba0\n"  );  
}  
