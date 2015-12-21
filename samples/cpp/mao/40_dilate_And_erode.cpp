#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f40
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u5716\u50cf\u8150\u8755\u8207\u81a8\u8139\u7d9c\u5408\u7bc4\u4f8b
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011-----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage;//\u539f\u59cb\u5716\u548c\u6548\u679c\u5716
int g_nTrackbarNumer = 0;//0\u8868\u793a\u8150\u8755erode, 1\u8868\u793a\u81a8\u8139dilate
int g_nStructElementSize = 3; //\u7d50\u69cb\u5143\u7d20(\u6838\u5fc3\u77e9\u9663)\u7684\u5c3a\u5bf8


//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
void Process();//\u81a8\u8139\u548c\u8150\u8755\u7684\u8655\u7406\u51fd\u6578
void on_TrackbarNumChange(int, void *);//\u56de\u8abf\u51fd\u6578
void on_ElementSizeChange(int, void *);//\u56de\u8abf\u51fd\u6578
void ShowHelpText();

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-----------------------------------------------------------------------------------------------
int main( )
{
	//\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 2F");  

	//\u8f09\u5165\u539f\u5716
	g_srcImage = imread("1.jpg");
	if( !g_srcImage.data ) { printf("\u8b80\u53d6srcImage\u932f\u8aa4~\uff01 \n"); return false; }

	ShowHelpText();

	//\u986f\u793a\u539f\u59cb\u5716
	namedWindow("\u3010\u539f\u59cb\u5716\u3011");
	imshow("\u3010\u539f\u59cb\u5716\u3011", g_srcImage);

	//\u9032\u884c\u521d\u6b21\u8150\u8755\u64cd\u4f5c\u4e26\u986f\u793a\u6548\u679c\u5716
	namedWindow("\u3010\u6548\u679c\u5716\u3011");
	//\u53d6\u5f97\u81ea\u5b9a\u7fa9\u6838
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));
	erode(g_srcImage, g_dstImage, element);
	imshow("\u3010\u6548\u679c\u5716\u3011", g_dstImage);

	//\u5efa\u7acb\u8ecc\u8de1\u689d
	createTrackbar("\u8150\u8755/\u81a8\u8139", "\u3010\u6548\u679c\u5716\u3011", &g_nTrackbarNumer, 1, on_TrackbarNumChange);
	createTrackbar("\u6838\u5fc3\u5c3a\u5bf8", "\u3010\u6548\u679c\u5716\u3011", &g_nStructElementSize, 21, on_ElementSizeChange);

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	cout<<endl<<"\t\u57f7\u884c\u6210\u529f\uff0c\u8acb\u8abf\u6574\u6372\u8ef8\u89c0\u5bdf\u5716\u50cf\u6548\u679c~\n\n"
		<<"\t\u6309\u4e0b\u201cq\u201d\u9375\u6642\uff0c\u7a0b\u5e8f\u9000\u51fa\u3002\n";

	//\u8f2a\u8a62\u53d6\u5f97\u6309\u9375\u8a0a\u606f\uff0c\u82e5\u4e0bq\u9375\uff0c\u7a0b\u5e8f\u9000\u51fa
	while(char(waitKey(1)) != 'q') {}

	return 0;
}

//-----------------------------\u3010Process( )\u51fd\u6578\u3011------------------------------------
//		\u63cf\u8ff0\uff1a\u9032\u884c\u81ea\u5b9a\u7fa9\u7684\u8150\u8755\u548c\u81a8\u8139\u64cd\u4f5c
//-----------------------------------------------------------------------------------------
void Process() 
{
	//\u53d6\u5f97\u81ea\u5b9a\u7fa9\u6838
	Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));

	//\u9032\u884c\u8150\u8755\u6216\u81a8\u8139\u64cd\u4f5c
	if(g_nTrackbarNumer == 0) {    
		erode(g_srcImage, g_dstImage, element);
	}
	else {
		dilate(g_srcImage, g_dstImage, element);
	}

	//\u986f\u793a\u6548\u679c\u5716
	imshow("\u3010\u6548\u679c\u5716\u3011", g_dstImage);
}


//-----------------------------\u3010on_TrackbarNumChange( )\u51fd\u6578\u3011------------------------------------
//		\u63cf\u8ff0\uff1a\u8150\u8755\u548c\u81a8\u8139\u4e4b\u9593\u5207\u63db\u958b\u95dc\u7684\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------------
void on_TrackbarNumChange(int, void *) 
{
	//\u8150\u8755\u548c\u81a8\u8139\u4e4b\u9593\u6548\u679c\u5df2\u7d93\u5207\u63db\uff0c\u56de\u8abf\u51fd\u6578\u9ad4\u5167\u9700\u4f7f\u7528\u4e00\u6b21Process\u51fd\u6578\uff0c\u4f7f\u6539\u8b8a\u5f8c\u7684\u6548\u679c\u7acb\u5373\u751f\u6548\u4e26\u986f\u793a\u51fa\u4f86
	Process();
}


//-----------------------------\u3010on_ElementSizeChange( )\u51fd\u6578\u3011-------------------------------------
//		\u63cf\u8ff0\uff1a\u8150\u8755\u548c\u81a8\u8139\u64cd\u4f5c\u6838\u5fc3\u6539\u8b8a\u6642\u7684\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------------
void on_ElementSizeChange(int, void *)
{
	//\u6838\u5fc3\u5c3a\u5bf8\u5df2\u6539\u8b8a\uff0c\u56de\u8abf\u51fd\u6578\u9ad4\u5167\u9700\u4f7f\u7528\u4e00\u6b21Process\u51fd\u6578\uff0c\u4f7f\u6539\u8b8a\u5f8c\u7684\u6548\u679c\u7acb\u5373\u751f\u6548\u4e26\u986f\u793a\u51fa\u4f86
	Process();
}


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011-----------------------------
//		 \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c40\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}
