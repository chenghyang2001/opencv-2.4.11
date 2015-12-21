#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f69
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u57fa\u790e\u8f2a\u5ed3\u67e5\u8a62\u2014\u2014findContours+drawContours
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
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------

//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-------------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	// \u30101\u3011\u8f09\u5165\u539f\u59cb\u5716\uff0c\u4e14\u5fc5\u9808\u4ee5\u4e8c\u503c\u5716\u6a21\u5f0f\u8f09\u5165
	Mat srcImage=imread("1.jpg", 0);
	imshow("\u539f\u59cb\u5716",srcImage);

	//\u30102\u3011\u521d\u59cb\u5316\u7d50\u679c\u5716
	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

	//\u30103\u3011srcImage\u53d6\u5927\u4e8e\u95be\u503c119\u7684\u90a3\u90e8\u5206
	srcImage = srcImage > 119;
	imshow( "\u53d6\u95be\u503c\u5f8c\u7684\u539f\u59cb\u5716", srcImage );

	//\u30104\u3011\u5b9a\u7fa9\u8f2a\u5ed3\u548c\u5c64\u6b21\u7d50\u69cb
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//\u30105\u3011\u67e5\u8a62\u8f2a\u5ed3
	findContours( srcImage, contours, hierarchy,
		CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

	// \u30106\u3011\u700f\u89bd\u6240\u6709\u9802\u5c64\u7684\u8f2a\u5ed3\uff0c \u4ee5\u96a8\u6a5f\u984f\u8272\u7e6a\u88fd\u51fa\u6bcf\u500b\u9023\u63a5\u7d44\u4ef6\u984f\u8272
	int index = 0;
	for( ; index >= 0; index = hierarchy[index][0] )
	{
		Scalar color( rand()&255, rand()&255, rand()&255 );
		drawContours( dstImage, contours, index, color, CV_FILLED, 8, hierarchy );
	}

	//\u30107\u3011\u986f\u793a\u6700\u5f8c\u7684\u8f2a\u5ed3\u5716
	imshow( "\u8f2a\u5ed3\u5716", dstImage );

	waitKey(0);

}
