#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f75
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u5efa\u7acb\u8f2a\u5ed3\u908a\u754c\u6846
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

//-----------------------------------\u3010\u547d\u540d\u7a7a\u9593\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//          \u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u547d\u540d\u7a7a\u9593
//-----------------------------------------------------------------------------------------------
using namespace cv;

//-----------------------------------\u3010\u5de8\u96c6\u5b9a\u7fa9\u90e8\u5206\u3011-------------------------------------------- 
//  \u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "\u3010\u539f\u59cb\u5716\u8996\u7a97\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 
#define WINDOW_NAME2 "\u3010\u6548\u679c\u5716\u8996\u7a97\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 

//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//  \u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 50;//\u95be\u503c
int g_nMaxThresh = 255;//\u95be\u503c\u6700\u5927\u503c
RNG g_rng(12345);//\u96a8\u6a5f\u6578\u7522\u751f\u5668

//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//   \u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
void on_ContoursChange(int, void* );
static void ShowHelpText( );

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//   \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( )
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 1F"); 

	//\u30100\u3011\u986f\u793a\u6b61\u8fce\u548c\u8aaa\u660e\u6587\u5b57
	ShowHelpText( );

	//\u30101\u3011\u8f09\u51653\u901a\u9053\u7684\u539f\u5716\u50cf
	g_srcImage = imread( "1.jpg", 1 );
	if(!g_srcImage.data ) { printf("\u8b80\u53d6\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u7684\u5716\u5f62\u5b58\u5728~\uff01 \n"); return false; }  

	//\u30102\u3011\u5f97\u5230\u539f\u5716\u7684\u7070\u5ea6\u5716\u50cf\u4e26\u9032\u884c\u5e73\u6ed1
	cvtColor( g_srcImage, g_grayImage, CV_BGR2GRAY );
	blur( g_grayImage, g_grayImage, Size(3,3) );

	//\u30103\u3011\u5efa\u7acb\u539f\u59cb\u5716\u8996\u7a97\u4e26\u986f\u793a
	namedWindow( WINDOW_NAME1, CV_WINDOW_AUTOSIZE );
	imshow( WINDOW_NAME1, g_srcImage );

	//\u30104\u3011\u8a2d\u5b9a\u6372\u8ef8\u4e26\u4f7f\u7528\u4e00\u6b21\u56de\u8abf\u51fd\u6578
	createTrackbar( " \u95be\u503c:", WINDOW_NAME1, &g_nThresh, g_nMaxThresh, on_ContoursChange );
	on_ContoursChange( 0, 0 );

	waitKey(0);

	return(0);
}

//----------------------------\u3010on_ContoursChange( )\u51fd\u6578\u3011---------------------------------
//      \u63cf\u8ff0\uff1a\u56de\u8abf\u51fd\u6578
//-------------------------------------------------------------------------------------------------  
void on_ContoursChange(int, void* )
{
#if 0
	//\u5b9a\u7fa9\u4e00\u4e9b\u53c3\u6578
	Mat threshold_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	// \u4f7f\u7528Threshold\u6aa2\u6e2c\u908a\u7de3
	threshold( g_grayImage, threshold_output, g_nThresh, 255, THRESH_BINARY );

	// \u627e\u51fa\u8f2a\u5ed3
	findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	// \u591a\u908a\u5f62\u903c\u8fd1\u8f2a\u5ed3 + \u53d6\u5f97\u77e9\u5f62\u548c\u5713\u5f62\u908a\u754c\u6846
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );
	vector<Point2f>center( contours.size() );
	vector<float>radius( contours.size() );

	//\u4e00\u500b\u5faa\u74b0\uff0c\u700f\u89bd\u6240\u6709\u90e8\u5206\uff0c\u9032\u884c\u672c\u7a0b\u5e8f\u6700\u6838\u5fc3\u7684\u64cd\u4f5c
	for( unsigned int i = 0; i < contours.size(); i++ )
	{ 
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );//\u7528\u6307\u5b9a\u7cbe\u5ea6\u903c\u8fd1\u591a\u908a\u5f62\u66f2\u7dda 
		boundRect[i] = boundingRect( Mat(contours_poly[i]) );//\u8a08\u7b97\u9ede\u96c6\u7684\u6700\u5916\u9762\uff08up-right\uff09\u77e9\u5f62\u908a\u754c
		minEnclosingCircle( contours_poly[i], center[i], radius[i] );//\u5c0d\u7d66\u5b9a\u7684 2D\u9ede\u96c6\uff0c\u5c0b\u627e\u6700\u5c0f\u9762\u7a4d\u7684\u5305\u570d\u5713\u5f62 
	}

	// \u7e6a\u88fd\u591a\u908a\u5f62\u8f2a\u5ed3 + \u5305\u570d\u7684\u77e9\u5f62\u6846 + \u5713\u5f62\u6846
	Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
	for( int unsigned i = 0; i<contours.size( ); i++ )
	{
		Scalar color = Scalar( g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255) );//\u96a8\u6a5f\u8a2d\u5b9a\u984f\u8272
		drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );//\u7e6a\u88fd\u8f2a\u5ed3
		rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );//\u7e6a\u88fd\u77e9\u5f62
		circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );//\u7e6a\u88fd\u5713
	}

	// \u986f\u793a\u6548\u679c\u5716\u8996\u7a97
	namedWindow( WINDOW_NAME2, CV_WINDOW_AUTOSIZE );
	imshow( WINDOW_NAME2, drawing );
#endif 
}

//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------  
//      \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c75\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
	printf("\n\n\n\t\u6b61\u8fce\u4f86\u5230\u3010\u5efa\u7acb\u5305\u570d\u8f2a\u5ed3\u7684\u77e9\u5f62\u548c\u5713\u5f62\u908a\u754c\u6846\u3011\u7bc4\u4f8b\u7a0b\u5e8f~\n\n");  
	printf( "\n\n\t\u6309\u9375\u64cd\u4f5c\u8aaa\u660e: \n\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u3010ESC\u3011- \u9000\u51fa\u7a0b\u5e8f\n\n"  
		"\t\t\u6ed1\u52d5\u6372\u8ef8 - \u6539\u8b8a\u95be\u503c\n\n");  
}  

