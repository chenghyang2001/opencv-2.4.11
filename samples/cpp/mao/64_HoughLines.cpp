#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f64
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u970d\u592b\u7dda\u8b8a\u63db\u7d9c\u5408\u7bc4\u4f8b
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


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage,g_midImage;//\u539f\u59cb\u5716\u3001\u4e2d\u9593\u5716\u548c\u6548\u679c\u5716
vector<Vec4i> g_lines;//\u5b9a\u7fa9\u4e00\u500b\u77e2\u91cf\u7d50\u69cbg_lines\u7528\u4e8e\u5b58\u653e\u5f97\u5230\u7684\u7dda\u6bb5\u77e2\u91cf\u96c6\u5408
//\u8b8a\u6578\u63a5\u6536\u7684TrackBar\u4f4d\u7f6e\u53c3\u6578
int g_nthreshold=100;

//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------

static void on_HoughLines(int, void*);//\u56de\u8abf\u51fd\u6578
static void ShowHelpText();


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-----------------------------------------------------------------------------------------------
int main( )
{
	//\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 4F");  

	ShowHelpText();

	//\u8f09\u5165\u539f\u59cb\u5716\u548cMat\u8b8a\u6578\u5b9a\u7fa9   
	Mat g_srcImage = imread("1.jpg");  //\u5c08\u6848\u76ee\u9304\u4e0b\u61c9\u8a72\u6709\u4e00\u5f35\u540d\u70ba1.jpg\u7684\u7d20\u6750\u5716

	//\u986f\u793a\u539f\u59cb\u5716  
	imshow("\u3010\u539f\u59cb\u5716\u3011", g_srcImage);  

	//\u5efa\u7acb\u6372\u8ef8
	namedWindow("\u3010\u6548\u679c\u5716\u3011",1);
	createTrackbar("\u503c", "\u3010\u6548\u679c\u5716\u3011",&g_nthreshold,200,on_HoughLines);

	//\u9032\u884c\u908a\u7de3\u6aa2\u6e2c\u548c\u8f49\u5316\u70ba\u7070\u5ea6\u5716
	Canny(g_srcImage, g_midImage, 50, 200, 3);//\u9032\u884c\u4e00\u6b21canny\u908a\u7de3\u6aa2\u6e2c
	cvtColor(g_midImage,g_dstImage, CV_GRAY2BGR);//\u8f49\u5316\u908a\u7de3\u6aa2\u6e2c\u5f8c\u7684\u5716\u70ba\u7070\u5ea6\u5716

	//\u4f7f\u7528\u4e00\u6b21\u56de\u8abf\u51fd\u6578\uff0c\u4f7f\u7528\u4e00\u6b21HoughLinesP\u51fd\u6578
	on_HoughLines(g_nthreshold,0);
	HoughLinesP(g_midImage, g_lines, 1, CV_PI/180, 80, 50, 10 );

	//\u986f\u793a\u6548\u679c\u5716  
	imshow("\u3010\u6548\u679c\u5716\u3011", g_dstImage);  


	waitKey(0);  

	return 0;  

}


//-----------------------------------\u3010on_HoughLines( )\u51fd\u6578\u3011--------------------------------
//		\u63cf\u8ff0\uff1a\u3010\u9802\u5e3d\u904b\u7b97/\u9ed1\u5e3d\u904b\u7b97\u3011\u8996\u7a97\u7684\u56de\u8abf\u51fd\u6578
//----------------------------------------------------------------------------------------------
static void on_HoughLines(int, void*)
{
	//\u5b9a\u7fa9\u5c40\u90e8\u8b8a\u6578\u5132\u5b58\u5168\u5c40\u8b8a\u6578
	Mat dstImage=g_dstImage.clone();
	Mat midImage=g_midImage.clone();

	//\u4f7f\u7528HoughLinesP\u51fd\u6578
	vector<Vec4i> mylines;
	HoughLinesP(midImage, mylines, 1, CV_PI/180, g_nthreshold+1, 50, 10 );

	//\u5faa\u74b0\u700f\u89bd\u7e6a\u88fd\u6bcf\u4e00\u689d\u7dda\u6bb5
	for( size_t i = 0; i < mylines.size(); i++ )
	{
		Vec4i l = mylines[i];
		line( dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23,180,55), 1, CV_AA);
	}
	//\u986f\u793a\u5716\u50cf
	imshow("\u3010\u6548\u679c\u5716\u3011",dstImage);
}

//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//		\u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c64\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf("\n\n\n\t\u8acb\u8abf\u6574\u6372\u8ef8\u89c0\u5bdf\u5716\u50cf\u6548\u679c~\n\n");


}
