#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f18
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1aHelloOpenCV
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------

//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011-----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//-------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
using namespace cv;

//-----------------------------------\u3010\u5de8\u96c6\u5b9a\u7fa9\u90e8\u5206\u3011--------------------------------------------
//  \u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME "\u3010\u7a0b\u5e8f\u8996\u7a97\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 


//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u7684\u5ba3\u544a
//------------------------------------------------------------------------------------------------
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle( cv::Mat& img, cv::Rect box );
void ShowHelpText( );

//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011-----------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Rect g_rectangle;
bool g_bDrawingBox = false;//\u662f\u5426\u9032\u884c\u7e6a\u88fd
RNG g_rng(12345);



//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-------------------------------------------------------------------------------------------------
int main( int argc, char** argv ) 
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 9F"); 

	//\u30100\u3011\u986f\u793a\u6b61\u8fce\u548c\u8aaa\u660e\u6587\u5b57
	ShowHelpText();

	//\u30101\u3011\u6e96\u5099\u53c3\u6578
	g_rectangle = Rect(-1,-1,0,0);
	Mat srcImage(600, 800,CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1,-1,0,0);
	srcImage = Scalar::all(0);

	//\u30102\u3011\u8a2d\u5b9a\u6ed1\u9f20\u64cd\u4f5c\u56de\u8abf\u51fd\u6578
	namedWindow( WINDOW_NAME );
	setMouseCallback(WINDOW_NAME,on_MouseHandle,(void*)&srcImage);

	//\u30103\u3011\u7a0b\u5e8f\u4e3b\u5faa\u74b0\uff0c\u7576\u9032\u884c\u7e6a\u88fd\u7684\u6a19\u8b58\u8868\u70ba\u771f\u6642\uff0c\u9032\u884c\u7e6a\u88fd
	while(1)
	{
		srcImage.copyTo(tempImage);//\u62f7\u8c9d\u6e90\u5716\u5230\u81e8\u6642\u8b8a\u6578
		if( g_bDrawingBox ) DrawRectangle( tempImage, g_rectangle );//\u7576\u9032\u884c\u7e6a\u88fd\u7684\u6a19\u8b58\u8868\u70ba\u771f\uff0c\u5247\u9032\u884c\u7e6a\u88fd
		imshow( WINDOW_NAME, tempImage );
		if( waitKey( 10 ) == 27 ) break;//\u6309\u4e0bESC\u9375\uff0c\u7a0b\u5e8f\u9000\u51fa
	}
	return 0;
}



//--------------------------------\u3010on_MouseHandle( )\u51fd\u6578\u3011-----------------------------
//		\u63cf\u8ff0\uff1a\u6ed1\u9f20\u56de\u8abf\u51fd\u6578\uff0c\u6839\u64da\u4e0d\u540c\u7684\u6ed1\u9f20\u4e8b\u4ef6\u9032\u884c\u4e0d\u540c\u7684\u64cd\u4f5c
//-----------------------------------------------------------------------------------------------
void on_MouseHandle(int event, int x, int y, int flags, void* param)
{

	Mat& image = *(cv::Mat*) param;
	switch( event)
	{
		//\u6ed1\u9f20\u79fb\u52d5\u8a0a\u606f
	case EVENT_MOUSEMOVE: 
		{
			if( g_bDrawingBox )//\u5982\u679c\u662f\u5426\u9032\u884c\u7e6a\u88fd\u7684\u6a19\u8b58\u8868\u70ba\u771f\uff0c\u5247\u8a18\u9304\u4e0b\u9577\u548c\u5bec\u5230RECT\u578b\u8b8a\u6578\u4e2d
			{
				g_rectangle.width = x-g_rectangle.x;
				g_rectangle.height = y-g_rectangle.y;
			}
		}
		break;

		//\u5de6\u9375\u6309\u4e0b\u8a0a\u606f
	case EVENT_LBUTTONDOWN: 
		{
			g_bDrawingBox = true;
			g_rectangle =Rect( x, y, 0, 0 );//\u8a18\u9304\u8d77\u59cb\u9ede
		}
		break;

		//\u5de6\u9375\u62ac\u8d77\u8a0a\u606f
	case EVENT_LBUTTONUP: 
		{
			g_bDrawingBox = false;//\u7f6e\u6a19\u8b58\u8868\u70bafalse
			//\u5c0d\u5bec\u548c\u9ad8\u5c0f\u4e8e0\u7684\u8655\u7406
			if( g_rectangle.width < 0 )
			{
				g_rectangle.x += g_rectangle.width;
				g_rectangle.width *= -1;
			}

			if( g_rectangle.height < 0 ) 
			{
				g_rectangle.y += g_rectangle.height;
				g_rectangle.height *= -1;
			}
			//\u4f7f\u7528\u51fd\u6578\u9032\u884c\u7e6a\u88fd
			DrawRectangle( image, g_rectangle );
		}
		break;

	}
}



//-----------------------------------\u3010DrawRectangle( )\u51fd\u6578\u3011------------------------------
//		\u63cf\u8ff0\uff1a\u81ea\u5b9a\u7fa9\u7684\u77e9\u5f62\u7e6a\u88fd\u51fd\u6578
//-----------------------------------------------------------------------------------------------
void DrawRectangle( cv::Mat& img, cv::Rect box )
{
	cv::rectangle(img,box.tl(),box.br(),cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255)));//\u96a8\u6a5f\u984f\u8272
}


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011-----------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c18\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf("\n\n\n\t\u6b61\u8fce\u4f86\u5230\u3010\u6ed1\u9f20\u4e92\u52d5\u793a\u7bc4\u3011\u7bc4\u4f8b\u7a0b\u5e8f\n"); 
	printf("\n\n\t\u8acb\u5728\u8996\u7a97\u4e2d\u9ede\u64ca\u6ed1\u9f20\u5de6\u9375\u4e26\u62d6\u52d5\u4ee5\u7e6a\u88fd\u77e9\u5f62\n");

}
