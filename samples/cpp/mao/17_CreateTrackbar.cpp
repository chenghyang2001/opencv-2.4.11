#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f17
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u70ba\u7a0b\u5e8f\u754c\u9762\u65b0\u589e\u6ed1\u52d5\u689d
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e746\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------


//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011-------------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//-------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
using namespace cv;

//-----------------------------------\u3010\u5de8\u96c6\u5b9a\u7fa9\u90e8\u5206\u3011-------------------------------------------- 
//  \u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME "\u3010\u6ed1\u52d5\u689d\u7684\u5efa\u7acb&\u7dda\u6027\u6df7\u5408\u7bc4\u4f8b\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
const int g_nMaxAlphaValue = 100;//Alpha\u503c\u7684\u6700\u5927\u503c
int g_nAlphaValueSlider;//\u6ed1\u52d5\u689d\u5c0d\u61c9\u7684\u8b8a\u6578
double g_dAlphaValue;
double g_dBetaValue;

//\u5ba3\u544a\u5b58\u5132\u5716\u50cf\u7684\u8b8a\u6578
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;


//-----------------------------------\u3010on_Trackbar( )\u51fd\u6578\u3011--------------------------------
//		\u63cf\u8ff0\uff1a\u97ff\u61c9\u6ed1\u52d5\u689d\u7684\u56de\u8abf\u51fd\u6578
//------------------------------------------------------------------------------------------
void on_Trackbar( int, void* )
{
	//\u6c42\u51fa\u73fe\u5728alpha\u503c\u76f8\u5c0d\u65bc\u6700\u5927\u503c\u7684\u6bd4\u4f8b
	g_dAlphaValue = (double) g_nAlphaValueSlider/g_nMaxAlphaValue ;
	//\u5247beta\u503c\u70ba1\u6e1b\u53bbalpha\u503c
	g_dBetaValue = ( 1.0 - g_dAlphaValue );

	//\u6839\u64daalpha\u548cbeta\u503c\u9032\u884c\u7dda\u6027\u6df7\u5408
	addWeighted( g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

	//\u986f\u793a\u6548\u679c\u5716
	imshow( WINDOW_NAME, g_dstImage );
}


//-----------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u8f38\u51fa\u8aaa\u660e\u8a0a\u606f
//-------------------------------------------------------------------------------------------------
//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//		\u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c17\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


//--------------------------------------\u3010main( )\u51fd\u6578\u3011-----------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{

	//\u986f\u793a\u8aaa\u660e\u8a0a\u606f
	ShowHelpText();

	//\u52a0\u8f09\u5716\u50cf (\u5169\u5716\u50cf\u7684\u5c3a\u5bf8\u9700\u76f8\u540c)
	g_srcImage1 = imread("1.jpg");
	g_srcImage2 = imread("2.jpg");
	if( !g_srcImage1.data ) { printf("\u8b80\u53d6\u7b2c\u4e00\u5e45\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u5716\u5f62\u5b58\u5728~\uff01 \n"); return -1; }
	if( !g_srcImage2.data ) { printf("\u8b80\u53d6\u7b2c\u4e8c\u5e45\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u5716\u5f62\u5b58\u5728~\uff01\n"); return -1; }

	//\u8a2d\u5b9a\u6ed1\u52d5\u689d\u521d\u503c\u70ba70
	g_nAlphaValueSlider = 70;

	//\u5efa\u7acb\u8996\u7a97
	namedWindow(WINDOW_NAME, 1);

	//\u5728\u5efa\u7acb\u7684\u8996\u7a97\u4e2d\u5efa\u7acb\u4e00\u500b\u6ed1\u52d5\u689d\u63a7\u5236\u9805
	char TrackbarName[50];
	sprintf( TrackbarName, "\u900f\u660e\u503c %d", g_nMaxAlphaValue );

	createTrackbar( TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar );

	//\u7d50\u679c\u5728\u56de\u8abf\u51fd\u6578\u4e2d\u986f\u793a
	on_Trackbar( g_nAlphaValueSlider, 0 );

	//\u6309\u4efb\u610f\u9375\u9000\u51fa
	waitKey(0);

	return 0;
}
