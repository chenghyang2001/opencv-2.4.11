#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f79
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1aH-S\u4e8c\u7dad\u76f4\u689d\u5716\u7684\u7e6a\u88fd
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
//		 \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c79\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


//--------------------------------------\u3010main( )\u51fd\u6578\u3011-----------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( )
{

	//\u30101\u3011\u8f09\u5165\u6e90\u5716\uff0c\u8f49\u5316\u70baHSV\u984f\u8272\u6a21\u578b
	Mat srcImage, hsvImage;
	srcImage=imread("1.jpg");
	cvtColor(srcImage,hsvImage, CV_BGR2HSV);

	system("color 2F");
	ShowHelpText();

	//\u30102\u3011\u53c3\u6578\u6e96\u5099
	//\u5c07\u8272\u8abf\u91cf\u5316\u70ba30\u500b\u7b49\u7d1a\uff0c\u5c07\u98fd\u548c\u5ea6\u91cf\u5316\u70ba32\u500b\u7b49\u7d1a
	int hueBinNum = 30;//\u8272\u8abf\u7684\u76f4\u689d\u5716\u76f4\u689d\u6578\u91cf
	int saturationBinNum = 32;//\u98fd\u548c\u5ea6\u7684\u76f4\u689d\u5716\u76f4\u689d\u6578\u91cf
	int histSize[ ] = {hueBinNum, saturationBinNum};
	// \u5b9a\u7fa9\u8272\u8abf\u7684\u8b8a\u5316\u8303\u570d\u70ba0\u5230179
	float hueRanges[] = { 0, 180 };
	//\u5b9a\u7fa9\u98fd\u548c\u5ea6\u7684\u8b8a\u5316\u8303\u570d\u70ba0\uff08\u9ed1\u3001\u767d\u3001\u7070\uff09\u5230255\uff08\u7d14\u5149\u8b5c\u984f\u8272\uff09
	float saturationRanges[] = { 0, 256 };
	const float* ranges[] = { hueRanges, saturationRanges };
	MatND dstHist;
	//\u53c3\u6578\u6e96\u5099\uff0ccalcHist\u51fd\u6578\u4e2d\u5c07\u8a08\u7b97\u7b2c0\u901a\u9053\u548c\u7b2c1\u901a\u9053\u7684\u76f4\u689d\u5716
	int channels[] = {0, 1};

	//\u30103\u3011\u6b63\u5f0f\u4f7f\u7528calcHist\uff0c\u9032\u884c\u76f4\u689d\u5716\u8a08\u7b97
	calcHist( &hsvImage,//\u8f38\u5165\u7684\u6578\u7d44
		1, //\u6578\u7d44\u500b\u6578\u70ba1
		channels,//\u901a\u9053\u7d22\u5f15
		Mat(), //\u4e0d\u4f7f\u7528\u63a9\u819c
		dstHist, //\u8f38\u51fa\u7684\u76ee\u6a19\u76f4\u689d\u5716
		2, //\u9700\u8981\u8a08\u7b97\u7684\u76f4\u689d\u5716\u7684\u7dad\u5ea6\u70ba2
		histSize, //\u5b58\u653e\u6bcf\u500b\u7dad\u5ea6\u7684\u76f4\u689d\u5716\u5c3a\u5bf8\u7684\u6578\u7d44
		ranges,//\u6bcf\u4e00\u7dad\u6578\u503c\u7684\u53d6\u503c\u8303\u570d\u6578\u7d44
		true, // \u6307\u793a\u76f4\u689d\u5716\u662f\u5426\u5747\u52fb\u7684\u6a19\u8b58\u8868\uff0ctrue\u8868\u793a\u5747\u52fb\u7684\u76f4\u689d\u5716
		false );//\u7d2f\u8a08\u6a19\u8b58\u8868\uff0cfalse\u8868\u793a\u76f4\u689d\u5716\u5728\u8a2d\u5b9a\u968e\u6bb5\u6703\u88ab\u6e05\u96f6

	//\u30104\u3011\u70ba\u7e6a\u88fd\u76f4\u689d\u5716\u6e96\u5099\u53c3\u6578
	double maxValue=0;//\u6700\u5927\u503c
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);//\u67e5\u8a62\u6578\u7d44\u548c\u5b50\u6578\u7d44\u7684\u5168\u5c40\u6700\u5c0f\u503c\u548c\u6700\u5927\u503c\u5b58\u5165maxValue\u4e2d
	int scale = 10;
	Mat histImg = Mat::zeros(saturationBinNum*scale, hueBinNum*10, CV_8UC3);

	//\u30105\u3011\u96d9\u5c64\u5faa\u74b0\uff0c\u9032\u884c\u76f4\u689d\u5716\u7e6a\u88fd
	for( int hue = 0; hue < hueBinNum; hue++ )
		for( int saturation = 0; saturation < saturationBinNum; saturation++ )
		{
			float binValue = dstHist.at<float>(hue, saturation);//\u76f4\u689d\u5716\u7d44\u8ddd\u7684\u503c
			int intensity = cvRound(binValue*255/maxValue);//\u56fa\u5b9a\u5ea6

			//\u6b63\u5f0f\u9032\u884c\u7e6a\u88fd
			rectangle( histImg, Point(hue*scale, saturation*scale),
				Point( (hue+1)*scale - 1, (saturation+1)*scale - 1),
				Scalar::all(intensity),
				CV_FILLED );
		}

		//\u30106\u3011\u986f\u793a\u6548\u679c\u5716
		imshow( "\u7d20\u6750\u5716", srcImage );
		imshow( "H-S \u76f4\u689d\u5716", histImg );

		waitKey();
}
