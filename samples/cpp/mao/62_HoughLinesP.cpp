#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f62
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1aHoughLinesP\u51fd\u6578\u7528\u6cd5\u7bc4\u4f8b
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
//-------------------------------------------------------------------------------------------------
int main( )
{
	//\u30101\u3011\u8f09\u5165\u539f\u59cb\u5716\u548cMat\u8b8a\u6578\u5b9a\u7fa9   
	Mat srcImage = imread("1.jpg");  //\u5c08\u6848\u76ee\u9304\u4e0b\u61c9\u8a72\u6709\u4e00\u5f35\u540d\u70ba1.jpg\u7684\u7d20\u6750\u5716
	Mat midImage,dstImage;//\u81e8\u6642\u8b8a\u6578\u548c\u76ee\u6a19\u5716\u7684\u5b9a\u7fa9

	//\u30102\u3011\u9032\u884c\u908a\u7de3\u6aa2\u6e2c\u548c\u8f49\u5316\u70ba\u7070\u5ea6\u5716
	Canny(srcImage, midImage, 50, 200, 3);//\u9032\u884c\u4e00\u6b64canny\u908a\u7de3\u6aa2\u6e2c
	cvtColor(midImage,dstImage, CV_GRAY2BGR);//\u8f49\u5316\u908a\u7de3\u6aa2\u6e2c\u5f8c\u7684\u5716\u70ba\u7070\u5ea6\u5716

	//\u30103\u3011\u9032\u884c\u970d\u592b\u7dda\u8b8a\u63db
	vector<Vec4i> lines;//\u5b9a\u7fa9\u4e00\u500b\u77e2\u91cf\u7d50\u69cblines\u7528\u4e8e\u5b58\u653e\u5f97\u5230\u7684\u7dda\u6bb5\u77e2\u91cf\u96c6\u5408
	HoughLinesP(midImage, lines, 1, CV_PI/180, 80, 50, 10 );

	//\u30104\u3011\u4f9d\u6b21\u5728\u5716\u4e2d\u7e6a\u88fd\u51fa\u6bcf\u689d\u7dda\u6bb5
	for( size_t i = 0; i < lines.size(); i++ )
	{
		Vec4i l = lines[i];
		line( dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186,88,255), 1, CV_AA);
	}

	//\u30105\u3011\u986f\u793a\u539f\u59cb\u5716  
	imshow("\u3010\u539f\u59cb\u5716\u3011", srcImage);  

	//\u30106\u3011\u908a\u7de3\u6aa2\u6e2c\u5f8c\u7684\u5716 
	imshow("\u3010\u908a\u7de3\u6aa2\u6e2c\u5f8c\u7684\u5716\u3011", midImage);  

	//\u30107\u3011\u986f\u793a\u6548\u679c\u5716  
	imshow("\u3010\u6548\u679c\u5716\u3011", dstImage);  

	waitKey(0);  

	return 0;  
}


