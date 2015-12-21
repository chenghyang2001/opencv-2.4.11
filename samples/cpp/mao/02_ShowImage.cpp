#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f02
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u7c21\u55ae\u7684OpenCV\u5716\u50cf\u986f\u793a
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7403\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------


#include <opencv2/opencv.hpp>  //\u982d\u6587\u4ef6
using namespace cv;  //\u5305\u542bcv\u547d\u540d\u7a7a\u9593

int main( )
{    
	// \u30101\u3011\u8b80\u5165\u4e00\u5f35\u5716\u5f62\uff0c\u8f09\u5165\u5716\u50cf
	Mat srcImage = imread("1.jpg");
	// \u30102\u3011\u986f\u793a\u8f09\u5165\u7684\u5716\u5f62
	imshow("\u3010\u539f\u59cb\u5716\u3011",srcImage);
	// \u30103\u3011\u7b49\u5f85\u4efb\u610f\u6309\u9375\u6309\u4e0b
	waitKey(0);
}  
