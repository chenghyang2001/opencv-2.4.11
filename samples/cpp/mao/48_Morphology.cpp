#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f48
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u5f62\u614b\u5b78\u5716\u50cf\u8655\u7406\u2014\u2014\u958b\u904b\u7b97\u3001\u9589\u904b\u7b97\u3001\u5f62\u614b\u5b78\u68af\u5ea6\u3001\u9802\u5e3d\u3001\u9ed1\u5e3d
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011-----------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage;//\u539f\u59cb\u5716\u548c\u6548\u679c\u5716
int g_nElementShape = MORPH_RECT;//\u5143\u7d20\u7d50\u69cb\u7684\u5f62\u72c0

//\u8b8a\u6578\u63a5\u6536\u7684TrackBar\u4f4d\u7f6e\u53c3\u6578
int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackHatNum = 0;



//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
static void on_OpenClose(int, void*);//\u56de\u8abf\u51fd\u6578
static void on_ErodeDilate(int, void*);//\u56de\u8abf\u51fd\u6578
static void on_TopBlackHat(int, void*);//\u56de\u8abf\u51fd\u6578
static void ShowHelpText();


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-----------------------------------------------------------------------------------------------
int main( )
{
	//\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 2F");  

	ShowHelpText();

	//\u8f09\u5165\u539f\u5716
	g_srcImage = imread("1.jpg");
	if( !g_srcImage.data ) { printf("Oh\uff0cno\uff0c\u8b80\u53d6srcImage\u932f\u8aa4~\uff01 \n"); return false; }

	//\u986f\u793a\u539f\u59cb\u5716
	namedWindow("\u3010\u539f\u59cb\u5716\u3011");
	imshow("\u3010\u539f\u59cb\u5716\u3011", g_srcImage);

	//\u5efa\u7acb\u4e09\u500b\u8996\u7a97
	namedWindow("\u3010\u958b\u904b\u7b97/\u9589\u904b\u7b97\u3011",1);
	namedWindow("\u3010\u8150\u8755/\u81a8\u8139\u3011",1);
	namedWindow("\u3010\u9802\u5e3d/\u9ed1\u5e3d\u3011",1);

	//\u53c3\u6578\u8ce6\u503c
	g_nOpenCloseNum=9;
	g_nErodeDilateNum=9;
	g_nTopBlackHatNum=2;

	//\u5206\u5225\u70ba\u4e09\u500b\u8996\u7a97\u5efa\u7acb\u6372\u8ef8
	createTrackbar("\u504f\u79fb\u91cf", "\u3010\u958b\u904b\u7b97/\u9589\u904b\u7b97\u3011",&g_nOpenCloseNum,g_nMaxIterationNum*2+1,on_OpenClose);
	createTrackbar("\u504f\u79fb\u91cf", "\u3010\u8150\u8755/\u81a8\u8139\u3011",&g_nErodeDilateNum,g_nMaxIterationNum*2+1,on_ErodeDilate);
	createTrackbar("\u504f\u79fb\u91cf", "\u3010\u9802\u5e3d/\u9ed1\u5e3d\u3011",&g_nTopBlackHatNum,g_nMaxIterationNum*2+1,on_TopBlackHat);

	//\u8f2a\u8a62\u53d6\u5f97\u6309\u9375\u8a0a\u606f
	while(1)
	{
		int c;

		//\u57f7\u884c\u56de\u8abf\u51fd\u6578
		on_OpenClose(g_nOpenCloseNum, 0);
		on_ErodeDilate(g_nErodeDilateNum, 0);
		on_TopBlackHat(g_nTopBlackHatNum,0);

		//\u53d6\u5f97\u6309\u9375
		c = waitKey(0);

		//\u6309\u4e0b\u9375\u76e4\u6309\u9375Q\u6216\u8005ESC\uff0c\u7a0b\u5e8f\u9000\u51fa
		if( (char)c == 'q'||(char)c == 27 )
			break;
		//\u6309\u4e0b\u9375\u76e4\u6309\u93751\uff0c\u4f7f\u7528\u6a62\u5713(Elliptic)\u7d50\u69cb\u5143\u7d20\u7d50\u69cb\u5143\u7d20MORPH_ELLIPSE
		if( (char)c == 49 )//\u9375\u76e4\u6309\u93751\u7684ASII\u78bc\u70ba49
			g_nElementShape = MORPH_ELLIPSE;
		//\u6309\u4e0b\u9375\u76e4\u6309\u93752\uff0c\u4f7f\u7528\u77e9\u5f62(Rectangle)\u7d50\u69cb\u5143\u7d20MORPH_RECT
		else if( (char)c == 50 )//\u9375\u76e4\u6309\u93752\u7684ASII\u78bc\u70ba50
			g_nElementShape = MORPH_RECT;
		//\u6309\u4e0b\u9375\u76e4\u6309\u93753\uff0c\u4f7f\u7528\u5341\u5b57\u5f62(Cross-shaped)\u7d50\u69cb\u5143\u7d20MORPH_CROSS
		else if( (char)c == 51 )//\u9375\u76e4\u6309\u93753\u7684ASII\u78bc\u70ba51
			g_nElementShape = MORPH_CROSS;
		//\u6309\u4e0b\u9375\u76e4\u6309\u9375space\uff0c\u5728\u77e9\u5f62\u3001\u6a62\u5713\u3001\u5341\u5b57\u5f62\u7d50\u69cb\u5143\u7d20\u4e2d\u5faa\u74b0
		else if( (char)c == ' ' )
			g_nElementShape = (g_nElementShape + 1) % 3;
	}

	return 0;
}


