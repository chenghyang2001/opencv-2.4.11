#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f37
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u4e94\u7a2e\u5716\u50cf\u6ffe\u6ce2\u7d9c\u5408\u7bc4\u4f8b
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------

//-----------------------------------\u3010\u982d\u6587\u4ef6\u5305\u542b\u90e8\u5206\u3011---------------------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f9d\u8cf4\u7684\u982d\u6587\u4ef6
//---------------------------------------------------------------------------------------------- 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

//-----------------------------------\u3010\u547d\u540d\u7a7a\u9593\u5ba3\u544a\u90e8\u5206\u3011---------------------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u547d\u540d\u7a7a\u9593
//-----------------------------------------------------------------------------------------------  
using namespace std;
using namespace cv;


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3,g_dstImage4,g_dstImage5;
int g_nBoxFilterValue=6;  //\u65b9\u6846\u6ffe\u6ce2\u6838\u5fc3\u503c
int g_nMeanBlurValue=10;  //\u5747\u503c\u6ffe\u6ce2\u6838\u5fc3\u503c
int g_nGaussianBlurValue=6;  //\u9ad8\u65af\u6ffe\u6ce2\u6838\u5fc3\u503c
int g_nMedianBlurValue=10;  //\u4e2d\u503c\u6ffe\u6ce2\u53c3\u6578\u503c
int g_nBilateralFilterValue=10;  //\u96d9\u908a\u6ffe\u6ce2\u53c3\u6578\u503c


//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
//\u8ecc\u8de1\u689d\u56de\u8abf\u51fd\u6578
static void on_BoxFilter(int, void *);		//\u65b9\u6846\u6ffe\u6ce2
static void on_MeanBlur(int, void *);		//\u5747\u503c\u584a\u6ffe\u6ce2\u5668
static void on_GaussianBlur(int, void *);			//\u9ad8\u65af\u6ffe\u6ce2\u5668
static void on_MedianBlur(int, void *);			//\u4e2d\u503c\u6ffe\u6ce2\u5668
static void on_BilateralFilter(int, void *);			//\u96d9\u908a\u6ffe\u6ce2\u5668
void ShowHelpText();


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-----------------------------------------------------------------------------------------------
int main(   )
{
	system("color 4F");  

	ShowHelpText();	

	// \u8f09\u5165\u539f\u5716
	g_srcImage = imread( "1.jpg", 1 );
	if( !g_srcImage.data ) { printf("\u8b80\u53d6srcImage\u932f\u8aa4~\uff01 \n"); return false; }

	//\u514b\u9686\u539f\u5716\u5230\u56db\u500bMat\u985e\u5225\u578b\u4e2d
	g_dstImage1 = g_srcImage.clone( );
	g_dstImage2 = g_srcImage.clone( );
	g_dstImage3 = g_srcImage.clone( );
	g_dstImage4 = g_srcImage.clone( );
	g_dstImage5 = g_srcImage.clone( );

	//\u986f\u793a\u539f\u5716
	namedWindow("\u3010<0>\u539f\u5716\u8996\u7a97\u3011", 1);
	imshow("\u3010<0>\u539f\u5716\u8996\u7a97\u3011",g_srcImage);


	//=================\u3010<1>\u65b9\u6846\u6ffe\u6ce2\u3011=========================
	//\u5efa\u7acb\u8996\u7a97
	namedWindow("\u3010<1>\u65b9\u6846\u6ffe\u6ce2\u3011", 1);
	//\u5efa\u7acb\u8ecc\u8de1\u689d
	createTrackbar("\u6838\u5fc3\u503c\uff1a", "\u3010<1>\u65b9\u6846\u6ffe\u6ce2\u3011",&g_nBoxFilterValue, 50,on_BoxFilter );
	on_MeanBlur(g_nBoxFilterValue,0);
	imshow("\u3010<1>\u65b9\u6846\u6ffe\u6ce2\u3011", g_dstImage1);
	//=====================================================


	//=================\u3010<2>\u5747\u503c\u6ffe\u6ce2\u3011==========================
	//\u5efa\u7acb\u8996\u7a97
	namedWindow("\u3010<2>\u5747\u503c\u6ffe\u6ce2\u3011", 1);
	//\u5efa\u7acb\u8ecc\u8de1\u689d
	createTrackbar("\u6838\u5fc3\u503c\uff1a", "\u3010<2>\u5747\u503c\u6ffe\u6ce2\u3011",&g_nMeanBlurValue, 50,on_MeanBlur );
	on_MeanBlur(g_nMeanBlurValue,0);
	//======================================================


	//=================\u3010<3>\u9ad8\u65af\u6ffe\u6ce2\u3011===========================
	//\u5efa\u7acb\u8996\u7a97
	namedWindow("\u3010<3>\u9ad8\u65af\u6ffe\u6ce2\u3011", 1);
	//\u5efa\u7acb\u8ecc\u8de1\u689d
	createTrackbar("\u6838\u5fc3\u503c\uff1a", "\u3010<3>\u9ad8\u65af\u6ffe\u6ce2\u3011",&g_nGaussianBlurValue, 50,on_GaussianBlur );
	on_GaussianBlur(g_nGaussianBlurValue,0);
	//=======================================================


	//=================\u3010<4>\u4e2d\u503c\u6ffe\u6ce2\u3011===========================
	//\u5efa\u7acb\u8996\u7a97
	namedWindow("\u3010<4>\u4e2d\u503c\u6ffe\u6ce2\u3011", 1);
	//\u5efa\u7acb\u8ecc\u8de1\u689d
	createTrackbar("\u53c3\u6578\u503c\uff1a", "\u3010<4>\u4e2d\u503c\u6ffe\u6ce2\u3011",&g_nMedianBlurValue, 50,on_MedianBlur );
	on_MedianBlur(g_nMedianBlurValue,0);
	//=======================================================


	//=================\u3010<5>\u96d9\u908a\u6ffe\u6ce2\u3011===========================
	//\u5efa\u7acb\u8996\u7a97
	namedWindow("\u3010<5>\u96d9\u908a\u6ffe\u6ce2\u3011", 1);
	//\u5efa\u7acb\u8ecc\u8de1\u689d
	createTrackbar("\u53c3\u6578\u503c\uff1a", "\u3010<5>\u96d9\u908a\u6ffe\u6ce2\u3011",&g_nBilateralFilterValue, 50,on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue,0);
	//=======================================================


	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	cout<<endl<<"\t\u57f7\u884c\u6210\u529f\uff0c\u8acb\u8abf\u6574\u6372\u8ef8\u89c0\u5bdf\u5716\u50cf\u6548\u679c~\n\n"
		<<"\t\u6309\u4e0b\u201cq\u201d\u9375\u6642\uff0c\u7a0b\u5e8f\u9000\u51fa\u3002\n";
	while(char(waitKey(1)) != 'q') {}

	return 0;
}

