#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f88
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u4e9e\u50cf\u7d20\u7d1a\u89d2\u9ede\u6aa2\u6e2c
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;


//-----------------------------------\u3010\u5de8\u96c6\u5b9a\u7fa9\u90e8\u5206\u3011-------------------------------------------- 
//  \u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6 
//----------------------------------------------------------------------------------------------
#define WINDOW_NAME "\u3010\u4e9e\u50cf\u7d20\u7d1a\u89d2\u9ede\u6aa2\u6e2c\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//          \u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_grayImage;
int g_maxCornerNumber = 33;
int g_maxTrackbarNumber = 500;
RNG g_rng(12345);//\u521d\u59cb\u5316\u96a8\u6a5f\u6578\u7522\u751f\u5668


//-----------------------------\u3010on_GoodFeaturesToTrack( )\u51fd\u6578\u3011----------------------------
//          \u63cf\u8ff0\uff1a\u97ff\u61c9\u6ed1\u52d5\u689d\u79fb\u52d5\u8a0a\u606f\u7684\u56de\u8abf\u51fd\u6578
//----------------------------------------------------------------------------------------------
void on_GoodFeaturesToTrack( int, void* )
{
	//\u30101\u3011\u5c0d\u8b8a\u6578\u5c0f\u4e8e\u7b49\u4e8e1\u6642\u7684\u8655\u7406
	if( g_maxCornerNumber <= 1 ) { g_maxCornerNumber = 1; }

	//\u30102\u3011Shi-Tomasi\u7b97\u6cd5\uff08goodFeaturesToTrack\u51fd\u6578\uff09\u7684\u53c3\u6578\u6e96\u5099
	vector<Point2f> corners;
	double qualityLevel = 0.01;//\u89d2\u9ede\u6aa2\u6e2c\u53ef\u63a5\u53d7\u7684\u6700\u5c0f\u7279\u5f81\u503c
	double minDistance = 10;//\u89d2\u9ede\u4e4b\u9593\u7684\u6700\u5c0f\u8ddd\u96e2
	int blockSize = 3;//\u8a08\u7b97\u5c0e\u6578\u81ea\u76f8\u95dc\u77e9\u9663\u6642\u6307\u5b9a\u7684\u9130\u57df\u8303\u570d
	double k = 0.04;//\u6b0a\u91cd\u7cfb\u6578
	Mat copy = g_srcImage.clone();	//\u5fa9\u5236\u6e90\u5716\u50cf\u5230\u4e00\u500b\u81e8\u6642\u8b8a\u6578\u4e2d\uff0c\u4f5c\u70ba\u611f\u8208\u8da3\u5340\u57df

	//\u30103\u3011\u9032\u884cShi-Tomasi\u89d2\u9ede\u6aa2\u6e2c
	goodFeaturesToTrack( g_grayImage,//\u8f38\u5165\u5716\u50cf
		corners,//\u6aa2\u6e2c\u5230\u7684\u89d2\u9ede\u7684\u8f38\u51fa\u5411\u91cf
		g_maxCornerNumber,//\u89d2\u9ede\u7684\u6700\u5927\u6578\u91cf
		qualityLevel,//\u89d2\u9ede\u6aa2\u6e2c\u53ef\u63a5\u53d7\u7684\u6700\u5c0f\u7279\u5f81\u503c
		minDistance,//\u89d2\u9ede\u4e4b\u9593\u7684\u6700\u5c0f\u8ddd\u96e2
		Mat(),//\u611f\u8208\u8da3\u5340\u57df
		blockSize,//\u8a08\u7b97\u5c0e\u6578\u81ea\u76f8\u95dc\u77e9\u9663\u6642\u6307\u5b9a\u7684\u9130\u57df\u8303\u570d
		false,//\u4e0d\u4f7f\u7528Harris\u89d2\u9ede\u6aa2\u6e2c
		k );//\u6b0a\u91cd\u7cfb\u6578

	//\u30104\u3011\u8f38\u51fa\u6587\u5b57\u8a0a\u606f
	cout<<"\n\t>-------------\u6b64\u6b21\u6aa2\u6e2c\u5230\u7684\u89d2\u9ede\u6578\u91cf\u70ba\uff1a"<<corners.size()<<endl;

	//\u30105\u3011\u7e6a\u88fd\u6aa2\u6e2c\u5230\u7684\u89d2\u9ede
	int r = 4;
	for( unsigned int i = 0; i < corners.size(); i++ )
	{ 
		//\u4ee5\u96a8\u6a5f\u7684\u984f\u8272\u7e6a\u88fd\u51fa\u89d2\u9ede
		circle( copy, corners[i], r, Scalar(g_rng.uniform(0,255), g_rng.uniform(0,255),
			g_rng.uniform(0,255)), -1, 8, 0 ); 
	}

	//\u30106\u3011\u986f\u793a\uff08\u66f4\u65b0\uff09\u8996\u7a97
	imshow( WINDOW_NAME, copy );

	//\u30107\u3011\u4e9e\u50cf\u7d20\u89d2\u9ede\u6aa2\u6e2c\u7684\u53c3\u6578\u8a2d\u5b9a
	Size winSize = Size( 5, 5 );
	Size zeroZone = Size( -1, -1 );
	TermCriteria criteria = TermCriteria( CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001 );

	//\u30108\u3011\u8a08\u7b97\u51fa\u4e9e\u50cf\u7d20\u89d2\u9ede\u4f4d\u7f6e
	cornerSubPix( g_grayImage, corners, winSize, zeroZone, criteria );

	//\u30109\u3011\u8f38\u51fa\u89d2\u9ede\u8a0a\u606f
	for( int i = 0; i < corners.size(); i++ )
	{ cout<<" \t>>\u7cbe\u78ba\u89d2\u9ede\u5ea7\u6a19["<<i<<"]  ("<<corners[i].x<<","<<corners[i].y<<")"<<endl; }


}


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
static void ShowHelpText( )
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c88\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf("\n\t\u6b61\u8fce\u4f86\u5230\u3010\u4e9e\u50cf\u7d20\u7d1a\u89d2\u9ede\u6aa2\u6e2c\u3011\u7bc4\u4f8b\u7a0b\u5e8f\n\n"); 
	printf("\n\t\u8acb\u8abf\u6574\u6ed1\u52d5\u689d\u89c0\u5bdf\u5716\u50cf\u6548\u679c\n\n");

}


