#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f50
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1a\u6f2b\u6c34\u586b\u5145\u7b97\u6cd5\u7d9c\u5408\u7bc4\u4f8b
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------


//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------  
//      \u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u5ba3\u544a  
//-----------------------------------------------------------------------------------------------  
Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;//\u5b9a\u7fa9\u539f\u59cb\u5716\u3001\u76ee\u6a19\u5716\u3001\u7070\u968e\u5716\u3001\u63a9\u6a21\u5716
int g_nFillMode = 1;//\u6f2b\u6c34\u586b\u5145\u7684\u6a21\u5f0f
int g_nLowDifference = 20, g_nUpDifference = 20;//\u8ca0\u5dee\u6700\u5927\u503c\u3001\u6b63\u5dee\u6700\u5927\u503c
int g_nConnectivity = 4;//\u8868\u793afloodFill\u51fd\u6578\u6a19\u8b58\u8868\u4f4e\u516b\u4f4d\u7684\u9023\u901a\u503c
int g_bIsColor = true;//\u662f\u5426\u70ba\u5f69\u8272\u5716\u7684\u6a19\u8b58\u8868\u5e03\u723e\u503c
bool g_bUseMask = false;//\u662f\u5426\u986f\u793a\u63a9\u819c\u8996\u7a97\u7684\u5e03\u723e\u503c
int g_nNewMaskVal = 255;//\u65b0\u7684\u91cd\u65b0\u7e6a\u88fd\u7684\u50cf\u7d20\u503c


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------  
//      \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c50\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
	printf("\n\n\t\u6b61\u8fce\u4f86\u5230\u6f2b\u6c34\u586b\u5145\u7bc4\u4f8b\u7a0b\u5f0f~");  
	printf("\n\n\t\u672c\u7bc4\u4f8b\u6839\u64da\u6ed1\u9f20\u9078\u53d6\u7684\u9ede\u641c\u7d22\u5f71\u50cf\u4e2d\u8207\u4e4b\u984f\u8272\u76f8\u8fd1\u7684\u9ede\uff0c\u4e26\u7528\u4e0d\u540c\u984f\u8272\u6a19\u8a3b\u3002");  
	
	printf( "\n\n\t\u6309\u9375\u64cd\u4f5c\u8aaa\u660e: \n\n"  
		"\t\t\u6ed1\u9f20\u9ede\u64ca\u5716\u4e2d\u5340\u57df- \u9032\u884c\u6f2b\u6c34\u586b\u5145\u64cd\u4f5c\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u3010ESC\u3011- \u9000\u51fa\u7a0b\u5f0f\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30101\u3011-  \u5207\u63db\u5f69\u8272\u5716/\u7070\u968e\u5716\u6a21\u5f0f\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30102\u3011- \u986f\u793a/\u96b1\u85cf\u63a9\u819c\u8996\u7a97\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30103\u3011- \u6062\u5fa9\u539f\u59cb\u5f71\u50cf\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30104\u3011- \u4f7f\u7528\u7a7a\u7bc4\u570d\u7684\u6f2b\u6c34\u586b\u5145\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30105\u3011- \u4f7f\u7528\u6f38\u8b8a\u3001\u56fa\u5b9a\u7bc4\u570d\u7684\u6f2b\u6c34\u586b\u5145\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30106\u3011- \u4f7f\u7528\u6f38\u8b8a\u3001\u6d6e\u52d5\u7bc4\u570d\u7684\u6f2b\u6c34\u586b\u5145\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30107\u3011- \u64cd\u4f5c\u6a19\u8a8c\u7b26\u865f\u7684\u4f4e\u516b\u4f4d\u5143\u4f7f\u75284 \u4f4d\u5143\u7684\u9023\u63a5\u6a21\u5f0f\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30108\u3011- \u64cd\u4f5c\u6a19\u8a8c\u7b26\u865f\u7684\u4f4e\u516b\u4f4d\u5143\u4f7f\u75288 \u4f4d\u5143\u7684\u9023\u63a5\u6a21\u5f0f\n\n" 	);  
}  


