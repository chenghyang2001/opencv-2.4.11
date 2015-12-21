#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f03
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u7c21\u55ae\u7684OpenCV\u5716\u50cf\u8150\u8755\u64cd\u4f5c
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7403\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------

//-----------------------------------\u3010\u982d\u6587\u4ef6\u5305\u542b\u90e8\u5206\u3011---------------------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f9d\u8cf4\u7684\u982d\u6587\u4ef6
//---------------------------------------------------------------------------------------------- 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//-----------------------------------\u3010\u547d\u540d\u7a7a\u9593\u5ba3\u544a\u90e8\u5206\u3011---------------------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u547d\u540d\u7a7a\u9593
//-----------------------------------------------------------------------------------------------  
using namespace cv;

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-----------------------------------------------------------------------------------------------
int main(   )
{
	//\u8f09\u5165\u539f\u5716  
	Mat srcImage = imread("1.jpg");
	//\u986f\u793a\u539f\u5716
	imshow("\u3010\u539f\u5716\u3011\u8150\u8755\u64cd\u4f5c", srcImage);
	//\u9032\u884c\u8150\u8755\u64cd\u4f5c 
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat dstImage;
	erode(srcImage, dstImage, element);
	//\u986f\u793a\u6548\u679c\u5716 
	imshow("\u3010\u6548\u679c\u5716\u3011\u8150\u8755\u64cd\u4f5c", dstImage);
	waitKey(0); 

	return 0;
}
