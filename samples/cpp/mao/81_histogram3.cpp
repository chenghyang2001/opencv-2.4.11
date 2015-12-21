#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f81
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1a\u7e6a\u88fdRGB\u4e09\u8272\u5206\u91cf\u7684\u76f4\u689d\u5716
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6a94\u6848\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6a94\u6848\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;  



//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011-----------------------------
//		 \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c81\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


//--------------------------------------\u3010main( )\u51fd\u6578\u3011-----------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main(  )
{

	//\u30101\u3011\u8f09\u5165\u7d20\u6750\u5716\u4e26\u986f\u793a
	Mat srcImage;
	srcImage=imread("1.jpg");
	imshow( "\u7d20\u6750\u5716", srcImage );

	system("color 3F");
	ShowHelpText();

	//\u30102\u3011\u53c3\u6578\u6e96\u5099
	int bins = 256;
	int hist_size[] = {bins};
	float range[] = { 0, 256 };
	const float* ranges[] = { range};
	MatND redHist,grayHist,blueHist;
	int channels_r[] = {0};

	//\u30103\u3011\u9032\u884c\u76f4\u689d\u5716\u7684\u8a08\u7b97\uff08\u7d05\u8272\u5206\u91cf\u90e8\u5206\uff09
	calcHist( &srcImage, 1, channels_r, Mat(), //\u4e0d\u4f7f\u7528\u63a9\u819c
		redHist, 1, hist_size, ranges,
		true, false );

	//\u30104\u3011\u9032\u884c\u76f4\u689d\u5716\u7684\u8a08\u7b97\uff08\u7da0\u8272\u5206\u91cf\u90e8\u5206\uff09
	int channels_g[] = {1};
	calcHist( &srcImage, 1, channels_g, Mat(), // do not use mask
		grayHist, 1, hist_size, ranges,
		true, // the histogram is uniform
		false );

	//\u30105\u3011\u9032\u884c\u76f4\u689d\u5716\u7684\u8a08\u7b97\uff08\u85cd\u8272\u5206\u91cf\u90e8\u5206\uff09
	int channels_b[] = {2};
	calcHist( &srcImage, 1, channels_b, Mat(), // do not use mask
		blueHist, 1, hist_size, ranges,
		true, // the histogram is uniform
		false );

	//-----------------------\u7e6a\u88fd\u51fa\u4e09\u8272\u76f4\u689d\u5716------------------------
	//\u53c3\u6578\u6e96\u5099
	double maxValue_red,maxValue_green,maxValue_blue;
	minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
	minMaxLoc(grayHist, 0, &maxValue_green, 0, 0);
	minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
	int scale = 1;
	int histHeight=256;
	Mat histImage = Mat::zeros(histHeight,bins*3, CV_8UC3);

	//\u6b63\u5f0f\u958b\u59cb\u7e6a\u88fd
	for(int i=0;i<bins;i++)
	{
		//\u53c3\u6578\u6e96\u5099
		float binValue_red = redHist.at<float>(i); 
		float binValue_green = grayHist.at<float>(i);
		float binValue_blue = blueHist.at<float>(i);
		int intensity_red = cvRound(binValue_red*histHeight/maxValue_red);  //\u8981\u7e6a\u88fd\u7684\u9ad8\u5ea6
		int intensity_green = cvRound(binValue_green*histHeight/maxValue_green);  //\u8981\u7e6a\u88fd\u7684\u9ad8\u5ea6
		int intensity_blue = cvRound(binValue_blue*histHeight/maxValue_blue);  //\u8981\u7e6a\u88fd\u7684\u9ad8\u5ea6

		//\u7e6a\u88fd\u7d05\u8272\u5206\u91cf\u7684\u76f4\u689d\u5716
		rectangle(histImage,Point(i*scale,histHeight-1),
			Point((i+1)*scale - 1, histHeight - intensity_red),
			CV_RGB(255,0,0));

		//\u7e6a\u88fd\u7da0\u8272\u5206\u91cf\u7684\u76f4\u689d\u5716
		rectangle(histImage,Point((i+bins)*scale,histHeight-1),
			Point((i+bins+1)*scale - 1, histHeight - intensity_green),
			CV_RGB(0,255,0));

		//\u7e6a\u88fd\u85cd\u8272\u5206\u91cf\u7684\u76f4\u689d\u5716
		rectangle(histImage,Point((i+bins*2)*scale,histHeight-1),
			Point((i+bins*2+1)*scale - 1, histHeight - intensity_blue),
			CV_RGB(0,0,255));

	}

	//\u5728\u8996\u7a97\u4e2d\u986f\u793a\u51fa\u7e6a\u88fd\u597d\u7684\u76f4\u689d\u5716
	imshow( "\u5716\u50cf\u7684RGB\u76f4\u689d\u5716", histImage );
	waitKey(0);
	return 0;
}
