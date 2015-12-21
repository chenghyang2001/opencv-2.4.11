#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f82
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1a\u76f4\u689d\u5716\u5c0d\u6bd4
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6a94\u6848\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6a94\u6848\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011-----------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c82\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf("\n\n\u6b61\u8fce\u4f86\u5230\u3010\u76f4\u689d\u5716\u5c0d\u6bd4\u3011\u7bc4\u4f8b\u7a0b\u5f0f~\n\n"); 

}


//--------------------------------------\u3010main( )\u51fd\u6578\u3011-----------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( )
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 2F"); 

	//\u30101\u3011\u986f\u793a\u8aaa\u660e\u6587\u5b57
	ShowHelpText();

	//\u30101\u3011\u5ba3\u544a\u5132\u5b58\u57fa\u6e96\u5f71\u50cf\u548c\u53e6\u5916\u5169\u5f35\u5c0d\u6bd4\u5f71\u50cf\u7684\u77e9\u9663( RGB \u548c HSV )
	Mat srcImage_base, hsvImage_base;
	Mat srcImage_test1, hsvImage_test1;
	Mat srcImage_test2, hsvImage_test2;
	Mat hsvImage_halfDown;

	//\u30102\u3011\u8f09\u5165\u57fa\u6e96\u5f71\u50cf(srcImage_base) \u548c\u5169\u5f35\u6e2c\u8a66\u5f71\u50cfsrcImage_test1\u3001srcImage_test2\uff0c\u4e26\u986f\u793a
	srcImage_base = imread( "1.jpg",1 );
	srcImage_test1 = imread( "2.jpg", 1 );
	srcImage_test2 = imread( "3.jpg", 1 );
	//\u986f\u793a\u8f09\u5165\u76843\u5f35\u5f71\u50cf
	imshow("\u57fa\u6e96\u5f71\u50cf",srcImage_base);
	imshow("\u6e2c\u8a66\u5f71\u50cf1",srcImage_test1);
	imshow("\u6e2c\u8a66\u5f71\u50cf2",srcImage_test2);

	// \u30103\u3011\u5c07\u5f71\u50cf\u7531BGR\u8272\u5f69\u7a7a\u9593\u8f49\u63db\u5230 HSV\u8272\u5f69\u7a7a\u9593
	cvtColor( srcImage_base, hsvImage_base, CV_BGR2HSV );
	cvtColor( srcImage_test1, hsvImage_test1, CV_BGR2HSV );
	cvtColor( srcImage_test2, hsvImage_test2, CV_BGR2HSV );

	//\u30104\u3011\u5efa\u7acb\u5305\u542b\u57fa\u6e96\u5f71\u50cf\u4e0b\u534a\u90e8\u7684\u534a\u8eab\u5f71\u50cf(HSV\u683c\u5f0f)
	hsvImage_halfDown = hsvImage_base( Range( hsvImage_base.rows/2, hsvImage_base.rows - 1 ), Range( 0, hsvImage_base.cols - 1 ) );

	//\u30105\u3011\u521d\u59cb\u5316\u8a08\u7b97\u76f4\u689d\u5716\u9700\u8981\u7684\u5be6\u53c3
	// \u5c0dhue\u901a\u9053\u4f7f\u752830\u500bbin,\u5c0dsaturatoin\u901a\u9053\u4f7f\u752832\u500bbin
	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };
	// hue\u7684\u53d6\u503c\u8303\u570d\u5f9e0\u5230256, saturation\u53d6\u503c\u8303\u570d\u5f9e0\u5230180
	float h_ranges[] = { 0, 256 };
	float s_ranges[] = { 0, 180 };
	const float* ranges[] = { h_ranges, s_ranges };
	// \u4f7f\u7528\u7b2c0\u548c\u7b2c1\u901a\u9053
	int channels[] = { 0, 1 };

	// \u30106\u3011\u5efa\u7acb\u5132\u5b58\u76f4\u689d\u5716\u7684 MatND \u985e\u5225\u5225\u5225\u7684\u5be6\u4f8b:
	MatND baseHist;
	MatND halfDownHist;
	MatND testHist1;
	MatND testHist2;

	// \u30107\u3011\u8a08\u7b97\u57fa\u6e96\u5f71\u50cf\uff0c\u5169\u5f35\u6e2c\u8a66\u5f71\u50cf\uff0c\u534a\u8eab\u57fa\u6e96\u5f71\u50cf\u7684HSV\u76f4\u689d\u5716:
	calcHist( &hsvImage_base, 1, channels, Mat(), baseHist, 2, histSize, ranges, true, false );
	normalize( baseHist, baseHist, 0, 1, NORM_MINMAX, -1, Mat() );

	calcHist( &hsvImage_halfDown, 1, channels, Mat(), halfDownHist, 2, histSize, ranges, true, false );
	normalize( halfDownHist, halfDownHist, 0, 1, NORM_MINMAX, -1, Mat() );

	calcHist( &hsvImage_test1, 1, channels, Mat(), testHist1, 2, histSize, ranges, true, false );
	normalize( testHist1, testHist1, 0, 1, NORM_MINMAX, -1, Mat() );

	calcHist( &hsvImage_test2, 1, channels, Mat(), testHist2, 2, histSize, ranges, true, false );
	normalize( testHist2, testHist2, 0, 1, NORM_MINMAX, -1, Mat() );


	//\u30108\u3011\u6309\u9806\u5e8f\u4f7f\u75284\u7a2e\u5c0d\u6bd4\u6a19\u6e96\u5c07\u57fa\u6e96\u5f71\u50cf\u7684\u76f4\u689d\u5716\u8207\u5176\u4f59\u5404\u76f4\u689d\u5716\u9032\u884c\u5c0d\u6bd4:
	for( int i = 0; i < 4; i++ )
	{ 
		//\u9032\u884c\u5f71\u50cf\u76f4\u689d\u5716\u7684\u5c0d\u6bd4
		int compare_method = i;
		double base_base = compareHist( baseHist, baseHist, compare_method );
		double base_half = compareHist( baseHist, halfDownHist, compare_method );
		double base_test1 = compareHist( baseHist, testHist1, compare_method );
		double base_test2 = compareHist( baseHist, testHist2, compare_method );

		//\u8f38\u51fa\u7d50\u679c
		printf( " \u65b9\u6cd5 [%d] \u7684\u6bd4\u5c0d\u7d50\u679c\u5982\u4e0b\uff1a\n\n \u3010\u57fa\u6e96\u5716 - \u57fa\u6e96\u5716\u3011\uff1a%f, \u3010\u57fa\u6e96\u5716 - \u534a\u8eab\u5716\u3011\uff1a%f,\u3010\u57fa\u6e96\u5716 - \u6e2c\u8a66\u57161\u3011\uff1a %f, \u3010\u57fa\u6e96\u5716 - \u6e2c\u8a66\u57162\u3011\uff1a%f \n-----------------------------------------------------------------\n", i, base_base, base_half , base_test1, base_test2 );
	}

	printf( "\u6aa2\u6e2c\u7d50\u675f\u3002" );
	waitKey(0);
	return 0;
}
