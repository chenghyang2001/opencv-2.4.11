#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f95
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1aORB\u7684\u95dc\u9375\u9ede\u548c\u63cf\u8ff0\u8868\u7684\u63d0\u53d6\uff0c\u4f7f\u7528FLANN-LSH\u9032\u884c\u6bd4\u5c0d
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
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>
using namespace cv;
using namespace std;



//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c72\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf("\n\t\u6b61\u8fce\u4f86\u5230\u3010ORB\u7b97\u6cd5\u63cf\u8ff0\u63d0\u53d6\uff0c\u914d\u5408FLANN-LSH\u9032\u884c\u6bd4\u5c0d\u3011\u7bc4\u4f8b\u7a0b\u5e8f\n"); 
	printf( "\n\n\t\u6309\u9375\u64cd\u4f5c\u8aaa\u660e: \n\n" 
		"\t\t\u9375\u76e4\u6309\u9375\u3010ESC\u3011- \u9000\u51fa\u7a0b\u5e8f\n" );
}


//--------------------------------------\u3010main( )\u51fd\u6578\u3011-----------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main(	) 
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 2F"); 

	//\u30100\u3011\u986f\u793a\u8aaa\u660e\u6587\u5b57
	ShowHelpText();

	//\u30100\u3011\u8f09\u5165\u6e90\u5716\uff0c\u986f\u793a\u4e26\u8f49\u5316\u70ba\u7070\u5ea6\u5716
	Mat srcImage = imread("1.jpg");
	imshow("\u539f\u59cb\u5716",srcImage);
	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	//------------------\u6aa2\u6e2cSIFT\u7279\u5fb5\u9ede\u4e26\u5728\u5716\u50cf\u4e2d\u63d0\u53d6\u7269\u9ad4\u7684\u63cf\u8ff0\u8868----------------------

	//\u30101\u3011\u53c3\u6578\u5b9a\u7fa9
	OrbFeatureDetector featureDetector;
	vector<KeyPoint> keyPoints;
	Mat descriptors;

	//\u30102\u3011\u4f7f\u7528detect\u51fd\u6578\u6aa2\u6e2c\u51fa\u7279\u5fb5\u95dc\u9375\u9ede\uff0c\u5132\u5b58\u5728vector\u5bbf\u4e3b\u4e2d
	featureDetector.detect(grayImage, keyPoints);

	//\u30103\u3011\u8a08\u7b97\u63cf\u8ff0\u8868\uff08\u7279\u5fb5\u5411\u91cf\uff09
	OrbDescriptorExtractor featureExtractor;
	featureExtractor.compute(grayImage, keyPoints, descriptors);

	//\u30104\u3011\u57fa\u4e8eFLANN\u7684\u63cf\u8ff0\u8868\u5c0d\u8c61\u6bd4\u5c0d
	flann::Index flannIndex(descriptors, flann::LshIndexParams(12, 20, 2), cvflann::FLANN_DIST_HAMMING);

	//\u30105\u3011\u521d\u59cb\u5316\u8996\u8a0a\u63a1\u96c6\u5c0d\u8c61
	VideoCapture cap(0);

	unsigned int frameCount = 0;//\u5e45\u6578

	//\u30106\u3011\u8f2a\u8a62\uff0c\u76f4\u5230\u6309\u4e0bESC\u9375\u9000\u51fa\u5faa\u74b0
	while(1)
	{
		double time0 = static_cast<double>(getTickCount( ));//\u8a18\u9304\u8d77\u59cb\u6642\u9593
		Mat  captureImage, captureImage_gray;//\u5b9a\u7fa9\u5169\u500bMat\u8b8a\u6578\uff0c\u7528\u4e8e\u8996\u8a0a\u63a1\u96c6
		cap >>  captureImage;//\u63a1\u96c6\u8996\u8a0a\u5e45
		if( captureImage.empty())//\u63a1\u96c6\u70ba\u7a7a\u7684\u8655\u7406
			continue;

		//\u8f49\u5316\u5716\u50cf\u5230\u7070\u5ea6
		cvtColor( captureImage, captureImage_gray, CV_BGR2GRAY);//\u63a1\u96c6\u7684\u8996\u8a0a\u5e45\u8f49\u5316\u70ba\u7070\u5ea6\u5716

		//\u30107\u3011\u6aa2\u6e2cSIFT\u95dc\u9375\u9ede\u4e26\u63d0\u53d6\u6e2c\u8a66\u5716\u50cf\u4e2d\u7684\u63cf\u8ff0\u8868
		vector<KeyPoint> captureKeyPoints;
		Mat captureDescription;

		//\u30108\u3011\u4f7f\u7528detect\u51fd\u6578\u6aa2\u6e2c\u51fa\u7279\u5fb5\u95dc\u9375\u9ede\uff0c\u5132\u5b58\u5728vector\u5bbf\u4e3b\u4e2d
		featureDetector.detect(captureImage_gray, captureKeyPoints);

		//\u30109\u3011\u8a08\u7b97\u63cf\u8ff0\u8868
		featureExtractor.compute(captureImage_gray, captureKeyPoints, captureDescription);

		//\u301010\u3011\u6bd4\u5c0d\u548c\u6e2c\u8a66\u63cf\u8ff0\u8868\uff0c\u53d6\u5f97\u5169\u500b\u6700\u9130\u8fd1\u7684\u63cf\u8ff0\u8868
		Mat matchIndex(captureDescription.rows, 2, CV_32SC1), matchDistance(captureDescription.rows, 2, CV_32FC1);
		flannIndex.knnSearch(captureDescription, matchIndex, matchDistance, 2, flann::SearchParams());//\u4f7f\u7528K\u9130\u8fd1\u7b97\u6cd5

		//\u301011\u3011\u6839\u64da\u52de\u6c0f\u7b97\u6cd5\uff08Lowe's algorithm\uff09\u9078\u51fa\u512a\u79c0\u7684\u6bd4\u5c0d
		vector<DMatch> goodMatches;
		for(int i = 0; i < matchDistance.rows; i++) 
		{
			if(matchDistance.at<float>(i, 0) < 0.6 * matchDistance.at<float>(i, 1)) 
			{
				DMatch dmatches(i, matchIndex.at<int>(i, 0), matchDistance.at<float>(i, 0));
				goodMatches.push_back(dmatches);
			}
		}

		//\u301012\u3011\u7e6a\u88fd\u4e26\u986f\u793a\u6bd4\u5c0d\u8996\u7a97
		Mat resultImage;
		drawMatches( captureImage, captureKeyPoints, srcImage, keyPoints, goodMatches, resultImage);
		imshow("\u6bd4\u5c0d\u8996\u7a97", resultImage);

		//\u301013\u3011\u986f\u793a\u5e45\u7387
		cout << ">\u5e45\u7387= " << getTickFrequency() / (getTickCount() - time0) << endl;

		//\u6309\u4e0bESC\u9375\uff0c\u5247\u7a0b\u5e8f\u9000\u51fa
		if(char(waitKey(1)) == 27) break;
	}

	return 0;
}


