#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f68
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1a\u76f4\u689d\u5716\u5747\u8861\u5316
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------


//---------------------------------\u3010\u982d\u6a94\u6848\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011---------------------------
//          \u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6a94\u6848\u548c\u547d\u540d\u7a7a\u9593
//-----------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;


//--------------------------------------\u3010main( )\u51fd\u6578\u3011-----------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( )
{
	// \u30101\u3011\u52a0\u8f09\u6e90\u5716\u50cf
	Mat srcImage, dstImage;
	srcImage = imread( "1.jpg", 1 );
	if(!srcImage.data ) { printf("\u8b80\u53d6\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u5716\u5f62\u5b58\u5728~\uff01 \n"); return false; } 

	// \u30102\u3011\u8f49\u70ba\u7070\u5ea6\u5716\u4e26\u986f\u793a\u51fa\u4f86
	cvtColor( srcImage, srcImage, CV_BGR2GRAY );
	imshow( "\u539f\u59cb\u5716", srcImage );

	// \u30103\u3011\u9032\u884c\u76f4\u689d\u5716\u5747\u8861\u5316
	equalizeHist( srcImage, dstImage );

	// \u30104\u3011\u986f\u793a\u7d50\u679c
	imshow( "\u7d93\u904e\u76f4\u689d\u5716\u5747\u8861\u5316\u5f8c\u7684\u5716", dstImage );

	// \u7b49\u5f85\u7528\u6236\u6309\u9375\u9000\u51fa\u7a0b\u5f0f
	waitKey(0);
	return 0;

}
