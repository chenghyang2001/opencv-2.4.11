#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f90
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1aSURF\u7279\u5fb5\u63cf\u8ff0
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/nonfree/nonfree.hpp>
#include<opencv2/legacy/legacy.hpp>
#include <iostream>
using namespace cv;
using namespace std;



//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
static void ShowHelpText( );//\u8f38\u51fa\u8aaa\u660e\u6587\u5b57


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main(  )
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 1F"); 

	//\u30100\u3011\u986f\u793a\u6b61\u8fce\u548c\u8aaa\u660e\u6587\u5b57
	ShowHelpText( );

	//\u30101\u3011\u8f09\u5165\u7d20\u6750\u5716
	Mat srcImage1 = imread("1.jpg",1);
	Mat srcImage2 = imread("2.jpg",1);
	if( !srcImage1.data || !srcImage2.data )
	{ printf("\u8b80\u53d6\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u7684\u5716\u5f62\u5b58\u5728~\uff01 \n"); return false; }  

	//\u30102\u3011\u4f7f\u7528SURF\u7b97\u5b50\u6aa2\u6e2c\u95dc\u9375\u9ede
	int minHessian = 700;//SURF\u7b97\u6cd5\u4e2d\u7684hessian\u95be\u503c
	SurfFeatureDetector detector( minHessian );//\u5b9a\u7fa9\u4e00\u500bSurfFeatureDetector\uff08SURF\uff09 \u7279\u5fb5\u6aa2\u6e2c\u985e\u5225\u5c0d\u8c61  
	std::vector<KeyPoint> keyPoint1, keyPoints2;//vector\u6a21\u677f\u985e\u5225\uff0c\u5b58\u653e\u4efb\u610f\u985e\u5225\u578b\u7684\u52d5\u614b\u6578\u7d44

	//\u30103\u3011\u4f7f\u7528detect\u51fd\u6578\u6aa2\u6e2c\u51faSURF\u7279\u5fb5\u95dc\u9375\u9ede\uff0c\u5132\u5b58\u5728vector\u5bbf\u4e3b\u4e2d
	detector.detect( srcImage1, keyPoint1 );
	detector.detect( srcImage2, keyPoints2 );

	//\u30104\u3011\u8a08\u7b97\u63cf\u8ff0\u8868\uff08\u7279\u5fb5\u5411\u91cf\uff09
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute( srcImage1, keyPoint1, descriptors1 );
	extractor.compute( srcImage2, keyPoints2, descriptors2 );

	//\u30105\u3011\u4f7f\u7528BruteForce\u9032\u884c\u6bd4\u5c0d
	// \u5be6\u4f8b\u5316\u4e00\u500b\u6bd4\u5c0d\u5668
	BruteForceMatcher< L2<float> > matcher;
	std::vector< DMatch > matches;
	//\u6bd4\u5c0d\u5169\u5e45\u5716\u4e2d\u7684\u63cf\u8ff0\u5b50\uff08descriptors\uff09
	matcher.match( descriptors1, descriptors2, matches );

	//\u30106\u3011\u7e6a\u88fd\u5f9e\u5169\u500b\u5716\u50cf\u4e2d\u6bd4\u5c0d\u51fa\u7684\u95dc\u9375\u9ede
	Mat imgMatches;
	drawMatches( srcImage1, keyPoint1, srcImage2, keyPoints2, matches, imgMatches );//\u9032\u884c\u7e6a\u88fd

	//\u30107\u3011\u986f\u793a\u6548\u679c\u5716
	imshow("\u6bd4\u5c0d\u5716", imgMatches );

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
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c90\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//\u8f38\u51fa\u8aaa\u660e\u8a0a\u606f  
	printf(  "\n\n\n\t\u6b61\u8fce\u4f86\u5230\u3010SURF\u7279\u5fb5\u63cf\u8ff0\u3011\u7bc4\u4f8b\u7a0b\u5e8f\n\n");  
}  
