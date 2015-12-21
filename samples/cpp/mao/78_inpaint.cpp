#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f78
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1a\u5f71\u50cf\u4fee\u88dc\u7bc4\u4f8b
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include <iostream>
using namespace cv;
using namespace std;


//-----------------------------------\u3010\u5de8\u96c6\u5b9a\u7fa9\u90e8\u5206\u3011-------------------------------------------- 
//  \u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6 
//----------------------------------------------------------------------------------------------
#define WINDOW_NAME0 "\u3010\u539f\u59cb\u5716\u53c3\u8003\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 
#define WINDOW_NAME1 "\u3010\u539f\u59cb\u5716\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 
#define WINDOW_NAME2 "\u3010\u4fee\u88dc\u5f8c\u7684\u6548\u679c\u5716\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//          \u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat srcImage0,srcImage1, inpaintMask;
Point previousPoint(-1,-1);//\u539f\u4f86\u7684\u9ede\u5750\u6a19


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
static void ShowHelpText( )
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c78\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf("\n\n\n\t\u6b61\u8fce\u4f86\u5230\u3010\u5f71\u50cf\u4fee\u5fa9\u3011\u7bc4\u4f8b\u7a0b\u5f0f~\n"); 
	printf(  "\n\t\u8acb\u5728\u9032\u884c\u5f71\u50cf\u4fee\u5fa9\u64cd\u4f5c\u4e4b\u524d\uff0c\u5728\u3010\u539f\u59cb\u5716\u3011\u8996\u7a97\u4e2d\u9032\u884c\u9069\u91cf\u7684\u7e6a\u88fd" 
		"\n\n\t\u6309\u9375\u64cd\u4f5c\u8aaa\u660e: \n\n" 
		"\t\t\u3010\u6ed1\u9f20\u5de6\u9375\u3011-\u5728\u5f71\u50cf\u4e0a\u7e6a\u88fd\u767d\u8272\u7dda\u689d\n\n"
		"\t\t\u9375\u76e4\u6309\u9375\u3010ESC\u3011- \u9000\u51fa\u7a0b\u5f0f\n\n" 
		"\t\t\u9375\u76e4\u6309\u9375\u30101\u3011\u6216\u3010SPACE\u3011-\u9032\u884c\u5f71\u50cf\u4fee\u5fa9\u64cd\u4f5c \n\n"   );  
}


//-----------------------------------\u3010On_Mouse( )\u51fd\u6578\u3011--------------------------------
//          \u63cf\u8ff0\uff1a\u97ff\u61c9\u6ed1\u9f20\u8a0a\u606f\u7684\u56de\u8abf\u51fd\u6578
//----------------------------------------------------------------------------------------------
static void On_Mouse( int event, int x, int y, int flags, void* )
{
	//\u6ed1\u9f20\u5de6\u9375\u5f48\u8d77\u8a0a\u606f
	if( event == CV_EVENT_LBUTTONUP || !(flags & CV_EVENT_FLAG_LBUTTON) )
		previousPoint = Point(-1,-1);
	//\u6ed1\u9f20\u5de6\u9375\u6309\u4e0b\u8a0a\u606f
	else if( event == CV_EVENT_LBUTTONDOWN )
		previousPoint = Point(x,y);
	//\u6ed1\u9f20\u6309\u4e0b\u4e26\u79fb\u52d5\uff0c\u9032\u884c\u7e6a\u88fd
	else if( event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) )
	{
		Point pt(x,y);
		if( previousPoint.x < 0 )
			previousPoint = pt;
		//\u7e6a\u88fd\u767d\u8272\u7dda\u689d
		line( inpaintMask, previousPoint, pt, Scalar::all(255), 5, 8, 0 );
		line( srcImage1, previousPoint, pt, Scalar::all(255), 5, 8, 0 );
		previousPoint = pt;
		imshow(WINDOW_NAME1, srcImage1);
	}
}


//--------------------------------------\u3010main( )\u51fd\u6578\u3011-----------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 2F"); 

	//\u986f\u793a\u8aaa\u660e\u6587\u5b57
	ShowHelpText();

	//\u8f09\u5165\u539f\u59cb\u5716\u4e26\u9032\u884c\u63a9\u819c\u7684\u521d\u59cb\u5316
	Mat srcImage = imread("1.jpg", -1);
	if(!srcImage.data ) { printf("\u8b80\u53d6\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u5716\u5f62\u5b58\u5728~\uff01 \n"); return false; } 
	srcImage0 = srcImage.clone();
	srcImage1 = srcImage.clone();
	inpaintMask = Mat::zeros(srcImage1.size(), CV_8U);

	//\u986f\u793a\u539f\u59cb\u5716\u53c3\u8003
	imshow(WINDOW_NAME0, srcImage0);
	//\u986f\u793a\u539f\u59cb\u5716
	imshow(WINDOW_NAME1, srcImage1);
	//\u8a2d\u5b9a\u6ed1\u9f20\u56de\u8abf\u8a0a\u606f
	setMouseCallback( WINDOW_NAME1, On_Mouse, 0 );

	//\u8f2a\u8a62\u6309\u9375\uff0c\u6839\u64da\u4e0d\u540c\u7684\u6309\u9375\u9032\u884c\u8655\u7406
	while (1)
	{
		//\u53d6\u5f97\u6309\u9375\u9375\u503c
		char c = (char)waitKey();

		//\u9375\u503c\u70baESC\uff0c\u7a0b\u5f0f\u9000\u51fa
		if( c == 27 )
			break;

		//\u9375\u503c\u70ba2\uff0c\u6062\u5fa9\u6210\u539f\u59cb\u5f71\u50cf
		if( c == '2' )
		{
			inpaintMask = Scalar::all(0);
			srcImage.copyTo(srcImage1);
			imshow(WINDOW_NAME1, srcImage1);
		}

		//\u9375\u503c\u70ba1\u6216\u8005\u7a7a\u683c\uff0c\u9032\u884c\u5f71\u50cf\u4fee\u88dc\u64cd\u4f5c
		if( c == '1' || c == ' ' )
		{
			Mat inpaintedImage;
			inpaint(srcImage1, inpaintMask, inpaintedImage, 3, CV_INPAINT_TELEA);
			imshow(WINDOW_NAME2, inpaintedImage);
		}
	}

	return 0;
}
