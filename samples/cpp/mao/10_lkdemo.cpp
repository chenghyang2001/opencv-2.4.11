#include <stdio.h>
//:read /home/peter/mao/10_lkdemo.cpp

//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序10
//		程序描述：來自OpenCV安裝目錄下Samples文件夾中的官方範例程序-點追蹤技術示範
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------

//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//-------------------------------------------------------------------------------------------------
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <ctype.h>

using namespace cv;
using namespace std;



//--------------------------------【help( )函數】----------------------------------------------
//		描述：輸出說明訊息
//-------------------------------------------------------------------------------------------------
static void help()
{
	//輸出歡迎訊息和OpenCV版本
	cout <<"\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n"
		<<"\n\n\t\t\t此為本書OpenCV2版的第10個配套範例程序\n"
		<<	"\n\n\t\t\t   現在使用的OpenCV版本為：" << CV_VERSION 
		<<"\n\n  ----------------------------------------------------------------------------" ;
	cout	<< "\n\n\t該Demo示範了 Lukas-Kanade基于光流的lkdemo\n";
	cout << "\n\t程序預設從攝影機讀入視訊，可以按需改為從視訊文件讀入圖像\n";
	cout << "\n\t操作說明: \n"
		"\t\t通過點擊在圖像中新增/刪除特征點\n" 
		"\t\tESC - 退出程序\n"
		"\t\tr -自動進行追蹤\n"
		"\t\tc - 刪除所有點\n"
		"\t\tn - 開/光-夜晚模式\n"<< endl;
}

Point2f point;
bool addRemovePt = false;

//--------------------------------【onMouse( )回調函數】------------------------------------
//		描述：滑鼠操作回調 
//-------------------------------------------------------------------------------------------------
static void onMouse( int event, int x, int y, int /*flags*/, void* /*param*/ )
{
	if( event == CV_EVENT_LBUTTONDOWN )
	{
		point = Point2f((float)x, (float)y);
		addRemovePt = true;
	}
}

//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-------------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	help();

	VideoCapture cap;
	TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03);
	Size subPixWinSize(10,10), winSize(31,31);

	const int MAX_COUNT = 500;
	bool needToInit = false;
	bool nightMode = false;

	cap.open(0);

	if( !cap.isOpened() )
	{
		cout << "Could not initialize capturing...\n";
		return 0;
	}

	namedWindow( "LK Demo", 1 );
	setMouseCallback( "LK Demo", onMouse, 0 );

	Mat gray, prevGray, image;
	vector<Point2f> points[2];

	for(;;)
	{
		Mat frame;
		cap >> frame;
		if( frame.empty() )
			break;

		frame.copyTo(image);
		cvtColor(image, gray, COLOR_BGR2GRAY);

		if( nightMode )
			image = Scalar::all(0);

		if( needToInit )
		{
			// 自動初始化
			goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
			cornerSubPix(gray, points[1], subPixWinSize, Size(-1,-1), termcrit);
			addRemovePt = false;
		}
		else if( !points[0].empty() )
		{
			vector<uchar> status;
			vector<float> err;
			if(prevGray.empty())
				gray.copyTo(prevGray);
			calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize,
				3, termcrit, 0, 0.001);
			size_t i, k;
			for( i = k = 0; i < points[1].size(); i++ )
			{
				if( addRemovePt )
				{
					if( norm(point - points[1][i]) <= 5 )
					{
						addRemovePt = false;
						continue;
					}
				}

				if( !status[i] )
					continue;

				points[1][k++] = points[1][i];
				circle( image, points[1][i], 3, Scalar(0,255,0), -1, 8);
			}
			points[1].resize(k);
		}

		if( addRemovePt && points[1].size() < (size_t)MAX_COUNT )
		{
			vector<Point2f> tmp;
			tmp.push_back(point);
			cornerSubPix( gray, tmp, winSize, cvSize(-1,-1), termcrit);
			points[1].push_back(tmp[0]);
			addRemovePt = false;
		}

		needToInit = false;
		imshow("LK Demo", image);

		char c = (char)waitKey(10);
		if( c == 27 )
			break;
		switch( c )
		{
		case 'r':
			needToInit = true;
			break;
		case 'c':
			points[0].clear();
			points[1].clear();
			break;
		case 'n':
			nightMode = !nightMode;
			break;
		}

		std::swap(points[1], points[0]);
		cv::swap(prevGray, gray);
	}

	return 0;
}