//-----------------------------------\u3010on_OpenClose( )\u51fd\u6578\u3011----------------------------------
//		\u63cf\u8ff0\uff1a\u3010\u958b\u904b\u7b97/\u9589\u904b\u7b97\u3011\u8996\u7a97\u7684\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------
static void on_OpenClose(int, void*)
{
	//\u504f\u79fb\u91cf\u7684\u5b9a\u7fa9
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;//\u504f\u79fb\u91cf
	int Absolute_offset = offset > 0 ? offset : -offset;//\u504f\u79fb\u91cf\u7d55\u5c0d\u503c
	//\u81ea\u5b9a\u7fa9\u6838
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset) );
	//\u9032\u884c\u64cd\u4f5c
	if( offset < 0 )
		morphologyEx(g_srcImage, g_dstImage, CV_MOP_OPEN, element);
	else
		morphologyEx(g_srcImage, g_dstImage, CV_MOP_CLOSE, element);
	//\u986f\u793a\u5716\u50cf
	imshow("\u3010\u958b\u904b\u7b97/\u9589\u904b\u7b97\u3011",g_dstImage);
}


//-----------------------------------\u3010on_ErodeDilate( )\u51fd\u6578\u3011----------------------------------
//		\u63cf\u8ff0\uff1a\u3010\u8150\u8755/\u81a8\u8139\u3011\u8996\u7a97\u7684\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------
static void on_ErodeDilate(int, void*)
{
	//\u504f\u79fb\u91cf\u7684\u5b9a\u7fa9
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;	//\u504f\u79fb\u91cf
	int Absolute_offset = offset > 0 ? offset : -offset;//\u504f\u79fb\u91cf\u7d55\u5c0d\u503c
	//\u81ea\u5b9a\u7fa9\u6838
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset) );
	//\u9032\u884c\u64cd\u4f5c
	if( offset < 0 )
		erode(g_srcImage, g_dstImage, element);
	else
		dilate(g_srcImage, g_dstImage, element);
	//\u986f\u793a\u5716\u50cf
	imshow("\u3010\u8150\u8755/\u81a8\u8139\u3011",g_dstImage);
}


//-----------------------------------\u3010on_TopBlackHat( )\u51fd\u6578\u3011--------------------------------
//		\u63cf\u8ff0\uff1a\u3010\u9802\u5e3d\u904b\u7b97/\u9ed1\u5e3d\u904b\u7b97\u3011\u8996\u7a97\u7684\u56de\u8abf\u51fd\u6578
//----------------------------------------------------------------------------------------------
static void on_TopBlackHat(int, void*)
{
	//\u504f\u79fb\u91cf\u7684\u5b9a\u7fa9
	int offset = g_nTopBlackHatNum - g_nMaxIterationNum;//\u504f\u79fb\u91cf
	int Absolute_offset = offset > 0 ? offset : -offset;//\u504f\u79fb\u91cf\u7d55\u5c0d\u503c
	//\u81ea\u5b9a\u7fa9\u6838
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset) );
	//\u9032\u884c\u64cd\u4f5c
	if( offset < 0 )
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT , element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
	//\u986f\u793a\u5716\u50cf
	imshow("\u3010\u9802\u5e3d/\u9ed1\u5e3d\u3011",g_dstImage);
}

//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//		\u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c48\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf("\n\t\u8acb\u8abf\u6574\u6372\u8ef8\u89c0\u5bdf\u5716\u50cf\u6548\u679c\n\n");
	printf( "\n\t\u6309\u9375\u64cd\u4f5c\u8aaa\u660e: \n\n"
		"\t\t\u9375\u76e4\u6309\u9375\u3010ESC\u3011\u6216\u8005\u3010Q\u3011- \u9000\u51fa\u7a0b\u5e8f\n"
		"\t\t\u9375\u76e4\u6309\u9375\u30101\u3011- \u4f7f\u7528\u6a62\u5713(Elliptic)\u7d50\u69cb\u5143\u7d20\n"
		"\t\t\u9375\u76e4\u6309\u9375\u30102\u3011- \u4f7f\u7528\u77e9\u5f62(Rectangle )\u7d50\u69cb\u5143\u7d20\n"
		"\t\t\u9375\u76e4\u6309\u9375\u30103\u3011- \u4f7f\u7528\u5341\u5b57\u578b(Cross-shaped)\u7d50\u69cb\u5143\u7d20\n"
		"\t\t\u9375\u76e4\u6309\u9375\u3010\u7a7a\u683cSPACE\u3011- \u5728\u77e9\u5f62\u3001\u6a62\u5713\u3001\u5341\u5b57\u5f62\u7d50\u69cb\u5143\u7d20\u4e2d\u5faa\u74b0\n"	);
}
