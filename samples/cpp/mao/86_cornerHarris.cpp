#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f86
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1aHarris\u89d2\u9ede\u6aa2\u6e2c
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;


//-----------------------------------\u3010\u5de8\u96c6\u5b9a\u7fa9\u90e8\u5206\u3011--------------------------------------------  
//  \u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6  
//------------------------------------------------------------------------------------------------  
#define WINDOW_NAME1 "\u3010\u7a0b\u5f0f\u8996\u7a971\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6  
#define WINDOW_NAME2 "\u3010\u7a0b\u5f0f\u8996\u7a972\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6  

//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_srcImage1,g_grayImage;
int thresh = 30; //\u73fe\u5728\u95be\u503c
int max_thresh = 175; //\u6700\u5927\u95be\u503c


//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
void on_CornerHarris( int, void* );//\u56de\u8abf\u51fd\u6578
static void ShowHelpText();

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 3F");  

	//\u30100\u3011\u986f\u793a\u8aaa\u660e\u6587\u5b57
	ShowHelpText();

	//\u30101\u3011\u8f09\u5165\u539f\u59cb\u5716\u4e26\u9032\u884c\u514b\u9686\u5132\u5b58
	g_srcImage = imread( "1.jpg", 1 );
	if(!g_srcImage.data ) { printf("\u8b80\u53d6\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u7684\u5716\u5f62\u5b58\u5728~\uff01 \n"); return false; }  
	imshow("\u539f\u59cb\u5716",g_srcImage);
	g_srcImage1=g_srcImage.clone( );

	//\u30102\u3011\u5b58\u7559\u4e00\u5f35\u7070\u5ea6\u5716
	cvtColor( g_srcImage1, g_grayImage, CV_BGR2GRAY );

	//\u30103\u3011\u5efa\u7acb\u8996\u7a97\u548c\u6372\u8ef8
	namedWindow( WINDOW_NAME1, CV_WINDOW_AUTOSIZE );
	createTrackbar( "\u95be\u503c: ", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris );

	//\u30104\u3011\u4f7f\u7528\u4e00\u6b21\u56de\u8abf\u51fd\u6578\uff0c\u9032\u884c\u521d\u59cb\u5316
	on_CornerHarris( 0, 0 );

	waitKey(0);
	return(0);
}

//-----------------------------------\u3010on_HoughLines( )\u51fd\u6578\u3011--------------------------------
//		\u63cf\u8ff0\uff1a\u56de\u8abf\u51fd\u6578
//----------------------------------------------------------------------------------------------

void on_CornerHarris( int, void* )
{
	//---------------------------\u30101\u3011\u5b9a\u7fa9\u4e00\u4e9b\u5c40\u90e8\u8b8a\u6578-----------------------------
	Mat dstImage;//\u76ee\u6a19\u5716
	Mat normImage;//\u6b78\u4e00\u5316\u5f8c\u7684\u5716
	Mat scaledImage;//\u7dda\u6027\u8b8a\u63db\u5f8c\u7684\u516b\u4f4d\u7121\u8868\u865f\u6574\u578b\u7684\u5716

	//---------------------------\u30102\u3011\u521d\u59cb\u5316---------------------------------------
	//\u7f6e\u96f6\u73fe\u5728\u9700\u8981\u986f\u793a\u7684\u5169\u5e45\u5716\uff0c\u5373\u6e05\u9664\u4e0a\u4e00\u6b21\u4f7f\u7528\u6b64\u51fd\u6578\u6642\u4ed6\u5011\u7684\u503c
	dstImage = Mat::zeros( g_srcImage.size(), CV_32FC1 );
	g_srcImage1=g_srcImage.clone( );

	//---------------------------\u30103\u3011\u6b63\u5f0f\u6aa2\u6e2c-------------------------------------
	//\u9032\u884c\u89d2\u9ede\u6aa2\u6e2c
	cornerHarris( g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT );

	// \u6b78\u4e00\u5316\u8207\u8f49\u63db
	normalize( dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
	convertScaleAbs( normImage, scaledImage );//\u5c07\u6b78\u4e00\u5316\u5f8c\u7684\u5716\u7dda\u6027\u8b8a\u63db\u62108\u4f4d\u7121\u8868\u865f\u6574\u578b 

	//---------------------------\u30104\u3011\u9032\u884c\u7e6a\u88fd-------------------------------------
	// \u5c07\u6aa2\u6e2c\u5230\u7684\uff0c\u4e14\u8868\u5408\u95be\u503c\u689d\u4ef6\u7684\u89d2\u9ede\u7e6a\u88fd\u51fa\u4f86
	for( int j = 0; j < normImage.rows ; j++ )
	{ for( int i = 0; i < normImage.cols; i++ )
	{
		if( (int) normImage.at<float>(j,i) > thresh+80 )
		{
			circle( g_srcImage1, Point( i, j ), 5,  Scalar(10,10,255), 2, 8, 0 );
			circle( scaledImage, Point( i, j ), 5,  Scalar(0,10,255), 2, 8, 0 );
		}
	}
	}
	//---------------------------\u30104\u3011\u986f\u793a\u6700\u7d42\u6548\u679c---------------------------------
	imshow( WINDOW_NAME1, g_srcImage1 );
	imshow( WINDOW_NAME2, scaledImage );

}

//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//		\u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c86\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf("\n\n\n\t\u3010\u6b61\u8fce\u4f86\u5230Harris\u89d2\u9ede\u6aa2\u6e2c\u7bc4\u4f8b\u7a0b\u5f0f~\u3011\n\n");  
	printf("\n\t\u8acb\u8abf\u6574\u6372\u8ef8\u89c0\u5bdf\u5716\u50cf\u6548\u679c~\n\n");
}
