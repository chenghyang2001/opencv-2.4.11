#include <stdio.h>


//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f27
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u5716\u50cf\u5c0d\u6bd4\u5ea6\u3001\u4eae\u5ea6\u503c\u8abf\u6574
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//-----------------------------------\u3010\u982d\u6587\u4ef6\u5305\u542b\u90e8\u5206\u3011---------------------------------------
//	\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f9d\u8cf4\u7684\u982d\u6587\u4ef6
//---------------------------------------------------------------------------------------------- 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

//-----------------------------------\u3010\u547d\u540d\u7a7a\u9593\u5ba3\u544a\u90e8\u5206\u3011---------------------------------------
//	\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u547d\u540d\u7a7a\u9593
//-----------------------------------------------------------------------------------------------   
using namespace std;
using namespace cv;


//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//	\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
static void ContrastAndBright(int, void *);
void   ShowHelpText();

//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//	\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
int g_nContrastValue; //\u5c0d\u6bd4\u5ea6\u503c
int g_nBrightValue;  //\u4eae\u5ea6\u503c
Mat g_srcImage,g_dstImage;
//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//	\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-----------------------------------------------------------------------------------------------
int main(   )
{
	//\u6539\u8b8a\u63a7\u5236\u81fa\u524d\u666f\u8272\u548c\u80cc\u666f\u8272
	system("color 2F");  

	ShowHelpText();
	// \u8b80\u5165\u7528\u6236\u63d0\u4f9b\u7684\u5716\u50cf
	g_srcImage = imread( "1.jpg");
	if( !g_srcImage.data ) { printf("Oh\uff0cno\uff0c\u8b80\u53d6g_srcImage\u5716\u5f62\u932f\u8aa4~\uff01 \n"); return false; }
	g_dstImage = Mat::zeros( g_srcImage.size(), g_srcImage.type() );

	//\u8a2d\u5b9a\u5c0d\u6bd4\u5ea6\u548c\u4eae\u5ea6\u7684\u521d\u503c
	g_nContrastValue=80;
	g_nBrightValue=80;

	//\u5efa\u7acb\u8996\u7a97
	namedWindow("\u3010\u6548\u679c\u5716\u8996\u7a97\u3011", 1);

	//\u5efa\u7acb\u8ecc\u8de1\u689d
	createTrackbar("\u5c0d\u6bd4\u5ea6\uff1a", "\u3010\u6548\u679c\u5716\u8996\u7a97\u3011",&g_nContrastValue, 300,ContrastAndBright );
	createTrackbar("\u4eae   \u5ea6\uff1a", "\u3010\u6548\u679c\u5716\u8996\u7a97\u3011",&g_nBrightValue, 200,ContrastAndBright );

	//\u4f7f\u7528\u56de\u8abf\u51fd\u6578
	ContrastAndBright(g_nContrastValue,0);
	ContrastAndBright(g_nBrightValue,0);

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	cout<<endl<<"\t\u57f7\u884c\u6210\u529f\uff0c\u8acb\u8abf\u6574\u6372\u8ef8\u89c0\u5bdf\u5716\u50cf\u6548\u679c\n\n"
		<<"\t\u6309\u4e0b\u201cq\u201d\u9375\u6642\uff0c\u7a0b\u5e8f\u9000\u51fa\n";

	//\u6309\u4e0b\u201cq\u201d\u9375\u6642\uff0c\u7a0b\u5e8f\u9000\u51fa
	while(char(waitKey(1)) != 'q') {}
	return 0;
}




//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//		 \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c27\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


//-----------------------------\u3010ContrastAndBright( )\u51fd\u6578\u3011------------------------------------
//	\u63cf\u8ff0\uff1a\u6539\u8b8a\u5716\u50cf\u5c0d\u6bd4\u5ea6\u548c\u4eae\u5ea6\u503c\u7684\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------
static void ContrastAndBright(int, void *)
{

	// \u5efa\u7acb\u8996\u7a97
	namedWindow("\u3010\u539f\u59cb\u5716\u8996\u7a97\u3011", 1);

	// \u4e09\u500bfor\u5faa\u74b0\uff0c\u57f7\u884c\u904b\u7b97 g_dstImage(i,j) = a*g_srcImage(i,j) + b
	for( int y = 0; y < g_srcImage.rows; y++ )
	{
		for( int x = 0; x < g_srcImage.cols; x++ )
		{
			for( int c = 0; c < 3; c++ )
			{
				g_dstImage.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( (g_nContrastValue*0.01)*( g_srcImage.at<Vec3b>(y,x)[c] ) + g_nBrightValue );
			}
		}
	}

	// \u986f\u793a\u5716\u50cf
	imshow("\u3010\u539f\u59cb\u5716\u8996\u7a97\u3011", g_srcImage);
	imshow("\u3010\u6548\u679c\u5716\u8996\u7a97\u3011", g_dstImage);
}


