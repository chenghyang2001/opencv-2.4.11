#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f74
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u5efa\u7acb\u5305\u570d\u8f2a\u5ed3\u7684\u5713\u5f62\u908a\u754c
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{

	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c13\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf("\n\n\t\t\t\u6b61\u8fce\u4f86\u5230\u3010\u5c0b\u627e\u6700\u5c0f\u9762\u7a4d\u7684\u5305\u570d\u5713\u3011\u7bc4\u4f8b\u7a0b\u5e8f~\n"); 
	printf("\n\n\t\u6309\u9375\u64cd\u4f5c\u8aaa\u660e: \n\n" 
		"\t\t\u9375\u76e4\u6309\u9375\u3010ESC\u3011\u3001\u3010Q\u3011\u3001\u3010q\u3011- \u9000\u51fa\u7a0b\u5e8f\n\n" 
		"\t\t\u9375\u76e4\u6309\u9375\u4efb\u610f\u9375 - \u91cd\u65b0\u7522\u751f\u96a8\u6a5f\u9ede\uff0c\u4e26\u5c0b\u627e\u6700\u5c0f\u9762\u7a4d\u7684\u5305\u570d\u5713\n" );  
}

int main(  )
{
	//\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 1F"); 

	//\u986f\u793a\u8aaa\u660e\u6587\u5b57
	ShowHelpText();

	//\u521d\u59cb\u5316\u8b8a\u6578\u548c\u96a8\u6a5f\u503c
	Mat image(600, 600, CV_8UC3);
	RNG& rng = theRNG();

	//\u5faa\u74b0\uff0c\u6309\u4e0bESC,Q,q\u9375\u7a0b\u5e8f\u9000\u51fa\uff0c\u5426\u5247\u6709\u9375\u6309\u4e0b\u4fbf\u4e00\u76f4\u66f4\u65b0
	while(1)
	{
		//\u53c3\u6578\u521d\u59cb\u5316
		int count = rng.uniform(3, 103);//\u96a8\u6a5f\u7522\u751f\u9ede\u7684\u6578\u91cf
		vector<Point> points;//\u9ede\u503c

		//\u96a8\u6a5f\u7522\u751f\u9ede\u5750\u6a19
		for(int  i = 0; i < count; i++ )
		{

			Point point;
			point.x = rng.uniform(image.cols/4, image.cols*3/4);
			point.y = rng.uniform(image.rows/4, image.rows*3/4);

			points.push_back(point);
		}

		//\u5c0d\u7d66\u5b9a\u7684 2D \u9ede\u96c6\uff0c\u5c0b\u627e\u6700\u5c0f\u9762\u7a4d\u7684\u5305\u570d\u5713
		Point2f center;
		float radius = 0;
		minEnclosingCircle(Mat(points), center, radius);

		//\u7e6a\u88fd\u51fa\u96a8\u6a5f\u984f\u8272\u7684\u9ede
		image = Scalar::all(0);
		for( int i = 0; i < count; i++ )
			circle( image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), CV_FILLED, CV_AA );


		//\u7e6a\u88fd\u51fa\u6700\u5c0f\u9762\u7a4d\u7684\u5305\u570d\u5713
		circle(image, center, cvRound(radius), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, CV_AA);

		//\u986f\u793a\u8996\u7a97
		imshow( "\u5713\u5f62\u5305\u570d\u7bc4\u4f8b", image );

		//\u6309\u4e0bESC,Q,\u6216\u8005q\uff0c\u7a0b\u5e8f\u9000\u51fa
		char key = (char)waitKey();
		if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
			break;
	}

	return 0;
}
