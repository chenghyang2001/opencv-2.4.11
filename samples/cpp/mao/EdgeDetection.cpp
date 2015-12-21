#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f60
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u908a\u7de3\u6aa2\u6e2c\u7d9c\u5408\u7bc4\u4f8b\u2014\u2014Canny\u7b97\u5b50,Sobel\u7b97\u5b50,Laplace\u7b97\u5b50,Scharr\u6ffe\u6ce2\u5668\u5408\u8f2f
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
//\u539f\u5716\uff0c\u539f\u5716\u7684\u7070\u5ea6\u7248\uff0c\u76ee\u6a19\u5716
Mat g_srcImage, g_srcGrayImage,g_dstImage;

//Canny\u908a\u7de3\u6aa2\u6e2c\u76f8\u95dc\u8b8a\u6578
Mat g_cannyDetectedEdges;
int g_cannyLowThreshold=1;//TrackBar\u4f4d\u7f6e\u53c3\u6578  

//Sobel\u908a\u7de3\u6aa2\u6e2c\u76f8\u95dc\u8b8a\u6578
Mat g_sobelGradient_X, g_sobelGradient_Y;
Mat g_sobelAbsGradient_X, g_sobelAbsGradient_Y;
int g_sobelKernelSize=1;//TrackBar\u4f4d\u7f6e\u53c3\u6578  

//Scharr\u6ffe\u6ce2\u5668\u76f8\u95dc\u8b8a\u6578
Mat g_scharrGradient_X, g_scharrGradient_Y;
Mat g_scharrAbsGradient_X, g_scharrAbsGradient_Y;


//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
static void ShowHelpText( );
static void on_Canny(int, void*);//Canny\u908a\u7de3\u6aa2\u6e2c\u8996\u7a97\u6372\u8ef8\u7684\u56de\u8abf\u51fd\u6578
static void on_Sobel(int, void*);//Sobel\u908a\u7de3\u6aa2\u6e2c\u8996\u7a97\u6372\u8ef8\u7684\u56de\u8abf\u51fd\u6578
void Scharr( );//\u5c01\u88dd\u4e86Scharr\u908a\u7de3\u6aa2\u6e2c\u76f8\u95dc\u7a0b\u5f0f\u78bc\u7684\u51fd\u6578


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 2F");  

	//\u986f\u793a\u6b61\u8fce\u8a9e
	ShowHelpText();

	//\u8f09\u5165\u539f\u5716
	g_srcImage = imread("1.jpg");
	if( !g_srcImage.data ) { printf("Oh\uff0cno\uff0c\u8b80\u53d6srcImage\u932f\u8aa4~\uff01 \n"); return false; }

	//\u986f\u793a\u539f\u59cb\u5716
	namedWindow("\u3010\u539f\u59cb\u5716\u3011");
	imshow("\u3010\u539f\u59cb\u5716\u3011", g_srcImage);

	// \u5efa\u7acb\u8207src\u540c\u985e\u5225\u578b\u548c\u5927\u5c0f\u7684\u77e9\u9663(dst)
	g_dstImage.create( g_srcImage.size(), g_srcImage.type() );

	// \u5c07\u539f\u5716\u50cf\u8f49\u63db\u70ba\u7070\u5ea6\u5716\u50cf
	cvtColor( g_srcImage, g_srcGrayImage, CV_BGR2GRAY );

	// \u5efa\u7acb\u986f\u793a\u8996\u7a97
	namedWindow( "\u3010\u6548\u679c\u5716\u3011Canny\u908a\u7de3\u6aa2\u6e2c", CV_WINDOW_AUTOSIZE );
	namedWindow( "\u3010\u6548\u679c\u5716\u3011Sobel\u908a\u7de3\u6aa2\u6e2c", CV_WINDOW_AUTOSIZE );

	// \u5efa\u7acbtrackbar
	createTrackbar( "\u53c3\u6578\u503c\uff1a", "\u3010\u6548\u679c\u5716\u3011Canny\u908a\u7de3\u6aa2\u6e2c", &g_cannyLowThreshold, 120, on_Canny );
	createTrackbar( "\u53c3\u6578\u503c\uff1a", "\u3010\u6548\u679c\u5716\u3011Sobel\u908a\u7de3\u6aa2\u6e2c", &g_sobelKernelSize, 3, on_Sobel );

	// \u4f7f\u7528\u56de\u8abf\u51fd\u6578
	on_Canny(0, 0);
	on_Sobel(0, 0);

	//\u4f7f\u7528\u5c01\u88dd\u4e86Scharr\u908a\u7de3\u6aa2\u6e2c\u7a0b\u5f0f\u78bc\u7684\u51fd\u6578
	Scharr( );

	//\u8f2a\u8a62\u53d6\u5f97\u6309\u9375\u8a0a\u606f\uff0c\u82e5\u6309\u4e0bQ\uff0c\u7a0b\u5e8f\u9000\u51fa
	while((char(waitKey(1)) != 'q')) {}

	return 0;
}


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//		\u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c60\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf( "\n\n\t\u57f7\u884c\u6210\u529f\uff0c\u8acb\u8abf\u6574\u6372\u8ef8\u89c0\u5bdf\u5716\u50cf\u6548\u679c~\n\n"
		"\t\u6309\u4e0b\u201cq\u201d\u9375\u6642\uff0c\u7a0b\u5e8f\u9000\u51fa\u3002\n");
}