//--------------------------------------\u3010main( )\u51fd\u6578\u3011-----------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main(  )
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 2F"); 

	//\u30100\u3011\u986f\u793a\u8aaa\u660e\u6587\u5b57
	ShowHelpText();

	//\u30101\u3011\u8f09\u5165\u6e90\u5716\u50cf\u4e26\u5c07\u5176\u8f49\u63db\u70ba\u7070\u5ea6\u5716
	g_srcImage = imread("1.jpg", 1 );
	cvtColor( g_srcImage, g_grayImage, CV_BGR2GRAY );

	//\u30102\u3011\u5efa\u7acb\u8996\u7a97\u548c\u6ed1\u52d5\u689d\uff0c\u4e26\u9032\u884c\u986f\u793a\u548c\u56de\u8abf\u51fd\u6578\u521d\u59cb\u5316
	namedWindow( WINDOW_NAME, CV_WINDOW_AUTOSIZE );
	createTrackbar( "\u6700\u5927\u89d2\u9ede\u6578", WINDOW_NAME, &g_maxCornerNumber, g_maxTrackbarNumber, on_GoodFeaturesToTrack );
	imshow( WINDOW_NAME, g_srcImage );
	on_GoodFeaturesToTrack( 0, 0 );

	waitKey(0);
	return(0);
}
