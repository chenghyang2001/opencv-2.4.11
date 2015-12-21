#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f92
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1aFLANN\u7d50\u5408SURF\u9032\u884c\u95dc\u9375\u9ede\u7684\u63cf\u8ff0\u548c\u6bd4\u5c0d
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


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011-----------------------------
//		 \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c92\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


//--------------------------------------\u3010main( )\u51fd\u6578\u3011-----------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( ) 
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 6F"); 

	void ShowHelpText();

	//\u30101\u3011\u8f09\u5165\u5716\u50cf\u3001\u986f\u793a\u4e26\u8f49\u5316\u70ba\u7070\u5ea6\u5716
	Mat trainImage = imread("1.jpg"), trainImage_gray;
	imshow("\u539f\u59cb\u5716",trainImage);
	cvtColor(trainImage, trainImage_gray, CV_BGR2GRAY);

	//\u30102\u3011\u6aa2\u6e2cSurf\u95dc\u9375\u9ede\u3001\u63d0\u53d6\u8a13\u7df4\u5716\u50cf\u63cf\u8ff0\u8868
	vector<KeyPoint> train_keyPoint;
	Mat trainDescriptor;
	SurfFeatureDetector featureDetector(80);
	featureDetector.detect(trainImage_gray, train_keyPoint);
	SurfDescriptorExtractor featureExtractor;
	featureExtractor.compute(trainImage_gray, train_keyPoint, trainDescriptor);

	//\u30103\u3011\u5efa\u7acb\u57fa\u4e8eFLANN\u7684\u63cf\u8ff0\u8868\u6bd4\u5c0d\u5c0d\u8c61
	FlannBasedMatcher matcher;
	vector<Mat> train_desc_collection(1, trainDescriptor);
	matcher.add(train_desc_collection);
	matcher.train();

	//\u30104\u3011\u5efa\u7acb\u8996\u8a0a\u5c0d\u8c61\u3001\u5b9a\u7fa9\u5e45\u7387
	VideoCapture cap(0);
	unsigned int frameCount = 0;//\u5e45\u6578

	//\u30105\u3011\u4e0d\u65b7\u5faa\u74b0\uff0c\u76f4\u5230q\u9375\u88ab\u6309\u4e0b
	while(char(waitKey(1)) != 'q')
	{
		//<1>\u53c3\u6578\u8a2d\u5b9a
		int64 time0 = getTickCount();
		Mat testImage, testImage_gray;
		cap >> testImage;//\u63a1\u96c6\u8996\u8a0a\u5230testImage\u4e2d
		if(testImage.empty())
			continue;

		//<2>\u8f49\u5316\u5716\u50cf\u5230\u7070\u5ea6
		cvtColor(testImage, testImage_gray, CV_BGR2GRAY);

		//<3>\u6aa2\u6e2cS\u95dc\u9375\u9ede\u3001\u63d0\u53d6\u6e2c\u8a66\u5716\u50cf\u63cf\u8ff0\u8868
		vector<KeyPoint> test_keyPoint;
		Mat testDescriptor;
		featureDetector.detect(testImage_gray, test_keyPoint);
		featureExtractor.compute(testImage_gray, test_keyPoint, testDescriptor);

		//<4>\u6bd4\u5c0d\u8a13\u7df4\u548c\u6e2c\u8a66\u63cf\u8ff0\u8868
		vector<vector<DMatch> > matches;
		matcher.knnMatch(testDescriptor, matches, 2);

		// <5>\u6839\u64da\u52de\u6c0f\u7b97\u6cd5\uff08Lowe's algorithm\uff09\uff0c\u5f97\u5230\u512a\u79c0\u7684\u6bd4\u5c0d\u9ede
		vector<DMatch> goodMatches;
		for(unsigned int i = 0; i < matches.size(); i++)
		{
			if(matches[i][0].distance < 0.6 * matches[i][1].distance)
				goodMatches.push_back(matches[i][0]);
		}

		//<6>\u7e6a\u88fd\u6bd4\u5c0d\u9ede\u4e26\u986f\u793a\u8996\u7a97
		Mat dstImage;
		drawMatches(testImage, test_keyPoint, trainImage, train_keyPoint, goodMatches, dstImage);
		imshow("\u6bd4\u5c0d\u8996\u7a97", dstImage);

		//<7>\u8f38\u51fa\u5e45\u7387\u8a0a\u606f
		cout << "\u73fe\u5728\u5e45\u7387\u70ba\uff1a" << getTickFrequency() / (getTickCount() - time0) << endl;
	}

	return 0;
}
