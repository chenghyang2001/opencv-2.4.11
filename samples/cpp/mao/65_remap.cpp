#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f65
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1aremap\u51fd\u6578\u7528\u6cd5\u7bc4\u4f8b
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
#include <iostream>
using namespace cv;


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main(  )
{
	//\u30100\u3011\u8b8a\u6578\u5b9a\u7fa9
	Mat srcImage, dstImage;
	Mat map_x, map_y;

	//\u30101\u3011\u8f09\u5165\u539f\u59cb\u5716
	srcImage = imread( "1.jpg", 1 );
	if(!srcImage.data ) { printf("\u8b80\u53d6\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u7684\u5716\u5f62\u5b58\u5728~\uff01 \n"); return false; }  
	imshow("\u539f\u59cb\u5716",srcImage);

	//\u30102\u3011\u5efa\u7acb\u548c\u539f\u59cb\u5716\u4e00\u6a23\u7684\u6548\u679c\u5716\uff0cx\u91cd\u6620\u5c04\u5716\uff0cy\u91cd\u6620\u5c04\u5716
	dstImage.create( srcImage.size(), srcImage.type() );
	map_x.create( srcImage.size(), CV_32FC1 );
	map_y.create( srcImage.size(), CV_32FC1 );

	//\u30103\u3011\u96d9\u5c64\u5faa\u74b0\uff0c\u700f\u89bd\u6bcf\u4e00\u500b\u50cf\u7d20\u9ede\uff0c\u6539\u8b8amap_x & map_y\u7684\u503c
	for( int j = 0; j < srcImage.rows;j++)
	{ 
		for( int i = 0; i < srcImage.cols;i++)
		{
			//\u6539\u8b8amap_x & map_y\u7684\u503c. 
			map_x.at<float>(j,i) = static_cast<float>(i);
			map_y.at<float>(j,i) = static_cast<float>(srcImage.rows - j);
		} 
	}

	//\u30104\u3011\u9032\u884c\u91cd\u6620\u5c04\u64cd\u4f5c
	remap( srcImage, dstImage, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0, 0) );

	//\u30105\u3011\u986f\u793a\u6548\u679c\u5716
	imshow( "\u3010\u7a0b\u5f0f\u8996\u7a97\u3011", dstImage );
	waitKey();

	return 0;
}

