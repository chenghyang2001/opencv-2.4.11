#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f07
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u4f7f\u7528VideoCapture\u985e\u5225\u4f7f\u7528\u651d\u5f71\u6a5f\u8b80\u5165\u8996\u8a0a\u4e26\u986f\u793a
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7403\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------

//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//-------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>  
using namespace cv;  

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-------------------------------------------------------------------------------------------------
int main( )  
{  
	//\u30101\u3011\u5f9e\u651d\u5f71\u6a5f\u8b80\u5165\u8996\u8a0a
	VideoCapture capture(0);

	//\u30102\u3011\u5faa\u74b0\u986f\u793a\u6bcf\u4e00\u5e45
	while(1)  
	{  
		Mat frame;  //\u5b9a\u7fa9\u4e00\u500bMat\u8b8a\u6578\uff0c\u7528\u4e8e\u5b58\u5132\u6bcf\u4e00\u5e45\u7684\u5716\u50cf
		capture>>frame;  //\u8b80\u53d6\u73fe\u5728\u5e45
		imshow("\u8b80\u53d6\u8996\u8a0a",frame);  //\u986f\u793a\u73fe\u5728\u5e45
		waitKey(30);  //\u5ef6\u664230ms
	}  
	return 0;     
}  