//-----------------------------------\u3010onMouse( )\u51fd\u6578\u3011--------------------------------------  
//      \u63cf\u8ff0\uff1a\u6ed1\u9f20\u8a0a\u606fonMouse\u56de\u8abf\u51fd\u6578
//---------------------------------------------------------------------------------------------
static void onMouse( int event, int x, int y, int, void* )
{
	// \u82e5\u6ed1\u9f20\u5de6\u9375\u6c92\u6709\u6309\u4e0b\uff0c\u4fbf\u8fd4\u56de
	if( event != CV_EVENT_LBUTTONDOWN )
		return;

	//-------------------\u3010<1>\u4f7f\u7528floodFill\u51fd\u6578\u4e4b\u524d\u7684\u53c3\u6578\u6e96\u5099\u90e8\u5206\u3011---------------
	Point seed = Point(x,y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;//\u7a7a\u7bc4\u570d\u7684\u6f2b\u6c34\u586b\u5145\uff0c\u6b64\u503c\u8a2d\u70ba0\uff0c\u5426\u5247\u8a2d\u70ba\u5168\u5c40\u7684g_nLowDifference
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;//\u7a7a\u7bc4\u570d\u7684\u6f2b\u6c34\u586b\u5145\uff0c\u6b64\u503c\u8a2d\u70ba0\uff0c\u5426\u5247\u8a2d\u70ba\u5168\u5c40\u7684g_nUpDifference
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) +
		(g_nFillMode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);//\u6a19\u8b58\u8868\u76840~7\u4f4d\u70bag_nConnectivity\uff0c8~15\u4f4d\u70bag_nNewMaskVal\u5de6\u79fb8\u4f4d\u7684\u503c\uff0c16~23\u4f4d\u70baCV_FLOODFILL_FIXED_RANGE\u6216\u80050\u3002

	//\u96a8\u6a5f\u7522\u751fbgr\u503c
	int b = (unsigned)theRNG() & 255;//\u96a8\u6a5f\u8fd4\u56de\u4e00\u500b0~255\u4e4b\u9593\u7684\u503c
	int g = (unsigned)theRNG() & 255;//\u96a8\u6a5f\u8fd4\u56de\u4e00\u500b0~255\u4e4b\u9593\u7684\u503c
	int r = (unsigned)theRNG() & 255;//\u96a8\u6a5f\u8fd4\u56de\u4e00\u500b0~255\u4e4b\u9593\u7684\u503c
	Rect ccomp;//\u5b9a\u7fa9\u91cd\u7e6a\u5340\u57df\u7684\u6700\u5c0f\u908a\u754c\u77e9\u5f62\u5340\u57df

	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g*0.587 + b*0.114);//\u5728\u91cd\u7e6a\u5340\u57df\u50cf\u7d20\u7684\u65b0\u503c\uff0c\u82e5\u662f\u5f69\u8272\u5716\u6a21\u5f0f\uff0c\u53d6Scalar(b, g, r)\uff1b\u82e5\u662f\u7070\u968e\u5716\u6a21\u5f0f\uff0c\u53d6Scalar(r*0.299 + g*0.587 + b*0.114)

	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;//\u76ee\u6a19\u5716\u7684\u8ce6\u503c
	int area;

	//--------------------\u3010<2>\u6b63\u5f0f\u4f7f\u7528floodFill\u51fd\u6578\u3011-----------------------------
	if( g_bUseMask )
	{
		threshold(g_maskImage, g_maskImage, 1, 128, CV_THRESH_BINARY);
		area = floodFill(dst, g_maskImage, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
		imshow( "mask", g_maskImage );
	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
	}

	imshow("\u6548\u679c\u5716", dst);
	cout << area << " \u500b\u50cf\u7d20\u88ab\u91cd\u7e6a\n";
}


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------  
//      \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb  
//-----------------------------------------------------------------------------------------------  
int main( int argc, char** argv )
{
	//\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272  
	system("color 2F");    

	//\u8f09\u5165\u539f\u5716
	g_srcImage = imread("1.jpg", 1);

	if( !g_srcImage.data ) { printf("Oh\uff0cno\uff0c\u8b80\u53d6\u5716\u5f62image0\u932f\u8aa4~\uff01 \n"); return false; }  

	//\u986f\u793a\u8aaa\u660e\u6587\u5b57
	ShowHelpText();

	g_srcImage.copyTo(g_dstImage);//\u62f7\u8c9d\u6e90\u5716\u5230\u76ee\u6a19\u5716
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//\u8f49\u63db\u4e09\u901a\u9053\u7684image0\u5230\u7070\u968e\u5716
	g_maskImage.create(g_srcImage.rows+2, g_srcImage.cols+2, CV_8UC1);//\u5229\u7528image0\u7684\u5c3a\u5bf8\u4f86\u521d\u59cb\u5316\u63a9\u819cmask

	namedWindow( "\u6548\u679c\u5716",CV_WINDOW_AUTOSIZE );

	//\u5efa\u7acbTrackbar
	createTrackbar( "\u8ca0\u5dee\u6700\u5927\u503c", "\u6548\u679c\u5716", &g_nLowDifference, 255, 0 );
	createTrackbar( "\u6b63\u5dee\u6700\u5927\u503c" ,"\u6548\u679c\u5716", &g_nUpDifference, 255, 0 );

	//\u6ed1\u9f20\u56de\u8abf\u51fd\u6578
	setMouseCallback( "\u6548\u679c\u5716", onMouse, 0 );

	//\u5faa\u74b0\u8f2a\u8a62\u6309\u9375
	while(1)
	{
		//\u5148\u986f\u793a\u6548\u679c\u5716
		imshow("\u6548\u679c\u5716", g_bIsColor ? g_dstImage : g_grayImage);

		//\u53d6\u5f97\u9375\u76e4\u6309\u9375
		int c = waitKey(0);
		//\u5224\u65b7ESC\u662f\u5426\u6309\u4e0b\uff0c\u82e5\u6309\u4e0b\u4fbf\u9000\u51fa
		if( (c & 255) == 27 )
		{
			cout << "\u7a0b\u5f0f\u9000\u51fa...........\n";
			break;
		}

		//\u6839\u64da\u6309\u9375\u7684\u4e0d\u540c\uff0c\u9032\u884c\u5404\u7a2e\u64cd\u4f5c
		switch( (char)c )
		{
			//\u5982\u679c\u9375\u76e4\u201c1\u201d\u88ab\u6309\u4e0b\uff0c\u6548\u679c\u5716\u5728\u5728\u7070\u968e\u5716\uff0c\u5f69\u8272\u5716\u4e4b\u9593\u4e92\u63db
		case '1':
			if( g_bIsColor )//\u82e5\u539f\u4f86\u70ba\u5f69\u8272\uff0c\u8f49\u70ba\u7070\u968e\u5716\uff0c\u4e26\u4e14\u5c07\u63a9\u819cmask\u6240\u6709\u5143\u7d20\u8a2d\u5b9a\u70ba0
			{
				cout << "\u9375\u76e4\u201c1\u201d\u88ab\u6309\u4e0b\uff0c\u5207\u63db\u5f69\u8272/\u7070\u968e\u6a21\u5f0f\uff0c\u73fe\u5728\u64cd\u4f5c\u70ba\u5c07\u3010\u5f69\u8272\u6a21\u5f0f\u3011\u5207\u63db\u70ba\u3010\u7070\u968e\u6a21\u5f0f\u3011\n";
				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
				g_maskImage = Scalar::all(0);	//\u5c07mask\u6240\u6709\u5143\u7d20\u8a2d\u5b9a\u70ba0
				g_bIsColor = false;	//\u5c07\u6a19\u8b58\u8868\u7f6e\u70bafalse\uff0c\u8868\u793a\u73fe\u5728\u5f71\u50cf\u4e0d\u70ba\u5f69\u8272\uff0c\u800c\u662f\u7070\u968e
			}
			else//\u82e5\u539f\u4f86\u70ba\u7070\u968e\u5716\uff0c\u4fbf\u5c07\u539f\u4f86\u7684\u5f69\u5716image0\u518d\u6b21\u62f7\u8c9d\u7d66image\uff0c\u4e26\u4e14\u5c07\u63a9\u819cmask\u6240\u6709\u5143\u7d20\u8a2d\u5b9a\u70ba0
			{
				cout << "\u9375\u76e4\u201c1\u201d\u88ab\u6309\u4e0b\uff0c\u5207\u63db\u5f69\u8272/\u7070\u968e\u6a21\u5f0f\uff0c\u73fe\u5728\u64cd\u4f5c\u70ba\u5c07\u3010\u5f69\u8272\u6a21\u5f0f\u3011\u5207\u63db\u70ba\u3010\u7070\u968e\u6a21\u5f0f\u3011\n";
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true;//\u5c07\u6a19\u8b58\u8868\u7f6e\u70batrue\uff0c\u8868\u793a\u73fe\u5728\u5f71\u50cf\u6a21\u5f0f\u70ba\u5f69\u8272
			}
			break;
			//\u5982\u679c\u9375\u76e4\u6309\u9375\u201c2\u201d\u88ab\u6309\u4e0b\uff0c\u986f\u793a/\u96b1\u85cf\u63a9\u819c\u8996\u7a97
		case '2':
			if( g_bUseMask )
			{
				destroyWindow( "mask" );
				g_bUseMask = false;
			}
			else
			{
				namedWindow( "mask", 0 );
				g_maskImage = Scalar::all(0);
				imshow("mask", g_maskImage);
				g_bUseMask = true;
			}
			break;
			//\u5982\u679c\u9375\u76e4\u6309\u9375\u201c3\u201d\u88ab\u6309\u4e0b\uff0c\u6062\u5fa9\u539f\u59cb\u5f71\u50cf
		case '3':
			cout << "\u6309\u9375\u201c3\u201d\u88ab\u6309\u4e0b\uff0c\u6062\u5fa9\u539f\u59cb\u5f71\u50cf\n";
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
			g_maskImage = Scalar::all(0);
			break;
			//\u5982\u679c\u6309\u9375"4" \u88ab\u6309\u4e0b\uff0c\u4f7f\u7528\u7a7a\u7bc4\u570d\u7684\u6f2b\u6c34\u586b\u5145
		case '4':
			cout << "\u6309\u9375\u201c4\u201c \u88ab\u6309\u4e0b\uff0c\u4f7f\u7528\u7a7a\u7bc4\u570d\u7684\u6f2b\u6c34\u586b\u5145\n";
			g_nFillMode = 0;
			break;
			//\u5982\u679c\u6309\u9375"5" \u88ab\u6309\u4e0b\uff0c\u4f7f\u7528\u6f38\u8b8a\u3001\u56fa\u5b9a\u7bc4\u570d\u7684\u6f2b\u6c34\u586b\u5145
		case '5':
			cout << "\u6309\u9375\u201c5\u201c \u88ab\u6309\u4e0b\uff0c\u4f7f\u7528\u6f38\u8b8a\u3001\u56fa\u5b9a\u7bc4\u570d\u7684\u6f2b\u6c34\u586b\u5145\n";
			g_nFillMode = 1;
			break;
			//\u5982\u679c\u6309\u9375"6" \u88ab\u6309\u4e0b\uff0c\u4f7f\u7528\u6f38\u8b8a\u3001\u6d6e\u52d5\u7bc4\u570d\u7684\u6f2b\u6c34\u586b\u5145
		case '6':
			cout << "\u6309\u9375\u201c6\u201c \u88ab\u6309\u4e0b\uff0c\u4f7f\u7528\u6f38\u8b8a\u3001\u6d6e\u52d5\u7bc4\u570d\u7684\u6f2b\u6c34\u586b\u5145\n";
			g_nFillMode = 2;
			break;
			//\u5982\u679c\u6309\u9375"7" \u88ab\u6309\u4e0b\uff0c\u64cd\u4f5c\u6a19\u8a8c\u7b26\u865f\u7684\u4f4e\u516b\u4f4d\u5143\u4f7f\u75284 \u4f4d\u5143\u7684\u9023\u63a5\u6a21\u5f0f
		case '7':
			cout << "\u6309\u9375\u201c7\u201c \u88ab\u6309\u4e0b\uff0c\u64cd\u4f5c\u6a19\u8a8c\u7b26\u865f\u7684\u4f4e\u516b\u4f4d\u5143\u4f7f\u75284 \u4f4d\u5143\u7684\u9023\u63a5\u6a21\u5f0f\n";
			g_nConnectivity = 4;
			break;
			//\u5982\u679c\u6309\u9375"8" \u88ab\u6309\u4e0b\uff0c\u64cd\u4f5c\u6a19\u8a8c\u7b26\u865f\u7684\u4f4e\u516b\u4f4d\u5143\u4f7f\u75288 \u4f4d\u5143\u7684\u9023\u63a5\u6a21\u5f0f
		case '8':
			cout << "\u6309\u9375\u201c8\u201c \u88ab\u6309\u4e0b\uff0c\u64cd\u4f5c\u6a19\u8a8c\u7b26\u865f\u7684\u4f4e\u516b\u4f4d\u5143\u4f7f\u75288 \u4f4d\u5143\u7684\u9023\u63a5\u6a21\u5f0f\n";
			g_nConnectivity = 8;
			break;




		}
	}

	return 0;
}
