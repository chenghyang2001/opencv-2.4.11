#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f51
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1aresize\u51fd\u6578\u7528\u6cd5\u7bc4\u4f8b
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-----------------------------------------------------------------------------------------------
int main( )
{
	//\u8f09\u5165\u539f\u59cb\u5716   
	Mat srcImage = imread("1.jpg");  //\u5c08\u6848\u76ee\u9304\u4e0b\u61c9\u8a72\u6709\u4e00\u5f35\u540d\u70ba1.jpg\u7684\u7d20\u6750\u5716
	Mat tmpImage,dstImage1,dstImage2;//\u81e8\u6642\u8b8a\u6578\u548c\u76ee\u6a19\u5716\u7684\u5b9a\u7fa9
	tmpImage=srcImage;//\u5c07\u539f\u59cb\u5716\u8ce6\u7d66\u81e8\u6642\u8b8a\u6578

	//\u986f\u793a\u539f\u59cb\u5716  
	imshow("\u3010\u539f\u59cb\u5716\u3011", srcImage);  

	//\u9032\u884c\u5c3a\u5bf8\u8abf\u6574\u64cd\u4f5c
	resize(tmpImage,dstImage1,Size( tmpImage.cols/2, tmpImage.rows/2 ),(0,0),(0,0),3);
	resize(tmpImage,dstImage2,Size( tmpImage.cols*2, tmpImage.rows*2 ),(0,0),(0,0),3);

	//\u986f\u793a\u6548\u679c\u5716  
	imshow("\u3010\u6548\u679c\u5716\u3011\u4e4b\u4e00", dstImage1);  
	imshow("\u3010\u6548\u679c\u5716\u3011\u4e4b\u4e8c", dstImage2);  

	waitKey(0);  
	return 0;  
}