//-----------------------------------\u3010on_Canny( )\u51fd\u6578\u3011----------------------------------
//		\u63cf\u8ff0\uff1aCanny\u908a\u7de3\u6aa2\u6e2c\u8996\u7a97\u6372\u8ef8\u7684\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------------
void on_Canny(int, void*)
{
	// \u5148\u4f7f\u7528 3x3\u6838\u5fc3\u4f86\u964d\u566a
	blur( g_srcGrayImage, g_cannyDetectedEdges, Size(3,3) );

	// \u57f7\u884c\u6211\u5011\u7684Canny\u7b97\u5b50
	Canny( g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold*3, 3 );

	//\u5148\u5c07g_dstImage\u5167\u7684\u6240\u6709\u5143\u7d20\u8a2d\u5b9a\u70ba0 
	g_dstImage = Scalar::all(0);

	//\u4f7f\u7528Canny\u7b97\u5b50\u8f38\u51fa\u7684\u908a\u7de3\u5716g_cannyDetectedEdges\u4f5c\u70ba\u63a9\u78bc\uff0c\u4f86\u5c07\u539f\u5716g_srcImage\u62f7\u5230\u76ee\u6a19\u5716g_dstImage\u4e2d
	g_srcImage.copyTo( g_dstImage, g_cannyDetectedEdges);

	//\u986f\u793a\u6548\u679c\u5716
	imshow( "\u3010\u6548\u679c\u5716\u3011Canny\u908a\u7de3\u6aa2\u6e2c", g_dstImage );
}



//-----------------------------------\u3010on_Sobel( )\u51fd\u6578\u3011----------------------------------
//		\u63cf\u8ff0\uff1aSobel\u908a\u7de3\u6aa2\u6e2c\u8996\u7a97\u6372\u8ef8\u7684\u56de\u8abf\u51fd\u6578
//-----------------------------------------------------------------------------------------
void on_Sobel(int, void*)
{
	// \u6c42 X\u65b9\u5411\u68af\u5ea6
	Sobel( g_srcImage, g_sobelGradient_X, CV_16S, 1, 0, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );
	convertScaleAbs( g_sobelGradient_X, g_sobelAbsGradient_X );//\u8a08\u7b97\u7d55\u5c0d\u503c\uff0c\u4e26\u5c07\u7d50\u679c\u8f49\u63db\u62108\u4f4d

	// \u6c42Y\u65b9\u5411\u68af\u5ea6
	Sobel( g_srcImage, g_sobelGradient_Y, CV_16S, 0, 1, (2*g_sobelKernelSize+1), 1, 1, BORDER_DEFAULT );
	convertScaleAbs( g_sobelGradient_Y, g_sobelAbsGradient_Y );//\u8a08\u7b97\u7d55\u5c0d\u503c\uff0c\u4e26\u5c07\u7d50\u679c\u8f49\u63db\u62108\u4f4d

	// \u5408\u4e26\u68af\u5ea6
	addWeighted( g_sobelAbsGradient_X, 0.5, g_sobelAbsGradient_Y, 0.5, 0, g_dstImage );

	//\u986f\u793a\u6548\u679c\u5716
	imshow("\u3010\u6548\u679c\u5716\u3011Sobel\u908a\u7de3\u6aa2\u6e2c", g_dstImage); 

}


//-----------------------------------\u3010Scharr( )\u51fd\u6578\u3011----------------------------------
//		\u63cf\u8ff0\uff1a\u5c01\u88dd\u4e86Scharr\u908a\u7de3\u6aa2\u6e2c\u76f8\u95dc\u7a0b\u5f0f\u78bc\u7684\u51fd\u6578
//-----------------------------------------------------------------------------------------
void Scharr( )
{
	// \u6c42 X\u65b9\u5411\u68af\u5ea6
	Scharr( g_srcImage, g_scharrGradient_X, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( g_scharrGradient_X, g_scharrAbsGradient_X );//\u8a08\u7b97\u7d55\u5c0d\u503c\uff0c\u4e26\u5c07\u7d50\u679c\u8f49\u63db\u62108\u4f4d

	// \u6c42Y\u65b9\u5411\u68af\u5ea6
	Scharr( g_srcImage, g_scharrGradient_Y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT );
	convertScaleAbs( g_scharrGradient_Y, g_scharrAbsGradient_Y );//\u8a08\u7b97\u7d55\u5c0d\u503c\uff0c\u4e26\u5c07\u7d50\u679c\u8f49\u63db\u62108\u4f4d

	// \u5408\u4e26\u68af\u5ea6
	addWeighted( g_scharrAbsGradient_X, 0.5, g_scharrAbsGradient_Y, 0.5, 0, g_dstImage );

	//\u986f\u793a\u6548\u679c\u5716
	imshow("\u3010\u6548\u679c\u5716\u3011Scharr\u6ffe\u6ce2\u5668", g_dstImage); 
}
