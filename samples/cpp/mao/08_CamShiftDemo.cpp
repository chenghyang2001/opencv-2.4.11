#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f08
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u4f86\u81eaOpenCV\u5b89\u88dd\u76ee\u9304\u4e0bSamples\u6587\u4ef6\u593e\u4e2d\u7684\u5b98\u65b9\u7bc4\u4f8b\u7a0b\u5e8f-\u5f69\u8272\u76ee\u6a19\u8ddf\u8e64\u64cd\u4f5c
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



//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u3011-----------------------------------------
//		\u63cf\u8ff0\uff1a\u5ba3\u544a\u5168\u5c40\u8b8a\u6578
//-------------------------------------------------------------------------------------------------
Mat image;
bool backprojMode = false;
bool selectObject = false;
int trackObject = 0;
bool showHist = true;
Point origin;
Rect selection;
int vmin = 10, vmax = 256, smin = 30;


//--------------------------------\u3010onMouse( )\u56de\u8abf\u51fd\u6578\u3011------------------------------------
//		\u63cf\u8ff0\uff1a\u6ed1\u9f20\u64cd\u4f5c\u56de\u8abf
//-------------------------------------------------------------------------------------------------
static void onMouse( int event, int x, int y, int, void* )
{
	if( selectObject )
	{
		selection.x = MIN(x, origin.x);
		selection.y = MIN(y, origin.y);
		selection.width = std::abs(x - origin.x);
		selection.height = std::abs(y - origin.y);

		selection &= Rect(0, 0, image.cols, image.rows);
	}

	switch( event )
	{
	case CV_EVENT_LBUTTONDOWN:
		origin = Point(x,y);
		selection = Rect(x,y,0,0);
		selectObject = true;
		break;
	case CV_EVENT_LBUTTONUP:
		selectObject = false;
		if( selection.width > 0 && selection.height > 0 )
			trackObject = -1;
		break;
	}
}

//--------------------------------\u3010help( )\u51fd\u6578\u3011----------------------------------------------
//		\u63cf\u8ff0\uff1a\u8f38\u51fa\u8aaa\u660e\u8a0a\u606f
//-------------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	cout <<"\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n"
		<<"\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c8\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n"
		<<	"\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" << CV_VERSION 
		<<"\n\n  ----------------------------------------------------------------------------" ;

	cout << "\n\n\t\u6b64Demo\u986f\u793a\u4e86\u57fa\u4e8e\u5747\u503c\u6f02\u79fb\u7684\u8ffd\u8e64\uff08tracking\uff09\u6280\u8853\n"
		"\t\u8acb\u7528\u6ed1\u9f20\u6846\u9078\u4e00\u500b\u6709\u984f\u8272\u7684\u7269\u9ad4\uff0c\u5c0d\u5b83\u9032\u884c\u8ffd\u8e64\u64cd\u4f5c\n";

	cout << "\n\n\t\u64cd\u4f5c\u8aaa\u660e\uff1a \n"
		"\t\t\u7528\u6ed1\u9f20\u6846\u9078\u5c0d\u8c61\u4f86\u521d\u59cb\u5316\u8ddf\u8e64\n"
		"\t\tESC - \u9000\u51fa\u7a0b\u5e8f\n"
		"\t\tc - \u505c\u6b62\u8ffd\u8e64\n"
		"\t\tb - \u958b/\u95dc-\u6295\u5f71\u8996\u5716\n"
		"\t\th - \u986f\u793a/\u96b1\u85cf-\u5c0d\u8c61\u76f4\u65b9\u5716\n"
		"\t\tp - \u66ab\u505c\u8996\u8a0a\n";
}

const char* keys =
{
	"{1|  | 0 | camera number}"
};


//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-------------------------------------------------------------------------------------------------
int main( int argc, const char** argv )
{
	ShowHelpText();

	VideoCapture cap;
	Rect trackWindow;
	int hsize = 16;
	float hranges[] = {0,180};
	const float* phranges = hranges;

	cap.open(0);

	if( !cap.isOpened() )
	{
		cout << "\u4e0d\u80fd\u521d\u59cb\u5316\u651d\u5f71\u6a5f\n";
	}

	namedWindow( "Histogram", 0 );
	namedWindow( "CamShift Demo", 0 );
	setMouseCallback( "CamShift Demo", onMouse, 0 );
	createTrackbar( "Vmin", "CamShift Demo", &vmin, 256, 0 );
	createTrackbar( "Vmax", "CamShift Demo", &vmax, 256, 0 );
	createTrackbar( "Smin", "CamShift Demo", &smin, 256, 0 );

	Mat frame, hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;
	bool paused = false;

	for(;;)
	{
		if( !paused )
		{
			cap >> frame;
			if( frame.empty() )
				break;
		}

		frame.copyTo(image);

		if( !paused )
		{
			cvtColor(image, hsv, COLOR_BGR2HSV);

			if( trackObject )
			{
				int _vmin = vmin, _vmax = vmax;

				inRange(hsv, Scalar(0, smin, MIN(_vmin,_vmax)),
					Scalar(180, 256, MAX(_vmin, _vmax)), mask);
				int ch[] = {0, 0};
				hue.create(hsv.size(), hsv.depth());
				mixChannels(&hsv, 1, &hue, 1, ch, 1);

				if( trackObject < 0 )
				{
					Mat roi(hue, selection), maskroi(mask, selection);
					calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
					normalize(hist, hist, 0, 255, CV_MINMAX);

					trackWindow = selection;
					trackObject = 1;

					histimg = Scalar::all(0);
					int binW = histimg.cols / hsize;
					Mat buf(1, hsize, CV_8UC3);
					for( int i = 0; i < hsize; i++ )
						buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180./hsize), 255, 255);
					cvtColor(buf, buf, CV_HSV2BGR);

					for( int i = 0; i < hsize; i++ )
					{
						int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);
						rectangle( histimg, Point(i*binW,histimg.rows),
							Point((i+1)*binW,histimg.rows - val),
							Scalar(buf.at<Vec3b>(i)), -1, 8 );
					}
				}

				calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
				backproj &= mask;
				RotatedRect trackBox = CamShift(backproj, trackWindow,
					TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));
				if( trackWindow.area() <= 1 )
				{
					int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5)/6;
					trackWindow = Rect(trackWindow.x - r, trackWindow.y - r,
						trackWindow.x + r, trackWindow.y + r) &
						Rect(0, 0, cols, rows);
				}

				if( backprojMode )
					cvtColor( backproj, image, COLOR_GRAY2BGR );
				ellipse( image, trackBox, Scalar(0,0,255), 3, CV_AA );
			}
		}
		else if( trackObject < 0 )
			paused = false;

		if( selectObject && selection.width > 0 && selection.height > 0 )
		{
			Mat roi(image, selection);
			bitwise_not(roi, roi);
		}

		imshow( "CamShift Demo", image );
		imshow( "Histogram", histimg );

		char c = (char)waitKey(10);
		if( c == 27 )
			break;
		switch(c)
		{
		case 'b':
			backprojMode = !backprojMode;
			break;
		case 'c':
			trackObject = 0;
			histimg = Scalar::all(0);
			break;
		case 'h':
			showHist = !showHist;
			if( !showHist )
				destroyWindow( "Histogram" );
			else
				namedWindow( "Histogram", 1 );
			break;
		case 'p':
			paused = !paused;
			break;
		default:
			;
		}
	}

	return 0;
}
