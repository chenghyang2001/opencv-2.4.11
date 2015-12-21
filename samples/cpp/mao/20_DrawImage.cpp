#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV3\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f20
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u4f7f\u7528OpenCV\u9032\u884c\u57fa\u672c\u7684\u7e6a\u5716\u64cd\u4f5c
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	3.0 beta
//		2014\u5e7411\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7412\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------


//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//          \u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

//OpenCV3\u9700\u52a0\u5165\u982d\u6587\u4ef6\uff1a
#include <opencv2/imgproc/imgproc.hpp>



//-----------------------------------\u3010\u5de8\u96c6\u5b9a\u7fa9\u90e8\u5206\u3011-------------------------------------------- 
//		\u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "\u3010\u7e6a\u88fd\u57161\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 
#define WINDOW_NAME2 "\u3010\u7e6a\u88fd\u57162\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 
#define WINDOW_WIDTH 600//\u5b9a\u7fa9\u8996\u7a97\u5927\u5c0f\u7684\u5de8\u96c6



//--------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011-------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
void DrawEllipse( Mat img, double angle );//\u7e6a\u88fd\u6a62\u5713
void DrawFilledCircle( Mat img, Point center );//\u7e6a\u88fd\u5713
void DrawPolygon( Mat img );//\u7e6a\u88fd\u591a\u908a\u5f62
void DrawLine( Mat img, Point start, Point end );//\u7e6a\u88fd\u7dda\u6bb5



//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	system("color 5F");
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV3\u7248\u7684\u7b2c20\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}




