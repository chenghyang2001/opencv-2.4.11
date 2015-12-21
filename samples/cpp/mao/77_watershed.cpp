#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f77
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1a\u5206\u6c34\u5dba\u6f14\u7b97\u6cd5\u7d9c\u5408\u7bc4\u4f8b
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
//  \u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "\u3010\u7a0b\u5f0f\u8996\u7a971\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 
#define WINDOW_NAME2 "\u3010\u5206\u6c34\u5dba\u6f14\u7b97\u6cd5\u6548\u679c\u5716\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6

//-----------------------------------\u3010\u5168\u5c40\u51fd\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat g_maskImage, g_srcImage;
Point prevPt(-1, -1);

//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
static void ShowHelpText();
static void on_Mouse( int event, int x, int y, int flags, void* );


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{	
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 6F"); 

	//\u30100\u3011\u986f\u793a\u8aaa\u660e\u6587\u5b57
	ShowHelpText( );

	//\u30101\u3011\u8f09\u5165\u539f\u5716\u4e26\u986f\u793a\uff0c\u521d\u59cb\u5316\u63a9\u819c\u548c\u7070\u5ea6\u5716
	g_srcImage = imread("1.jpg", 1);
	imshow( WINDOW_NAME1, g_srcImage );
	Mat srcImage,grayImage;
	g_srcImage.copyTo(srcImage);
	cvtColor(g_srcImage, g_maskImage, COLOR_BGR2GRAY);
	cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
	g_maskImage = Scalar::all(0);

	//\u30102\u3011\u8a2d\u5b9a\u6ed1\u9f20\u56de\u8abf\u51fd\u6578
	setMouseCallback( WINDOW_NAME1, on_Mouse, 0 );

	//\u30103\u3011\u8f2a\u8a62\u6309\u9375\uff0c\u9032\u884c\u8655\u7406
	while(1)
	{
		//\u53d6\u5f97\u9375\u503c
		int c = waitKey(0);

		//\u82e5\u6309\u9375\u9375\u503c\u70baESC\u6642\uff0c\u9000\u51fa
		if( (char)c == 27 )
			break;

		//\u6309\u9375\u9375\u503c\u70ba2\u6642\uff0c\u6062\u5fa9\u6e90\u5716
		if( (char)c == '2' )
		{
			g_maskImage = Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			imshow( "image", g_srcImage );
		}

		//\u82e5\u6aa2\u6e2c\u5230\u6309\u9375\u503c\u70ba1\u6216\u8005\u7a7a\u683c\uff0c\u5247\u9032\u884c\u8655\u7406
		if( (char)c == '1' || (char)c == ' ' )
		{
			//\u5b9a\u7fa9\u4e00\u4e9b\u53c3\u6578
			int i, j, compCount = 0;
			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;

			//\u5c0b\u627e\u8f2a\u5ed3
			findContours(g_maskImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

			//\u8f2a\u5ed3\u70ba\u7a7a\u6642\u7684\u8655\u7406
			if( contours.empty() )
				continue;

			//\u62f7\u8c9d\u63a9\u819c
			Mat maskImage(g_maskImage.size(), CV_32S);
			maskImage = Scalar::all(0);

			//\u5faa\u74b0\u7e6a\u88fd\u51fa\u8f2a\u5ed3
			for( int index = 0; index >= 0; index = hierarchy[index][0], compCount++ )
				drawContours(maskImage, contours, index, Scalar::all(compCount+1), -1, 8, hierarchy, INT_MAX);

			//compCount\u70ba\u96f6\u6642\u7684\u8655\u7406
			if( compCount == 0 )
				continue;

			//\u7522\u751f\u96a8\u6a5f\u984f\u8272
			vector<Vec3b> colorTab;
			for( i = 0; i < compCount; i++ )
			{
				int b = theRNG().uniform(0, 255);
				int g = theRNG().uniform(0, 255);
				int r = theRNG().uniform(0, 255);

				colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
			}

			//\u8a08\u7b97\u8655\u7406\u6642\u9593\u4e26\u8f38\u51fa\u5230\u8996\u7a97\u4e2d
			double dTime = (double)getTickCount();
			watershed( srcImage, maskImage );
			dTime = (double)getTickCount() - dTime;
			printf( "\t\u8655\u7406\u6642\u9593 = %gms\n", dTime*1000./getTickFrequency() );

			//\u96d9\u5c64\u5faa\u74b0\uff0c\u5c07\u5206\u6c34\u5dba\u5716\u50cf\u700f\u89bd\u5b58\u5165watershedImage\u4e2d
			Mat watershedImage(maskImage.size(), CV_8UC3);
			for( i = 0; i < maskImage.rows; i++ )
				for( j = 0; j < maskImage.cols; j++ )
				{
					int index = maskImage.at<int>(i,j);
					if( index == -1 )
						watershedImage.at<Vec3b>(i,j) = Vec3b(255,255,255);
					else if( index <= 0 || index > compCount )
						watershedImage.at<Vec3b>(i,j) = Vec3b(0,0,0);
					else
						watershedImage.at<Vec3b>(i,j) = colorTab[index - 1];
				}

				//\u6df7\u5408\u7070\u5ea6\u5716\u548c\u5206\u6c34\u5dba\u6548\u679c\u5716\u4e26\u986f\u793a\u6700\u7d42\u7684\u8996\u7a97
				watershedImage = watershedImage*0.5 + grayImage*0.5;
				imshow( WINDOW_NAME2, watershedImage );
		}
	}

	return 0;
}


//-----------------------------------\u3010onMouse( )\u51fd\u6578\u3011---------------------------------------
//		\u63cf\u8ff0\uff1a\u6ed1\u9f20\u8a0a\u606f\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------
static void on_Mouse( int event, int x, int y, int flags, void* )
{
	//\u8655\u7406\u6ed1\u9f20\u4e0d\u5728\u8996\u7a97\u4e2d\u7684\u60c5\u6cc1
	if( x < 0 || x >= g_srcImage.cols || y < 0 || y >= g_srcImage.rows )
		return;

	//\u8655\u7406\u6ed1\u9f20\u5de6\u9375\u76f8\u95dc\u8a0a\u606f
	if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
		prevPt = Point(-1,-1);
	else if( event == CV_EVENT_LBUTTONDOWN )
		prevPt = Point(x,y);

	//\u6ed1\u9f20\u5de6\u9375\u6309\u4e0b\u4e26\u79fb\u52d5\uff0c\u7e6a\u88fd\u51fa\u767d\u8272\u7dda\u689d
	else if( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) )
	{
		Point pt(x, y);
		if( prevPt.x < 0 )
			prevPt = pt;
		line( g_maskImage, prevPt, pt, Scalar::all(255), 5, 8, 0 );
		line( g_srcImage, prevPt, pt, Scalar::all(255), 5, 8, 0 );
		prevPt = pt;
		imshow(WINDOW_NAME1, g_srcImage);
	}
}


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------  
//      \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c77\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
	printf(  "\n\n\n\t\u6b61\u8fce\u4f86\u5230\u3010\u5206\u6c34\u5dba\u6f14\u7b97\u6cd5\u3011\u7bc4\u4f8b\u7a0b\u5f0f~\n\n");  
	printf(  "\t\u8acb\u5148\u7528\u6ed1\u9f20\u5728\u5716\u5f62\u8996\u7a97\u4e2d\u6a19\u8a18\u51fa\u5927\u81f4\u7684\u5340\u57df\uff0c\n\n\t\u7136\u5f8c\u518d\u6309\u9375\u30101\u3011\u6216\u8005\u3010SPACE\u3011\u555f\u52d5\u7b97\u6cd5\u3002"
		"\n\n\t\u6309\u9375\u64cd\u4f5c\u8aaa\u660e: \n\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30101\u3011\u6216\u8005\u3010SPACE\u3011- \u57f7\u884c\u7684\u5206\u6c34\u5dba\u5206\u5272\u7b97\u6cd5\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30102\u3011- \u6062\u5fa9\u539f\u59cb\u5716\u5f62\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u3010ESC\u3011- \u9000\u51fa\u7a0b\u5f0f\n\n\n");  
}  
