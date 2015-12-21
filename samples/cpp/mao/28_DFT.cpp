#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f28
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u96e2\u6563\u5085\u7acb\u8449\u8b8a\u63db
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011-----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//-------------------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//		 \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c28\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}



//--------------------------------------\u3010main( )\u51fd\u6578\u3011-----------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-------------------------------------------------------------------------------------------------
int main( )
{

	//\u30101\u3011\u4ee5\u7070\u5ea6\u6a21\u5f0f\u8b80\u53d6\u539f\u59cb\u5716\u50cf\u4e26\u986f\u793a
	Mat srcImage = imread("1.jpg", 0);
	if(!srcImage.data ) { printf("\u8b80\u53d6\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u5716\u5f62\u5b58\u5728~\uff01 \n"); return false; } 
	imshow("\u539f\u59cb\u5716\u50cf" , srcImage);   

	ShowHelpText();

	//\u30102\u3011\u5c07\u8f38\u5165\u5716\u50cf\u5ef6\u64f4\u5230\u6700\u4f73\u7684\u5c3a\u5bf8\uff0c\u908a\u754c\u75280\u88dc\u5145
	int m = getOptimalDFTSize( srcImage.rows );
	int n = getOptimalDFTSize( srcImage.cols ); 
	//\u5c07\u65b0\u589e\u7684\u50cf\u7d20\u521d\u59cb\u5316\u70ba0.
	Mat padded;  
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

	//\u30103\u3011\u70ba\u5085\u7acb\u8449\u8b8a\u63db\u7684\u7d50\u679c(\u5be6\u90e8\u548c\u865b\u90e8)\u5206\u914d\u5b58\u5132\u7a7a\u9593\u3002
	//\u5c07planes\u6578\u7d44\u7d44\u5408\u5408\u4e26\u6210\u4e00\u500b\u591a\u901a\u9053\u7684\u6578\u7d44complexI
	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
	Mat complexI;
	merge(planes, 2, complexI);         

	//\u30104\u3011\u9032\u884c\u5c31\u5730\u96e2\u6563\u5085\u7acb\u8449\u8b8a\u63db
	dft(complexI, complexI);           

	//\u30105\u3011\u5c07\u5fa9\u6578\u8f49\u63db\u70ba\u5e45\u503c\uff0c\u5373=> log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes); // \u5c07\u591a\u901a\u9053\u6578\u7d44complexI\u5206\u96e2\u6210\u5e7e\u500b\u55ae\u901a\u9053\u6578\u7d44\uff0cplanes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude  
	Mat magnitudeImage = planes[0];

	//\u30106\u3011\u9032\u884c\u5c0d\u6578\u5c3a\u5ea6(logarithmic scale)\u7e2e\u653e
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);//\u6c42\u81ea\u7136\u5c0d\u6578

	//\u30107\u3011\u526a\u5207\u548c\u91cd\u5206\u5e03\u5e45\u5ea6\u5716\u8c61\u9650
	//\u82e5\u6709\u5947\u6578\u884c\u6216\u5947\u6578\u5217\uff0c\u9032\u884c\u983b\u8b5c\u88c1\u526a      
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
	//\u91cd\u65b0\u6392\u5217\u5085\u7acb\u8449\u5716\u50cf\u4e2d\u7684\u8c61\u9650\uff0c\u4f7f\u5f97\u539f\u9ede\u4f4d\u4e8e\u5716\u50cf\u4e2d\u5fc3  
	int cx = magnitudeImage.cols/2;
	int cy = magnitudeImage.rows/2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));   // ROI\u5340\u57df\u7684\u5de6\u4e0a
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));  // ROI\u5340\u57df\u7684\u53f3\u4e0a
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));  // ROI\u5340\u57df\u7684\u5de6\u4e0b
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); // ROI\u5340\u57df\u7684\u53f3\u4e0b
	//\u4ea4\u63db\u8c61\u9650\uff08\u5de6\u4e0a\u8207\u53f3\u4e0b\u9032\u884c\u4ea4\u63db\uff09
	Mat tmp;                           
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//\u4ea4\u63db\u8c61\u9650\uff08\u53f3\u4e0a\u8207\u5de6\u4e0b\u9032\u884c\u4ea4\u63db\uff09
	q1.copyTo(tmp);                 
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//\u30108\u3011\u6b78\u4e00\u5316\uff0c\u75280\u52301\u4e4b\u9593\u7684\u6d6e\u9ede\u503c\u5c07\u77e9\u9663\u8b8a\u63db\u70ba\u53ef\u8996\u7684\u5716\u50cf\u683c\u5f0f
	normalize(magnitudeImage, magnitudeImage, 0, 1, CV_MINMAX); 

	//\u30109\u3011\u986f\u793a\u6548\u679c\u5716
	imshow("\u983b\u8b5c\u5e45\u503c", magnitudeImage);    
	waitKey();

	return 0;
}
