#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f83
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1a\u53cd\u5411\u6295\u5f71\u7bc4\u4f8b\u7a0b\u5f0f
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6a94\u6848\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6a94\u6848\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;


//-----------------------------------\u3010\u5de8\u96c6\u5b9a\u7fa9\u90e8\u5206\u3011-------------------------------------------- 
//  \u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "\u3010\u539f\u59cb\u5716\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//          \u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat g_srcImage; Mat g_hsvImage; Mat g_hueImage;
int g_bins = 30;//\u76f4\u689d\u5716\u7d44\u8ddd

//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//          \u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
static void ShowHelpText();
void on_BinChange(int, void* );

//--------------------------------------\u3010main( )\u51fd\u6578\u3011-----------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( )
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 6F"); 

	//\u30100\u3011\u986f\u793a\u8aaa\u660e\u6587\u5b57
	ShowHelpText();

	//\u30101\u3011\u8b80\u53d6\u6e90\u5716\u50cf\uff0c\u4e26\u8f49\u63db\u5230 HSV \u7a7a\u9593
	g_srcImage = imread( "1.jpg", 1 );
	if(!g_srcImage.data ) { printf("\u8b80\u53d6\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u5716\u5f62\u5b58\u5728~\uff01 \n"); return false; } 
	cvtColor( g_srcImage, g_hsvImage, CV_BGR2HSV );

	//\u30102\u3011\u5206\u96e2 Hue \u8272\u8abf\u901a\u9053
	g_hueImage.create( g_hsvImage.size(), g_hsvImage.depth() );
	int ch[ ] = { 0, 0 };
	mixChannels( &g_hsvImage, 1, &g_hueImage, 1, ch, 1 );

	//\u30103\u3011\u5efa\u7acb Trackbar \u4f86\u8f38\u5165bin\u7684\u6578\u76ee
	namedWindow( WINDOW_NAME1 , CV_WINDOW_AUTOSIZE );
	createTrackbar("\u8272\u8abf\u7d44\u8ddd ", WINDOW_NAME1 , &g_bins, 180, on_BinChange );
	on_BinChange(0, 0);//\u9032\u884c\u4e00\u6b21\u521d\u59cb\u5316

	//\u30104\u3011\u986f\u793a\u6548\u679c\u5716
	imshow( WINDOW_NAME1 , g_srcImage );

	// \u7b49\u5f85\u7528\u6236\u6309\u9375
	waitKey(0);
	return 0;
}


//-----------------------------------\u3010on_HoughLines( )\u51fd\u6578\u3011--------------------------------
//          \u63cf\u8ff0\uff1a\u97ff\u61c9\u6ed1\u52d5\u689d\u79fb\u52d5\u8a0a\u606f\u7684\u56de\u8abf\u51fd\u6578
//---------------------------------------------------------------------------------------------
void on_BinChange(int, void* )
{
	//\u30101\u3011\u53c3\u6578\u6e96\u5099
	MatND hist;
	int histSize = MAX( g_bins, 2 );
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };

	//\u30102\u3011\u8a08\u7b97\u76f4\u689d\u5716\u4e26\u6b78\u4e00\u5316
	calcHist( &g_hueImage, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false );
	normalize( hist, hist, 0, 255, NORM_MINMAX, -1, Mat() );

	//\u30103\u3011\u8a08\u7b97\u53cd\u5411\u6295\u5f71
	MatND backproj;
	calcBackProject( &g_hueImage, 1, 0, hist, backproj, &ranges, 1, true );

	//\u30104\u3011\u986f\u793a\u53cd\u5411\u6295\u5f71
	imshow( "\u53cd\u5411\u6295\u5f71\u5716", backproj );

	//\u30105\u3011\u7e6a\u88fd\u76f4\u689d\u5716\u7684\u53c3\u6578\u6e96\u5099
	int w = 400; int h = 400;
	int bin_w = cvRound( (double) w / histSize );
	Mat histImg = Mat::zeros( w, h, CV_8UC3 );

	//\u30106\u3011\u7e6a\u88fd\u76f4\u689d\u5716
	for( int i = 0; i < g_bins; i ++ )
	{ rectangle( histImg, Point( i*bin_w, h ), Point( (i+1)*bin_w, h - cvRound( hist.at<float>(i)*h/255.0 ) ), Scalar( 100, 123, 255 ), -1 ); }

	//\u30107\u3011\u986f\u793a\u76f4\u689d\u5716\u8996\u7a97
	imshow( "\u76f4\u689d\u5716", histImg );
}


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c83\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf("\n\n\t\u6b61\u8fce\u4f86\u5230\u3010\u53cd\u5411\u6295\u5f71\u3011\u7bc4\u4f8b\u7a0b\u5f0f\n\n"); 
	printf("\n\t\u8acb\u8abf\u6574\u6ed1\u52d5\u689d\u89c0\u5bdf\u5716\u50cf\u6548\u679c\n\n");

}
