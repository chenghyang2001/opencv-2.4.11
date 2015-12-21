#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f67
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u4eff\u5c04\u8b8a\u63db\u7d9c\u5408\u7bc4\u4f8b
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
#define WINDOW_NAME1 "\u3010\u539f\u59cb\u5716\u8996\u7a97\u3011"					//\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 
#define WINDOW_NAME2 "\u3010\u7d93\u904eWarp\u5f8c\u7684\u5716\u50cf\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 
#define WINDOW_NAME3 "\u3010\u7d93\u904eWarp\u548cRotate\u5f8c\u7684\u5716\u50cf\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 



//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
static void ShowHelpText( );


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main(  )
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 1F"); 

	//\u30100\u3011\u986f\u793a\u6b61\u8fce\u548c\u8aaa\u660e\u6587\u5b57
	ShowHelpText( );

	//\u30101\u3011\u53c3\u6578\u6e96\u5099
	//\u5b9a\u7fa9\u5169\u7d44\u9ede\uff0c\u4ee3\u8868\u5169\u500b\u4e09\u89d2\u5f62
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];
	//\u5b9a\u7fa9\u4e00\u4e9bMat\u8b8a\u6578
	Mat rotMat( 2, 3, CV_32FC1 );
	Mat warpMat( 2, 3, CV_32FC1 );
	Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	//\u30102\u3011\u52a0\u8f09\u6e90\u5716\u50cf\u4e26\u4f5c\u4e00\u4e9b\u521d\u59cb\u5316
	srcImage = imread( "1.jpg", 1 );
	if(!srcImage.data ) { printf("\u8b80\u53d6\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u7684\u5716\u5f62\u5b58\u5728~\uff01 \n"); return false; } 
	// \u8a2d\u5b9a\u76ee\u6a19\u5716\u50cf\u7684\u5927\u5c0f\u548c\u985e\u5225\u578b\u8207\u6e90\u5716\u50cf\u4e00\u81f4
	dstImage_warp = Mat::zeros( srcImage.rows, srcImage.cols, srcImage.type() );

	//\u30103\u3011\u8a2d\u5b9a\u6e90\u5716\u50cf\u548c\u76ee\u6a19\u5716\u50cf\u4e0a\u7684\u4e09\u7d44\u9ede\u4ee5\u8a08\u7b97\u4eff\u5c04\u8b8a\u63db
	srcTriangle[0] = Point2f( 0,0 );
	srcTriangle[1] = Point2f( static_cast<float>(srcImage.cols - 1), 0 );
	srcTriangle[2] = Point2f( 0, static_cast<float>(srcImage.rows - 1 ));

	dstTriangle[0] = Point2f( static_cast<float>(srcImage.cols*0.0), static_cast<float>(srcImage.rows*0.33));
	dstTriangle[1] = Point2f( static_cast<float>(srcImage.cols*0.65), static_cast<float>(srcImage.rows*0.35));
	dstTriangle[2] = Point2f( static_cast<float>(srcImage.cols*0.15), static_cast<float>(srcImage.rows*0.6));

	//\u30104\u3011\u6c42\u5f97\u4eff\u5c04\u8b8a\u63db
	warpMat = getAffineTransform( srcTriangle, dstTriangle );

	//\u30105\u3011\u5c0d\u6e90\u5716\u50cf\u61c9\u7528\u525b\u525b\u6c42\u5f97\u7684\u4eff\u5c04\u8b8a\u63db
	warpAffine( srcImage, dstImage_warp, warpMat, dstImage_warp.size() );

	//\u30106\u3011\u5c0d\u5716\u50cf\u9032\u884c\u7e2e\u653e\u5f8c\u518d\u65cb\u8f49
	// \u8a08\u7b97\u7e5e\u5716\u50cf\u4e2d\u9ede\u9806\u6642\u91dd\u65cb\u8f4950\u5ea6\u7e2e\u653e\u56e0\u5b50\u70ba0.6\u7684\u65cb\u8f49\u77e9\u9663
	Point center = Point( dstImage_warp.cols/2, dstImage_warp.rows/2 );
	double angle = -50.0;
	double scale = 0.6;
	// \u901a\u904e\u4e0a\u9762\u7684\u65cb\u8f49\u7d30\u7bc0\u8a0a\u606f\u6c42\u5f97\u65cb\u8f49\u77e9\u9663
	rotMat = getRotationMatrix2D( center, angle, scale );
	// \u65cb\u8f49\u5df2\u7e2e\u653e\u5f8c\u7684\u5716\u50cf
	warpAffine( dstImage_warp, dstImage_warp_rotate, rotMat, dstImage_warp.size() );


	//\u30107\u3011\u986f\u793a\u7d50\u679c
	imshow( WINDOW_NAME1, srcImage );
	imshow( WINDOW_NAME2, dstImage_warp );
	imshow( WINDOW_NAME3, dstImage_warp_rotate );

	// \u7b49\u5f85\u7528\u6236\u6309\u4efb\u610f\u6309\u9375\u9000\u51fa\u7a0b\u5e8f
	waitKey(0);

	return 0;
}


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------  
//      \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  

	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c67\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
	printf(   "\n\n\t\t\u6b61\u8fce\u4f86\u5230\u4eff\u5c04\u8b8a\u63db\u7d9c\u5408\u7bc4\u4f8b\u7a0b\u5e8f.\n\n");  
	printf(  "\t\t\u9375\u76e4\u6309\u9375\u3010ESC\u3011- \u9000\u51fa\u7a0b\u5e8f\n"  );  
}  

