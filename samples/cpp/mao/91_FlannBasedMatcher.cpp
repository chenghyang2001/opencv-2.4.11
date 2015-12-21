#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f91
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1a\u4f7f\u7528FLANN\u9032\u884c\u7279\u5fb5\u9ede\u6bd4\u5c0d
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
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
//      \u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a    
//----------------------------------------------------------------------------------------------- 
static void ShowHelpText( );


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//   \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272    
	system("color 4F");    

	//\u30100\u3011\u986f\u793a\u8aaa\u660e\u6587\u5b57  
	ShowHelpText();  

	//\u30101\u3011\u8f09\u5165\u6e90\u5716\u5f62
	Mat img_1 = imread("1.jpg", 1 );
	Mat img_2 = imread( "2.jpg", 1 );
	if( !img_1.data || !img_2.data ) { printf("\u8b80\u53d6\u5716\u5f62image0\u932f\u8aa4~\uff01 \n"); return false; }  

	//\u30102\u3011\u5229\u7528SURF\u6aa2\u6e2c\u5668\u6aa2\u6e2c\u7684\u95dc\u9375\u9ede
	int minHessian = 300;
	SURF detector( minHessian );
	std::vector<KeyPoint> keypoints_1, keypoints_2;
	detector.detect( img_1, keypoints_1 );
	detector.detect( img_2, keypoints_2 );

	//\u30103\u3011\u8a08\u7b97\u63cf\u8ff0\u8868\uff08\u7279\u5fb5\u5411\u91cf\uff09
	SURF extractor;
	Mat descriptors_1, descriptors_2;
	extractor.compute( img_1, keypoints_1, descriptors_1 );
	extractor.compute( img_2, keypoints_2, descriptors_2 );

	//\u30104\u3011\u91c7\u7528FLANN\u7b97\u6cd5\u6bd4\u5c0d\u63cf\u8ff0\u8868\u5411\u91cf
	FlannBasedMatcher matcher;
	std::vector< DMatch > matches;
	matcher.match( descriptors_1, descriptors_2, matches );
	double max_dist = 0; double min_dist = 100;

	//\u30105\u3011\u5feb\u901f\u8a08\u7b97\u95dc\u9375\u9ede\u4e4b\u9593\u7684\u6700\u5927\u548c\u6700\u5c0f\u8ddd\u96e2
	for( int i = 0; i < descriptors_1.rows; i++ )
	{
		double dist = matches[i].distance;
		if( dist < min_dist ) min_dist = dist;
		if( dist > max_dist ) max_dist = dist;
	}
	//\u8f38\u51fa\u8ddd\u96e2\u8a0a\u606f
	printf("> \u6700\u5927\u8ddd\u96e2\uff08Max dist\uff09 : %f \n", max_dist );
	printf("> \u6700\u5c0f\u8ddd\u96e2\uff08Min dist\uff09 : %f \n", min_dist );

	//\u30106\u3011\u5b58\u4e0b\u8868\u5408\u689d\u4ef6\u7684\u6bd4\u5c0d\u7d50\u679c\uff08\u5373\u5176\u8ddd\u96e2\u5c0f\u4e8e2* min_dist\u7684\uff09\uff0c\u4f7f\u7528radiusMatch\u540c\u6a23\u53ef\u884c
	std::vector< DMatch > good_matches;
	for( int i = 0; i < descriptors_1.rows; i++ )
	{ 
		if( matches[i].distance < 2*min_dist )
		{ good_matches.push_back( matches[i]); }
	}

	//\u30107\u3011\u7e6a\u88fd\u51fa\u8868\u5408\u689d\u4ef6\u7684\u6bd4\u5c0d\u9ede
	Mat img_matches;
	drawMatches( img_1, keypoints_1, img_2, keypoints_2,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

	//\u30108\u3011\u8f38\u51fa\u76f8\u95dc\u6bd4\u5c0d\u9ede\u8a0a\u606f
	for( int i = 0; i < good_matches.size(); i++ )
	{ printf( ">\u8868\u5408\u689d\u4ef6\u7684\u6bd4\u5c0d\u9ede [%d] \u7279\u5fb5\u9ede1: %d  -- \u7279\u5fb5\u9ede2: %d  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx ); }

	//\u30109\u3011\u986f\u793a\u6548\u679c\u5716
	imshow( "\u6bd4\u5c0d\u6548\u679c\u5716", img_matches );

	//\u6309\u4efb\u610f\u9375\u9000\u51fa\u7a0b\u5f0f
	waitKey(0);
	return 0;
}

//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{ 
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c91\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
	printf("\n\t\u6b61\u8fce\u4f86\u5230\u3010FLNN\u7279\u5fb5\u6bd4\u5c0d\u3011\u7bc4\u4f8b\u7a0b\u5f0f\n\n");    
	printf( "\n\n\t\u6309\u9375\u64cd\u4f5c\u8aaa\u660e: \n\n"     
		"\t\t\u9375\u76e4\u6309\u9375\u4efb\u610f\u9375- \u9000\u51fa\u7a0b\u5f0f\n\n" );

}
