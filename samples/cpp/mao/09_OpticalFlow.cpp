#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/09_OpticalFlow.cpp



/************************************************************************
* Copyright(c) 2011  Yang Xian
* All rights reserved.
*
* File:	opticalFlow.cpp
* Brief: lk光流法做運動目標檢測
* Version: 1.0
* Author: Yang Xian
* Email: xyang2011@sinano.ac.cn
* Date:	2011/11/18
* History:
************************************************************************/


//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//-------------------------------------------------------------------------------------------------
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;





//-----------------------------------【全局函數宣告】-----------------------------------------
//		描述：宣告全局函數
//-------------------------------------------------------------------------------------------------
void tracking(Mat &frame, Mat &output);
bool addNewPoints();
bool acceptTrackedPoint(int i);

//-----------------------------------【全局變數宣告】-----------------------------------------
//		描述：宣告全局變數
//-------------------------------------------------------------------------------------------------
string window_name = "optical flow tracking";
Mat gray;	// 現在圖形
Mat gray_prev;	// 預測圖形
vector<Point2f> points[2];	// point0為特征點的原來位置，point1為特征點的新位置
vector<Point2f> initial;	// 初始化跟蹤點的位置
vector<Point2f> features;	// 檢測的特征
int maxCount = 500;	// 檢測的最大特征數
double qLevel = 0.01;	// 特征檢測的等級
double minDist = 10.0;	// 兩特征點之間的最小距離
vector<uchar> status;	// 跟蹤特征的狀態，特征的流發現為1，否則為0
vector<float> err;


//--------------------------------【help( )函數】----------------------------------------------
//		描述：輸出說明訊息
//-------------------------------------------------------------------------------------------------
static void help()
{
	//輸出歡迎訊息和OpenCV版本
	cout <<"\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n"
		<<"\n\n\t\t\t此為本書OpenCV2版的第9個配套範例程序\n"
		<<	"\n\n\t\t\t   現在使用的OpenCV版本為：" << CV_VERSION 
		<<"\n\n  ----------------------------------------------------------------------------" ;
}


//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-------------------------------------------------------------------------------------------------
int main()
{

	Mat frame;
	Mat result;

//        VideoCapture capture("1.avi");
	VideoCapture capture("/home/peter/opencv-2.4.11/samples/cpp/mao/1.avi");

	help();
	if(capture.isOpened())	// 攝影機讀取文件開關
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
// brief: 跟蹤
// parameter: frame	輸入的視訊幅
//			  output 有跟蹤結果的視訊幅
// return: void
//-------------------------------------------------------------------------------------------------
void tracking(Mat &frame, Mat &output)
{
	cvtColor(frame, gray, CV_BGR2GRAY);
	frame.copyTo(output);
	// 新增特征點
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
	// l-k光流法運動估計
	calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);
	// 去掉一些不好的特征點
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
	// 顯示特征點和運動軌跡
	for (size_t i=0; i<points[1].size(); i++)
	{
		line(output, initial[i], points[1][i], Scalar(0, 0, 255));
		circle(output, points[1][i], 3, Scalar(0, 255, 0), -1);
	}

	// 把現在跟蹤結果作為下一此參考
	swap(points[1], points[0]);
	swap(gray_prev, gray);

	imshow(window_name, output);
	moveWindow(window_name, 100,100);
}

//-------------------------------------------------------------------------------------------------
// function: addNewPoints
// brief: 檢測新點是否應該被新增
// parameter:
// return: 是否被新增標志
//-------------------------------------------------------------------------------------------------
bool addNewPoints()
{
	return points[0].size() <= 10;
}

//-------------------------------------------------------------------------------------------------
// function: acceptTrackedPoint
// brief: 決定哪些跟蹤點被接受
// parameter:
// return:
//-------------------------------------------------------------------------------------------------
bool acceptTrackedPoint(int i)
{
	return status[i] && ((abs(points[0][i].x - points[1][i].x) + abs(points[0][i].y - points[1][i].y)) > 2);
}