//---------------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( void )
{

	// \u5efa\u7acb\u7a7a\u767d\u7684Mat\u5716\u50cf
	Mat atomImage = Mat::zeros( WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3 );
	Mat rookImage = Mat::zeros( WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3 );

	ShowHelpText();
	// ---------------------<1>\u7e6a\u88fd\u5316\u5b78\u4e2d\u7684\u539f\u5b50\u7bc4\u4f8b\u5716------------------------

	//\u30101.1\u3011\u5148\u7e6a\u88fd\u51fa\u6a62\u5713
	DrawEllipse( atomImage, 90 );
	DrawEllipse( atomImage, 0 );
	DrawEllipse( atomImage, 45 );
	DrawEllipse( atomImage, -45 );

	//\u30101.2\u3011\u518d\u7e6a\u88fd\u5713\u5fc3
	DrawFilledCircle( atomImage, Point( WINDOW_WIDTH/2, WINDOW_WIDTH/2) );

	// ----------------------------<2>\u7e6a\u88fd\u7d44\u5408\u5716-----------------------------
	//\u30102.1\u3011\u5148\u7e6a\u88fd\u51fa\u6a62\u5713
	DrawPolygon( rookImage );

	// \u30102.2\u3011\u7e6a\u88fd\u77e9\u5f62
	rectangle( rookImage,
		Point( 0, 7*WINDOW_WIDTH/8 ),
		Point( WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar( 0, 255, 255 ),
		-1,
		8 );

	// \u30102.3\u3011\u7e6a\u88fd\u4e00\u4e9b\u7dda\u6bb5
	DrawLine( rookImage, Point( 0, 15*WINDOW_WIDTH/16 ), Point( WINDOW_WIDTH, 15*WINDOW_WIDTH/16 ) );
	DrawLine( rookImage, Point( WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8 ), Point( WINDOW_WIDTH/4, WINDOW_WIDTH ) );
	DrawLine( rookImage, Point( WINDOW_WIDTH/2, 7*WINDOW_WIDTH/8 ), Point( WINDOW_WIDTH/2, WINDOW_WIDTH ) );
	DrawLine( rookImage, Point( 3*WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8 ), Point( 3*WINDOW_WIDTH/4, WINDOW_WIDTH ) );

	// ---------------------------<3>\u986f\u793a\u7e6a\u88fd\u51fa\u7684\u5716\u50cf------------------------
	imshow( WINDOW_NAME1, atomImage );
	moveWindow( WINDOW_NAME1, 0, 200 );
	imshow( WINDOW_NAME2, rookImage );
	moveWindow( WINDOW_NAME2, WINDOW_WIDTH, 200 );

	waitKey( 0 );
	return(0);
}



//-------------------------------\u3010DrawEllipse( )\u51fd\u6578\u3011--------------------------------
//		\u63cf\u8ff0\uff1a\u81ea\u5b9a\u7fa9\u7684\u7e6a\u88fd\u51fd\u6578\uff0c\u5be6\u73fe\u4e86\u7e6a\u88fd\u4e0d\u540c\u89d2\u5ea6\u3001\u76f8\u540c\u5c3a\u5bf8\u7684\u6a62\u5713
//-----------------------------------------------------------------------------------------
void DrawEllipse( Mat img, double angle )
{
	int thickness = 2;
	int lineType = 8;

	ellipse( img,
		Point( WINDOW_WIDTH/2, WINDOW_WIDTH/2 ),
		Size( WINDOW_WIDTH/4, WINDOW_WIDTH/16 ),
		angle,
		0,
		360,
		Scalar( 255, 129, 0 ),
		thickness,
		lineType );
}


//-----------------------------------\u3010DrawFilledCircle( )\u51fd\u6578\u3011---------------------------
//		\u63cf\u8ff0\uff1a\u81ea\u5b9a\u7fa9\u7684\u7e6a\u88fd\u51fd\u6578\uff0c\u5be6\u73fe\u4e86\u5be6\u5fc3\u5713\u7684\u7e6a\u88fd
//-----------------------------------------------------------------------------------------
void DrawFilledCircle( Mat img, Point center )
{
	int thickness = -1;
	int lineType = 8;

	circle( img,
		center,
		WINDOW_WIDTH/32,
		Scalar( 0, 0, 255 ),
		thickness,
		lineType );
}


//-----------------------------------\u3010DrawPolygon( )\u51fd\u6578\u3011--------------------------
//		\u63cf\u8ff0\uff1a\u81ea\u5b9a\u7fa9\u7684\u7e6a\u88fd\u51fd\u6578\uff0c\u5be6\u73fe\u4e86\u51f9\u591a\u908a\u5f62\u7684\u7e6a\u88fd
//--------------------------------------------------------------------------------------
void DrawPolygon( Mat img )
{
	int lineType = 8;

	//\u5efa\u7acb\u4e00\u4e9b\u9ede
	Point rookPoints[1][20];
	rookPoints[0][0]  = Point(    WINDOW_WIDTH/4,   7*WINDOW_WIDTH/8 );
	rookPoints[0][1]  = Point(  3*WINDOW_WIDTH/4,   7*WINDOW_WIDTH/8 );
	rookPoints[0][2]  = Point(  3*WINDOW_WIDTH/4,  13*WINDOW_WIDTH/16 );
	rookPoints[0][3]  = Point( 11*WINDOW_WIDTH/16, 13*WINDOW_WIDTH/16 );
	rookPoints[0][4]  = Point( 19*WINDOW_WIDTH/32,  3*WINDOW_WIDTH/8 );
	rookPoints[0][5]  = Point(  3*WINDOW_WIDTH/4,   3*WINDOW_WIDTH/8 );
	rookPoints[0][6]  = Point(  3*WINDOW_WIDTH/4,     WINDOW_WIDTH/8 );
	rookPoints[0][7]  = Point( 26*WINDOW_WIDTH/40,    WINDOW_WIDTH/8 );
	rookPoints[0][8]  = Point( 26*WINDOW_WIDTH/40,    WINDOW_WIDTH/4 );
	rookPoints[0][9]  = Point( 22*WINDOW_WIDTH/40,    WINDOW_WIDTH/4 );
	rookPoints[0][10] = Point( 22*WINDOW_WIDTH/40,    WINDOW_WIDTH/8 );
	rookPoints[0][11] = Point( 18*WINDOW_WIDTH/40,    WINDOW_WIDTH/8 );
	rookPoints[0][12] = Point( 18*WINDOW_WIDTH/40,    WINDOW_WIDTH/4 );
	rookPoints[0][13] = Point( 14*WINDOW_WIDTH/40,    WINDOW_WIDTH/4 );
	rookPoints[0][14] = Point( 14*WINDOW_WIDTH/40,    WINDOW_WIDTH/8 );
	rookPoints[0][15] = Point(    WINDOW_WIDTH/4,     WINDOW_WIDTH/8 );
	rookPoints[0][16] = Point(    WINDOW_WIDTH/4,   3*WINDOW_WIDTH/8 );
	rookPoints[0][17] = Point( 13*WINDOW_WIDTH/32,  3*WINDOW_WIDTH/8 );
	rookPoints[0][18] = Point(  5*WINDOW_WIDTH/16, 13*WINDOW_WIDTH/16 );
	rookPoints[0][19] = Point(    WINDOW_WIDTH/4,  13*WINDOW_WIDTH/16 );

	const Point* ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };

	fillPoly( img,
		ppt,
		npt,
		1,
		Scalar( 255, 255, 255 ),
		lineType );
}


//-----------------------------------\u3010DrawLine( )\u51fd\u6578\u3011--------------------------
//		\u63cf\u8ff0\uff1a\u81ea\u5b9a\u7fa9\u7684\u7e6a\u88fd\u51fd\u6578\uff0c\u5be6\u73fe\u4e86\u7dda\u7684\u7e6a\u88fd
//---------------------------------------------------------------------------------
void DrawLine( Mat img, Point start, Point end )
{
	int thickness = 2;
	int lineType = 8;
	line( img,
		start,
		end,
		Scalar( 0, 0, 0 ),
		thickness,
		lineType );
}
