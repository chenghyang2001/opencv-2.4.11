#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f10
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u4f86\u81eaOpenCV\u5b89\u88dd\u76ee\u9304\u4e0bSamples\u6587\u4ef6\u593e\u4e2d\u7684\u5b98\u65b9\u7bc4\u4f8b\u7a0b\u5e8f-\u9ede\u8ffd\u8e64\u6280\u8853\u793a\u7bc4
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------

//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//-------------------------------------------------------------------------------------------------
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <ctype.h>

using namespace cv;
using namespace std;



//--------------------------------\u3010help( )\u51fd\u6578\u3011----------------------------------------------
//		\u63cf\u8ff0\uff1a\u8f38\u51fa\u8aaa\u660e\u8a0a\u606f
//-------------------------------------------------------------------------------------------------
static void help()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	cout <<"\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n"
		<<"\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c10\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n"
		<<	"\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" << CV_VERSION 
		<<"\n\n  ----------------------------------------------------------------------------" ;
	cout	<< "\n\n\t\u8a72Demo\u793a\u7bc4\u4e86 Lukas-Kanade\u57fa\u4e8e\u5149\u6d41\u7684lkdemo\n";
	cout << "\n\t\u7a0b\u5e8f\u9810\u8a2d\u5f9e\u651d\u5f71\u6a5f\u8b80\u5165\u8996\u8a0a\uff0c\u53ef\u4ee5\u6309\u9700\u6539\u70ba\u5f9e\u8996\u8a0a\u6587\u4ef6\u8b80\u5165\u5716\u50cf\n";
	cout << "\n\t\u64cd\u4f5c\u8aaa\u660e: \n"
		"\t\t\u901a\u904e\u9ede\u64ca\u5728\u5716\u50cf\u4e2d\u65b0\u589e/\u522a\u9664\u7279\u5f81\u9ede\n" 
		"\t\tESC - \u9000\u51fa\u7a0b\u5e8f\n"
		"\t\tr -\u81ea\u52d5\u9032\u884c\u8ffd\u8e64\n"
		"\t\tc - \u522a\u9664\u6240\u6709\u9ede\n"
		"\t\tn - \u958b/\u5149-\u591c\u665a\u6a21\u5f0f\n"<< endl;
}

Point2f point;
bool addRemovePt = false;

//--------------------------------\u3010onMouse( )\u56de\u8abf\u51fd\u6578\u3011------------------------------------
//		\u63cf\u8ff0\uff1a\u6ed1\u9f20\u64cd\u4f5c\u56de\u8abf
//-------------------------------------------------------------------------------------------------
static void onMouse( int event, int x, int y, int /*flags*/, void* /*param*/ )
{
	if( event == CV_EVENT_LBUTTONDOWN )
	{
		point = Point2f((float)x, (float)y);
		addRemovePt = true;
	}
}

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
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
			// \u81ea\u52d5\u521d\u59cb\u5316
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
