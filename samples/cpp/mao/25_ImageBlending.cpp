#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f25
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u521d\u7d1a\u5716\u50cf\u6df7\u5408
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------


//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011-------------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------                                                                                 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//	\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
bool  ROI_AddImage();
bool  LinearBlending();
bool  ROI_LinearBlending();
void   ShowHelpText();

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//	\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-----------------------------------------------------------------------------------------------
int main(   )
{
	system("color 6F");
 
	ShowHelpText();

	if(ROI_AddImage( )&& LinearBlending( )&&ROI_LinearBlending( ))
	{
		cout<<endl<<"\n\u57f7\u884c\u6210\u529f\uff0c\u5f97\u51fa\u4e86\u9700\u8981\u7684\u5716\u50cf~! ";
	}

	waitKey(0);
	return 0;
}


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//		 \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c25\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}




//----------------------------------\u3010ROI_AddImage( )\u51fd\u6578\u3011----------------------------------
// \u51fd\u6578\u540d\uff1aROI_AddImage\uff08\uff09
//	\u63cf\u8ff0\uff1a\u5229\u7528\u611f\u8208\u8da3\u5340\u57dfROI\u5be6\u73fe\u5716\u50cf\u758a\u52a0
//----------------------------------------------------------------------------------------------
bool  ROI_AddImage()
{

	// \u30101\u3011\u8b80\u5165\u5716\u50cf
	Mat srcImage1= imread("dota_pa.jpg");
	Mat logoImage= imread("dota_logo.jpg");
	if( !srcImage1.data ) { printf("\u8b80\u53d6srcImage1\u932f\u8aa4~\uff01 \n"); return false; }
	if( !logoImage.data ) { printf("\u8b80\u53d6logoImage\u932f\u8aa4~\uff01 \n"); return false; }

	// \u30102\u3011\u5b9a\u7fa9\u4e00\u500bMat\u985e\u5225\u578b\u4e26\u7d66\u5176\u8a2d\u5b9aROI\u5340\u57df
	Mat imageROI= srcImage1(Rect(200,250,logoImage.cols,logoImage.rows));

	// \u30103\u3011\u52a0\u8f09\u63a9\u6a21\uff08\u5fc5\u9808\u662f\u7070\u5ea6\u5716\uff09
	Mat mask= imread("dota_logo.jpg",0);

	//\u30104\u3011\u5c07\u63a9\u819c\u62f7\u8c9d\u5230ROI
	logoImage.copyTo(imageROI,mask);

	// \u30105\u3011\u986f\u793a\u7d50\u679c
	namedWindow("<1>\u5229\u7528ROI\u5be6\u73fe\u5716\u50cf\u758a\u52a0\u7bc4\u4f8b\u8996\u7a97");
	imshow("<1>\u5229\u7528ROI\u5be6\u73fe\u5716\u50cf\u758a\u52a0\u7bc4\u4f8b\u8996\u7a97",srcImage1);

	return true;
}


//---------------------------------\u3010LinearBlending\uff08\uff09\u51fd\u6578\u3011-------------------------------------
// \u51fd\u6578\u540d\uff1aLinearBlending\uff08\uff09
// \u63cf\u8ff0\uff1a\u5229\u7528cv::addWeighted\uff08\uff09\u51fd\u6578\u5be6\u73fe\u5716\u50cf\u7dda\u6027\u6df7\u5408
//--------------------------------------------------------------------------------------------
bool  LinearBlending()
{
	//\u30100\u3011\u5b9a\u7fa9\u4e00\u4e9b\u5c40\u90e8\u8b8a\u6578
	double alphaValue = 0.5; 
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	// \u30101\u3011\u8b80\u53d6\u5716\u50cf ( \u5169\u5e45\u5716\u5f62\u9700\u70ba\u540c\u6a23\u7684\u985e\u5225\u578b\u548c\u5c3a\u5bf8 )
	srcImage2 = imread("mogu.jpg");
	srcImage3 = imread("rain.jpg");

	if( !srcImage2.data ) { printf("\u8b80\u53d6srcImage2\u932f\u8aa4\uff01 \n"); return false; }
	if( !srcImage3.data ) { printf("\u8b80\u53d6srcImage3\u932f\u8aa4\uff01 \n"); return false; }

	// \u30102\u3011\u9032\u884c\u5716\u50cf\u6df7\u5408\u52a0\u6b0a\u64cd\u4f5c
	betaValue = ( 1.0 - alphaValue );
	addWeighted( srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	// \u30103\u3011\u986f\u793a\u539f\u5716\u8996\u7a97
	imshow( "<2>\u7dda\u6027\u6df7\u5408\u7bc4\u4f8b\u8996\u7a97\u3010\u539f\u5716\u3011", srcImage2 );
	imshow( "<3>\u7dda\u6027\u6df7\u5408\u7bc4\u4f8b\u8996\u7a97\u3010\u6548\u679c\u5716\u3011", dstImage );

	return true;

}

//---------------------------------\u3010ROI_LinearBlending\uff08\uff09\u3011-------------------------------------
// \u51fd\u6578\u540d\uff1aROI_LinearBlending\uff08\uff09
// \u63cf\u8ff0\uff1a\u7dda\u6027\u6df7\u5408\u5be6\u73fe\u51fd\u6578,\u6307\u5b9a\u5340\u57df\u7dda\u6027\u5716\u50cf\u6df7\u5408.\u5229\u7528cv::addWeighted\uff08\uff09\u51fd\u6578\u7d50\u5408\u5b9a\u7fa9
//			  \u611f\u8208\u8da3\u5340\u57dfROI\uff0c\u5be6\u73fe\u81ea\u5b9a\u7fa9\u5340\u57df\u7684\u7dda\u6027\u6df7\u5408
//--------------------------------------------------------------------------------------------
bool  ROI_LinearBlending()
{

	//\u30101\u3011\u8b80\u53d6\u5716\u50cf
	Mat srcImage4= imread("dota_pa.jpg",1);
	Mat logoImage= imread("dota_logo.jpg");

	if( !srcImage4.data ) { printf("\u8b80\u53d6srcImage4\u932f\u8aa4~\uff01 \n"); return false; }
	if( !logoImage.data ) { printf("\u8b80\u53d6logoImage\u932f\u8aa4~\uff01 \n"); return false; }

	//\u30102\u3011\u5b9a\u7fa9\u4e00\u500bMat\u985e\u5225\u578b\u4e26\u7d66\u5176\u8a2d\u5b9aROI\u5340\u57df
	Mat imageROI;
	//\u65b9\u6cd5\u4e00
	imageROI= srcImage4(Rect(200,250,logoImage.cols,logoImage.rows));
	//\u65b9\u6cd5\u4e8c
	//imageROI= srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));

	//\u30103\u3011\u5c07logo\u52a0\u5230\u539f\u5716\u4e0a
	addWeighted(imageROI,0.5,logoImage,0.3,0.,imageROI);

	//\u30104\u3011\u986f\u793a\u7d50\u679c
	imshow("<4>\u5340\u57df\u7dda\u6027\u5716\u50cf\u6df7\u5408\u7bc4\u4f8b\u8996\u7a97",srcImage4);

	return true;
}