//-----------------------------\u3010on_BoxFilter( )\u51fd\u6578\u3011------------------------------------
//		\u63cf\u8ff0\uff1a\u65b9\u6846\u6ffe\u6ce2\u64cd\u4f5c\u7684\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------
static void on_BoxFilter(int, void *)
{
	//\u65b9\u6846\u6ffe\u6ce2\u64cd\u4f5c
	boxFilter( g_srcImage, g_dstImage1, -1,Size( g_nBoxFilterValue+1, g_nBoxFilterValue+1));
	//\u986f\u793a\u8996\u7a97
	imshow("\u3010<1>\u65b9\u6846\u6ffe\u6ce2\u3011", g_dstImage1);
}

//-----------------------------\u3010on_MeanBlur( )\u51fd\u6578\u3011------------------------------------
//		\u63cf\u8ff0\uff1a\u5747\u503c\u6ffe\u6ce2\u64cd\u4f5c\u7684\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------
static void on_MeanBlur(int, void *)
{
	blur( g_srcImage, g_dstImage2, Size( g_nMeanBlurValue+1, g_nMeanBlurValue+1), Point(-1,-1));
	imshow("\u3010<2>\u5747\u503c\u6ffe\u6ce2\u3011", g_dstImage2);

}

//-----------------------------\u3010on_GaussianBlur( )\u51fd\u6578\u3011------------------------------------
//		\u63cf\u8ff0\uff1a\u9ad8\u65af\u6ffe\u6ce2\u64cd\u4f5c\u7684\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------
static void on_GaussianBlur(int, void *)
{
	GaussianBlur( g_srcImage, g_dstImage3, Size( g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1 ), 0, 0);
	imshow("\u3010<3>\u9ad8\u65af\u6ffe\u6ce2\u3011", g_dstImage3);
}


//-----------------------------\u3010on_MedianBlur( )\u51fd\u6578\u3011------------------------------------
//		\u63cf\u8ff0\uff1a\u4e2d\u503c\u6ffe\u6ce2\u64cd\u4f5c\u7684\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------
static void on_MedianBlur(int, void *)
{
	medianBlur ( g_srcImage, g_dstImage4, g_nMedianBlurValue*2+1 );
	imshow("\u3010<4>\u4e2d\u503c\u6ffe\u6ce2\u3011", g_dstImage4);
}


//-----------------------------\u3010on_BilateralFilter( )\u51fd\u6578\u3011------------------------------------
//		\u63cf\u8ff0\uff1a\u96d9\u908a\u6ffe\u6ce2\u64cd\u4f5c\u7684\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------
static void on_BilateralFilter(int, void *)
{
	bilateralFilter ( g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue*2, g_nBilateralFilterValue/2 );
	imshow("\u3010<5>\u96d9\u908a\u6ffe\u6ce2\u3011", g_dstImage5);
}

//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011-----------------------------
//		 \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c37\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


