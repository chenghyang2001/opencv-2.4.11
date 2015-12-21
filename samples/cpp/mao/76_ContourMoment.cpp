#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f76
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u67e5\u8a62\u548c\u7e6a\u88fd\u5716\u5f62\u8f2a\u5ed3\u77e9
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
//		\u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "\u3010\u539f\u59cb\u5716\u3011"					//\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 
#define WINDOW_NAME2 "\u3010\u5716\u50cf\u8f2a\u5ed3\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat g_srcImage; Mat g_grayImage;
int g_nThresh = 100;
int g_nMaxThresh = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;

//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
void on_ThreshChange(int, void* );
static void ShowHelpText( );

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 71"); 

	ShowHelpText();
	// \u8b80\u5165\u539f\u5716\u50cf, \u8fd4\u56de3\u901a\u9053\u5716\u50cf\u8cc7\u6599
	g_srcImage = imread( "1.jpg", 1 );

	// \u628a\u539f\u5716\u50cf\u8f49\u5316\u6210\u7070\u5ea6\u5716\u50cf\u4e26\u9032\u884c\u5e73\u6ed1
	cvtColor( g_srcImage, g_grayImage, CV_BGR2GRAY );
	blur( g_grayImage, g_grayImage, Size(3,3) );

	// \u5efa\u7acb\u65b0\u8996\u7a97
	namedWindow( WINDOW_NAME1, CV_WINDOW_AUTOSIZE );
	imshow( WINDOW_NAME1, g_srcImage );

	//\u5efa\u7acb\u6372\u8ef8\u4e26\u9032\u884c\u521d\u59cb\u5316
	createTrackbar( " \u95be\u503c", WINDOW_NAME1, &g_nThresh, g_nMaxThresh, on_ThreshChange );
	on_ThreshChange( 0, 0 );

	waitKey(0);
	return(0);
}

//-----------------------------------\u3010on_ThreshChange( )\u51fd\u6578\u3011-------------------------------
//		\u63cf\u8ff0\uff1a\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------
void on_ThreshChange(int, void* )
{
	// \u4f7f\u7528Canndy\u6aa2\u6e2c\u908a\u7de3
	Canny( g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh*2, 3 );

	// \u627e\u5230\u8f2a\u5ed3
	findContours( g_cannyMat_output, g_vContours, g_vHierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	// \u8a08\u7b97\u77e9
	vector<Moments> mu(g_vContours.size() );
	for(unsigned int i = 0; i < g_vContours.size(); i++ )
	{ mu[i] = moments( g_vContours[i], false ); }

	//  \u8a08\u7b97\u4e2d\u5fc3\u77e9
	vector<Point2f> mc( g_vContours.size() );
	for( unsigned int i = 0; i < g_vContours.size(); i++ )
	{ mc[i] = Point2f( static_cast<float>(mu[i].m10/mu[i].m00), static_cast<float>(mu[i].m01/mu[i].m00 )); }

	// \u7e6a\u88fd\u8f2a\u5ed3
	Mat drawing = Mat::zeros( g_cannyMat_output.size(), CV_8UC3 );
	for( unsigned int i = 0; i< g_vContours.size(); i++ )
	{
		Scalar color = Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//\u96a8\u6a5f\u7522\u751f\u984f\u8272\u503c
		drawContours( drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point() );//\u7e6a\u88fd\u5916\u5c64\u548c\u5167\u5c64\u8f2a\u5ed3
		circle( drawing, mc[i], 4, color, -1, 8, 0 );;//\u7e6a\u88fd\u5713
	}

	// \u986f\u793a\u5230\u8996\u7a97\u4e2d
	namedWindow( WINDOW_NAME2, CV_WINDOW_AUTOSIZE );
	imshow( WINDOW_NAME2, drawing );

	// \u900f\u904em00\u8a08\u7b97\u8f2a\u5ed3\u9762\u7a4d\u4e26\u4e14\u548cOpenCV\u51fd\u6578\u6bd4\u8f03
	printf("\t \u8f38\u51fa\u5167\u5bb9: \u9762\u7a4d\u548c\u8f2a\u5ed3\u9577\u5ea6\n");
	for(unsigned  int i = 0; i< g_vContours.size(); i++ )
	{
		printf(" >\u900f\u904em00\u8a08\u7b97\u51fa\u8f2a\u5ed3[%d]\u7684\u9762\u7a4d: (M_00) = %.2f \n OpenCV\u51fd\u6578\u8a08\u7b97\u51fa\u7684\u9762\u7a4d=%.2f , \u9577\u5ea6: %.2f \n\n", i, mu[i].m00, contourArea(g_vContours[i]), arcLength( g_vContours[i], true ) );
		Scalar color = Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );
		drawContours( drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point() );
		circle( drawing, mc[i], 4, color, -1, 8, 0 );
	}
}


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011-----------------------------
//		 \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c76\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}
