#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f84
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1a\u7bc4\u672c\u6bd4\u5c0d\u7bc4\u4f8b
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6a94\u6848\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6a94\u6848\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;


//-----------------------------------\u3010\u5de8\u96c6\u5b9a\u7fa9\u90e8\u5206\u3011-------------------------------------------- 
//  \u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "\u3010\u539f\u59cb\u5716\u5f62\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 
#define WINDOW_NAME2 "\u3010\u6bd4\u5c0d\u8996\u7a97\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 

//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011------------------------------------
//          \u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat g_srcImage; Mat g_templateImage; Mat g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;

//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//          \u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
void on_Matching( int, void* );
static void ShowHelpText( );


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main(  )
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 1F"); 

	//\u30100\u3011\u986f\u793a\u8aaa\u660e\u6587\u5b57
	ShowHelpText();

	//\u30101\u3011\u8f09\u5165\u539f\u5f71\u50cf\u548c\u7bc4\u672c\u584a
	g_srcImage = imread( "1.jpg", 1 );
	g_templateImage = imread( "2.jpg", 1 );

	//\u30102\u3011\u5efa\u7acb\u8996\u7a97
	namedWindow( WINDOW_NAME1, CV_WINDOW_AUTOSIZE );
	namedWindow( WINDOW_NAME2, CV_WINDOW_AUTOSIZE );

	//\u30103\u3011\u5efa\u7acb\u6ed1\u52d5\u689d\u4e26\u9032\u884c\u4e00\u6b21\u521d\u59cb\u5316
	createTrackbar( "\u65b9\u6cd5", WINDOW_NAME1, &g_nMatchMethod, g_nMaxTrackbarNum, on_Matching );
	on_Matching( 0, 0 );

	waitKey(0);
	return 0;

}

//-----------------------------------\u3010on_Matching( )\u51fd\u6578\u3011--------------------------------
//          \u63cf\u8ff0\uff1a\u56de\u8abf\u51fd\u6578
//-------------------------------------------------------------------------------------------
void on_Matching( int, void* )
{
	//\u30101\u3011\u7d66\u5c40\u90e8\u8b8a\u6578\u521d\u59cb\u5316
	Mat srcImage;
	g_srcImage.copyTo( srcImage );

	//\u30102\u3011\u521d\u59cb\u5316\u7528\u4e8e\u7d50\u679c\u8f38\u51fa\u7684\u77e9\u9663
	int resultImage_cols =  g_srcImage.cols - g_templateImage.cols + 1;
	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	g_resultImage.create( resultImage_cols, resultImage_rows, CV_32FC1 );

	//\u30103\u3011\u9032\u884c\u6bd4\u5c0d\u548c\u6a19\u6e96\u5316
	matchTemplate( g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod );
	normalize( g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat() );

	//\u30104\u3011\u901a\u904e\u51fd\u6578 minMaxLoc \u5b9a\u4f4d\u6700\u6bd4\u5c0d\u7684\u4f4d\u7f6e
	double minValue; double maxValue; Point minLocation; Point maxLocation;
	Point matchLocation;
	minMaxLoc( g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat() );

	//\u30105\u3011\u5c0d\u65bc\u65b9\u6cd5 SQDIFF \u548c SQDIFF_NORMED, \u8d8a\u5c0f\u7684\u6578\u503c\u6709\u8457\u66f4\u9ad8\u7684\u6bd4\u5c0d\u7d50\u679c. \u800c\u5176\u4f59\u7684\u65b9\u6cd5, \u6578\u503c\u8d8a\u5927\u6bd4\u5c0d\u6548\u679c\u8d8a\u597d
	if( g_nMatchMethod  == CV_TM_SQDIFF || g_nMatchMethod == CV_TM_SQDIFF_NORMED )
	{ matchLocation = minLocation; }
	else
	{ matchLocation = maxLocation; }

	//\u30106\u3011\u7e6a\u88fd\u51fa\u77e9\u5f62\uff0c\u4e26\u986f\u793a\u6700\u7d42\u7d50\u679c
	rectangle( srcImage, matchLocation, Point( matchLocation.x + g_templateImage.cols , matchLocation.y + g_templateImage.rows ), Scalar(0,0,255), 2, 8, 0 );
	rectangle( g_resultImage, matchLocation, Point( matchLocation.x + g_templateImage.cols , matchLocation.y + g_templateImage.rows ), Scalar(0,0,255), 2, 8, 0 );

	imshow( WINDOW_NAME1, srcImage );
	imshow( WINDOW_NAME2, g_resultImage );

}



//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c84\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf("\t\u6b61\u8fce\u4f86\u5230\u3010\u7bc4\u672c\u6bd4\u5c0d\u3011\u7bc4\u4f8b\u7a0b\u5f0f~\n"); 
	printf("\n\n\t\u8acb\u8abf\u6574\u6ed1\u52d5\u689d\u89c0\u5bdf\u5f71\u50cf\u6548\u679c\n\n");
	printf(  "\n\t\u6ed1\u52d5\u689d\u5c0d\u61c9\u7684\u65b9\u6cd5\u6578\u503c\u8aaa\u660e: \n\n" 
		"\t\t\u65b9\u6cd5\u30100\u3011- \u5e73\u65b9\u5dee\u6bd4\u5c0d\u6cd5(SQDIFF)\n" 
		"\t\t\u65b9\u6cd5\u30101\u3011- \u6b63\u898f\u5316\u5e73\u65b9\u5dee\u6bd4\u5c0d\u6cd5(SQDIFF NORMED)\n" 
		"\t\t\u65b9\u6cd5\u30102\u3011- \u76f8\u95dc\u6bd4\u5c0d\u6cd5(TM CCORR)\n" 
		"\t\t\u65b9\u6cd5\u30103\u3011- \u6b63\u898f\u5316\u76f8\u95dc\u6bd4\u5c0d\u6cd5(TM CCORR NORMED)\n" 
		"\t\t\u65b9\u6cd5\u30104\u3011- \u76f8\u95dc\u7cfb\u6578\u6bd4\u5c0d\u6cd5(TM COEFF)\n" 
		"\t\t\u65b9\u6cd5\u30105\u3011- \u6b63\u898f\u5316\u76f8\u95dc\u7cfb\u6578\u6bd4\u5c0d\u6cd5(TM COEFF NORMED)\n" );  
}
