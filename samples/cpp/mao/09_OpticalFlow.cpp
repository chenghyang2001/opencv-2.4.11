#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f09
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u4f86\u81eaOpenCV\u5b89\u88dd\u76ee\u9304\u4e0bSamples\u6587\u4ef6\u593e\u4e2d\u7684\u5b98\u65b9\u7bc4\u4f8b\u7a0b\u5e8f-\u5229\u7528\u5149\u6d41\u6cd5\u9032\u884c\u904b\u52d5\u76ee\u6a19\u6aa2\u6e2c
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------


/************************************************************************
* Copyright(c) 2011  Yang Xian
* All rights reserved.
*
* File:	opticalFlow.cpp
* Brief: lk\u5149\u6d41\u6cd5\u505a\u904b\u52d5\u76ee\u6a19\u6aa2\u6e2c
* Version: 1.0
* Author: Yang Xian
* Email: xyang2011@sinano.ac.cn
* Date:	2011/11/18
* History:
************************************************************************/


//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//-------------------------------------------------------------------------------------------------
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;





//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u3011-----------------------------------------
//		\u63cf\u8ff0\uff1a\u5ba3\u544a\u5168\u5c40\u51fd\u6578
//-------------------------------------------------------------------------------------------------
void tracking(Mat &frame, Mat &output);
bool addNewPoints();
bool acceptTrackedPoint(int i);

//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u3011-----------------------------------------
//		\u63cf\u8ff0\uff1a\u5ba3\u544a\u5168\u5c40\u8b8a\u6578
//-------------------------------------------------------------------------------------------------
string window_name = "optical flow tracking";
Mat gray;	// \u73fe\u5728\u5716\u5f62
Mat gray_prev;	// \u9810\u6e2c\u5716\u5f62
vector<Point2f> points[2];	// point0\u70ba\u7279\u5f81\u9ede\u7684\u539f\u4f86\u4f4d\u7f6e\uff0cpoint1\u70ba\u7279\u5f81\u9ede\u7684\u65b0\u4f4d\u7f6e
vector<Point2f> initial;	// \u521d\u59cb\u5316\u8ddf\u8e64\u9ede\u7684\u4f4d\u7f6e
vector<Point2f> features;	// \u6aa2\u6e2c\u7684\u7279\u5f81
int maxCount = 500;	// \u6aa2\u6e2c\u7684\u6700\u5927\u7279\u5f81\u6578
double qLevel = 0.01;	// \u7279\u5f81\u6aa2\u6e2c\u7684\u7b49\u7d1a
double minDist = 10.0;	// \u5169\u7279\u5f81\u9ede\u4e4b\u9593\u7684\u6700\u5c0f\u8ddd\u96e2
vector<uchar> status;	// \u8ddf\u8e64\u7279\u5f81\u7684\u72c0\u614b\uff0c\u7279\u5f81\u7684\u6d41\u767c\u73fe\u70ba1\uff0c\u5426\u5247\u70ba0
vector<float> err;


//--------------------------------\u3010help( )\u51fd\u6578\u3011----------------------------------------------
//		\u63cf\u8ff0\uff1a\u8f38\u51fa\u8aaa\u660e\u8a0a\u606f
//-------------------------------------------------------------------------------------------------
static void help()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	cout <<"\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n"
		<<"\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c9\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n"
		<<	"\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" << CV_VERSION 
		<<"\n\n  ----------------------------------------------------------------------------" ;
}


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-------------------------------------------------------------------------------------------------
int main()
{

	Mat frame;
	Mat result;

	VideoCapture capture("1.avi");

	help();
	if(capture.isOpened())	// \u651d\u5f71\u6a5f\u8b80\u53d6\u6587\u4ef6\u958b\u95dc
	{
		while(true)
		{
			capture >> frame;

			if(!frame.empty())
			{ 
				tracking(frame, result);
			}
			else
			{ 
				printf(" --(!) No captured frame -- Break!");
				break;
			}

			int c = waitKey(50);
			if( (char)c == 27 )
			{
				break; 
			} 
		}
	}
	return 0;
}

//-------------------------------------------------------------------------------------------------
// function: tracking
// brief: \u8ddf\u8e64
// parameter: frame	\u8f38\u5165\u7684\u8996\u8a0a\u5e45
//			  output \u6709\u8ddf\u8e64\u7d50\u679c\u7684\u8996\u8a0a\u5e45
// return: void
//-------------------------------------------------------------------------------------------------
void tracking(Mat &frame, Mat &output)
{
	cvtColor(frame, gray, CV_BGR2GRAY);
	frame.copyTo(output);
	// \u65b0\u589e\u7279\u5f81\u9ede
	if (addNewPoints())
	{
		goodFeaturesToTrack(gray, features, maxCount, qLevel, minDist);
		points[0].insert(points[0].end(), features.begin(), features.end());
		initial.insert(initial.end(), features.begin(), features.end());
	}

	if (gray_prev.empty())
	{
		gray.copyTo(gray_prev);
	}
	// l-k\u5149\u6d41\u6cd5\u904b\u52d5\u4f30\u8a08
	calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);
	// \u53bb\u6389\u4e00\u4e9b\u4e0d\u597d\u7684\u7279\u5f81\u9ede
	int k = 0;
	for (size_t i=0; i<points[1].size(); i++)
	{
		if (acceptTrackedPoint(i))
		{
			initial[k] = initial[i];
			points[1][k++] = points[1][i];
		}
	}
	points[1].resize(k);
	initial.resize(k);
	// \u986f\u793a\u7279\u5f81\u9ede\u548c\u904b\u52d5\u8ecc\u8de1
	for (size_t i=0; i<points[1].size(); i++)
	{
		line(output, initial[i], points[1][i], Scalar(0, 0, 255));
		circle(output, points[1][i], 3, Scalar(0, 255, 0), -1);
	}

	// \u628a\u73fe\u5728\u8ddf\u8e64\u7d50\u679c\u4f5c\u70ba\u4e0b\u4e00\u6b64\u53c3\u8003
	swap(points[1], points[0]);
	swap(gray_prev, gray);

	imshow(window_name, output);
}

//-------------------------------------------------------------------------------------------------
// function: addNewPoints
// brief: \u6aa2\u6e2c\u65b0\u9ede\u662f\u5426\u61c9\u8a72\u88ab\u65b0\u589e
// parameter:
// return: \u662f\u5426\u88ab\u65b0\u589e\u6a19\u5fd7
//-------------------------------------------------------------------------------------------------
bool addNewPoints()
{
	return points[0].size() <= 10;
}

//-------------------------------------------------------------------------------------------------
// function: acceptTrackedPoint
// brief: \u6c7a\u5b9a\u54ea\u4e9b\u8ddf\u8e64\u9ede\u88ab\u63a5\u53d7
// parameter:
// return:
//-------------------------------------------------------------------------------------------------
bool acceptTrackedPoint(int i)
{
	return status[i] && ((abs(points[0][i].x - points[1][i].x) + abs(points[0][i].y - points[1][i].y)) > 2);
}


