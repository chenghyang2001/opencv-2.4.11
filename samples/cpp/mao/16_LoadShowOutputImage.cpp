#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f16
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u5716\u50cf\u7684\u8f09\u5165\u3001\u986f\u793a\u548c\u8f38\u51fa\u7bc4\u4f8b
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7403\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;


int main( )
{
	//-----------------------------------\u3010\u4e00\u3001\u5716\u50cf\u7684\u8f09\u5165\u548c\u986f\u793a\u3011---------------------------------
	//	\u63cf\u8ff0\uff1a\u4ee5\u4e0b\u4e09\u884c\u7a0b\u5f0f\u78bc\u7528\u4e8e\u5b8c\u6210\u5716\u50cf\u7684\u8f09\u5165\u548c\u986f\u793a
	//--------------------------------------------------------------------------------------------------

	Mat girl=imread("girl.jpg"); //\u8f09\u5165\u5716\u50cf\u5230Mat
	namedWindow("\u30101\u3011\u52d5\u6f2b\u5716"); //\u5efa\u7acb\u4e00\u500b\u540d\u70ba "\u30101\u3011\u52d5\u6f2b\u5716"\u7684\u8996\u7a97  
	imshow("\u30101\u3011\u52d5\u6f2b\u5716",girl);//\u986f\u793a\u540d\u70ba "\u30101\u3011\u52d5\u6f2b\u5716"\u7684\u8996\u7a97  

	//-----------------------------------\u3010\u4e8c\u3001\u521d\u7d1a\u5716\u50cf\u6df7\u5408\u3011--------------------------------------
	//	\u63cf\u8ff0\uff1a\u4e8c\u3001\u521d\u7d1a\u5716\u50cf\u6df7\u5408
	//--------------------------------------------------------------------------------------------------
	//\u8f09\u5165\u5716\u5f62
	Mat image= imread("dota.jpg",199);
	Mat logo= imread("dota_logo.jpg");

	//\u8f09\u5165\u5f8c\u5148\u986f\u793a
	namedWindow("\u30102\u3011\u539f\u756b\u5716");
	imshow("\u30102\u3011\u539f\u756b\u5716",image);

	namedWindow("\u30103\u3011logo\u5716");
	imshow("\u30103\u3011logo\u5716",logo);

	// \u5b9a\u7fa9\u4e00\u500bMat\u985e\u5225\u578b\uff0c\u7528\u4e8e\u5b58\u653e\uff0c\u5716\u50cf\u7684ROI
	Mat imageROI;
	//\u65b9\u6cd5\u4e00
	imageROI= image(Rect(800,350,logo.cols,logo.rows));
	//\u65b9\u6cd5\u4e8c
	//imageROI= image(Range(350,350+logo.rows),Range(800,800+logo.cols));

	// \u5c07logo\u52a0\u5230\u539f\u5716\u4e0a
	addWeighted(imageROI,0.5,logo,0.3,0.,imageROI);

	//\u986f\u793a\u7d50\u679c
	namedWindow("\u30104\u3011\u539f\u756b+logo\u5716");
	imshow("\u30104\u3011\u539f\u756b+logo\u5716",image);

	//-----------------------------------\u3010\u4e09\u3001\u5716\u50cf\u7684\u8f38\u51fa\u3011--------------------------------------
	//	\u63cf\u8ff0\uff1a\u5c07\u4e00\u500bMat\u5716\u50cf\u8f38\u51fa\u5230\u5716\u50cf\u6587\u4ef6
	//-----------------------------------------------------------------------------------------------
	//\u8f38\u51fa\u4e00\u5f35jpg\u5716\u5f62\u5230\u5c08\u6848\u76ee\u9304\u4e0b
	imwrite("\u7531imwrite\u7522\u751f\u7684\u5716\u5f62.jpg",image);

	waitKey();

	return 0;
}
