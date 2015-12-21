#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f54
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u5716\u50cf\u91d1\u5b57\u5854\u548cresize\u7d9c\u5408\u7bc4\u4f8b
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
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;


//-----------------------------------\u3010\u5de8\u96c6\u5b9a\u7fa9\u90e8\u5206\u3011--------------------------------------------
//	\u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6
//------------------------------------------------------------------------------------------------
#define WINDOW_NAME "\u3010\u7a0b\u5e8f\u8996\u7a97\u3011"		//\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage, g_tmpImage;


//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
static void ShowHelpText();

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-----------------------------------------------------------------------------------------------
int main( )
{
	//\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 2F");  

	//\u986f\u793a\u8aaa\u660e\u6587\u5b57
	ShowHelpText();

	//\u8f09\u5165\u539f\u5716
	g_srcImage = imread("1.jpg");//\u5c08\u6848\u76ee\u9304\u4e0b\u9700\u8981\u6709\u4e00\u5f35\u540d\u70ba1.jpg\u7684\u6e2c\u8a66\u5716\u50cf\uff0c\u4e14\u5176\u5c3a\u5bf8\u9700\u88ab2\u7684N\u6b21\u65b9\u6574\u9664\uff0cN\u70ba\u53ef\u4ee5\u7e2e\u653e\u7684\u6b21\u6578
	if( !g_srcImage.data ) { printf("Oh\uff0cno\uff0c\u8b80\u53d6srcImage\u932f\u8aa4~\uff01 \n"); return false; }

	// \u5efa\u7acb\u986f\u793a\u8996\u7a97
	namedWindow( WINDOW_NAME, CV_WINDOW_AUTOSIZE );
	imshow(WINDOW_NAME, g_srcImage);

	//\u53c3\u6578\u8ce6\u503c
	g_tmpImage = g_srcImage;
	g_dstImage = g_tmpImage;

	int key =0;

	//\u8f2a\u8a62\u53d6\u5f97\u6309\u9375\u8a0a\u606f
	while(1)
	{
		key=waitKey(9) ;//\u8b80\u53d6\u9375\u503c\u5230key\u8b8a\u6578\u4e2d

		//\u6839\u64dakey\u8b8a\u6578\u7684\u503c\uff0c\u9032\u884c\u4e0d\u540c\u7684\u64cd\u4f5c
		switch(key)
		{
			//======================\u3010\u7a0b\u5e8f\u9000\u51fa\u76f8\u95dc\u9375\u503c\u8655\u7406\u3011=======================  
		case 27://\u6309\u9375ESC
			return 0;
			break; 

		case 'q'://\u6309\u9375Q
			return 0;
			break; 

			//======================\u3010\u5716\u5f62\u653e\u5927\u76f8\u95dc\u9375\u503c\u8655\u7406\u3011=======================  
		case 'a'://\u6309\u9375A\u6309\u4e0b\uff0c\u4f7f\u7528pyrUp\u51fd\u6578
			pyrUp( g_tmpImage, g_dstImage, Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ) );
			printf( ">\u6aa2\u6e2c\u5230\u6309\u9375\u3010A\u3011\u88ab\u6309\u4e0b\uff0c\u958b\u59cb\u9032\u884c\u57fa\u4e8e\u3010pyrUp\u3011\u51fd\u6578\u7684\u5716\u5f62\u653e\u5927\uff1a\u5716\u5f62\u5c3a\u5bf8×2 \n" );		
			break; 

		case 'w'://\u6309\u9375W\u6309\u4e0b\uff0c\u4f7f\u7528resize\u51fd\u6578
			resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ));
			printf( ">\u6aa2\u6e2c\u5230\u6309\u9375\u3010W\u3011\u88ab\u6309\u4e0b\uff0c\u958b\u59cb\u9032\u884c\u57fa\u4e8e\u3010resize\u3011\u51fd\u6578\u7684\u5716\u5f62\u653e\u5927\uff1a\u5716\u5f62\u5c3a\u5bf8×2 \n" );		
			break; 

		case '1'://\u6309\u93751\u6309\u4e0b\uff0c\u4f7f\u7528resize\u51fd\u6578
			resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ));
			printf( ">\u6aa2\u6e2c\u5230\u6309\u9375\u30101\u3011\u88ab\u6309\u4e0b\uff0c\u958b\u59cb\u9032\u884c\u57fa\u4e8e\u3010resize\u3011\u51fd\u6578\u7684\u5716\u5f62\u653e\u5927\uff1a\u5716\u5f62\u5c3a\u5bf8×2 \n" );
			break; 

		case '3': //\u6309\u93753\u6309\u4e0b\uff0c\u4f7f\u7528pyrUp\u51fd\u6578
			pyrUp( g_tmpImage, g_dstImage, Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ));
			printf( ">\u6aa2\u6e2c\u5230\u6309\u9375\u30103\u3011\u88ab\u6309\u4e0b\uff0c\u958b\u59cb\u9032\u884c\u57fa\u4e8e\u3010pyrUp\u3011\u51fd\u6578\u7684\u5716\u5f62\u653e\u5927\uff1a\u5716\u5f62\u5c3a\u5bf8×2 \n" );
			break; 
			//======================\u3010\u5716\u5f62\u7e2e\u5c0f\u76f8\u95dc\u9375\u503c\u8655\u7406\u3011=======================  
		case 'd': //\u6309\u9375D\u6309\u4e0b\uff0c\u4f7f\u7528pyrDown\u51fd\u6578
			pyrDown( g_tmpImage, g_dstImage, Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ));
			printf( ">\u6aa2\u6e2c\u5230\u6309\u9375\u3010D\u3011\u88ab\u6309\u4e0b\uff0c\u958b\u59cb\u9032\u884c\u57fa\u4e8e\u3010pyrDown\u3011\u51fd\u6578\u7684\u5716\u5f62\u7e2e\u5c0f\uff1a\u5716\u5f62\u5c3a\u5bf8/2\n" );
			break; 

		case  's' : //\u6309\u9375S\u6309\u4e0b\uff0c\u4f7f\u7528resize\u51fd\u6578
			resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ));
			printf( ">\u6aa2\u6e2c\u5230\u6309\u9375\u3010S\u3011\u88ab\u6309\u4e0b\uff0c\u958b\u59cb\u9032\u884c\u57fa\u4e8e\u3010resize\u3011\u51fd\u6578\u7684\u5716\u5f62\u7e2e\u5c0f\uff1a\u5716\u5f62\u5c3a\u5bf8/2\n" );
			break; 

		case '2'://\u6309\u93752\u6309\u4e0b\uff0c\u4f7f\u7528resize\u51fd\u6578
			resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ));
			printf( ">\u6aa2\u6e2c\u5230\u6309\u9375\u30102\u3011\u88ab\u6309\u4e0b\uff0c\u958b\u59cb\u9032\u884c\u57fa\u4e8e\u3010resize\u3011\u51fd\u6578\u7684\u5716\u5f62\u7e2e\u5c0f\uff1a\u5716\u5f62\u5c3a\u5bf8/2\n" );
			break; 

		case '4': //\u6309\u93754\u6309\u4e0b\uff0c\u4f7f\u7528pyrDown\u51fd\u6578
			pyrDown( g_tmpImage, g_dstImage, Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ) );
			printf( ">\u6aa2\u6e2c\u5230\u6309\u9375\u30104\u3011\u88ab\u6309\u4e0b\uff0c\u958b\u59cb\u9032\u884c\u57fa\u4e8e\u3010pyrDown\u3011\u51fd\u6578\u7684\u5716\u5f62\u7e2e\u5c0f\uff1a\u5716\u5f62\u5c3a\u5bf8/2\n" );
			break; 
		}

		//\u7d93\u904e\u64cd\u4f5c\u5f8c\uff0c\u986f\u793a\u8b8a\u5316\u5f8c\u7684\u5716
		imshow( WINDOW_NAME, g_dstImage );

		//\u5c07g_dstImage\u8ce6\u7d66g_tmpImage\uff0c\u65b9\u4fbf\u4e0b\u4e00\u6b21\u5faa\u74b0
		g_tmpImage = g_dstImage;
	}

	return 0;
}

//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//		\u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{

	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c54\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf("\n\t\u6b61\u8fce\u4f86\u5230OpenCV\u5716\u50cf\u91d1\u5b57\u5854\u548cresize\u7bc4\u4f8b\u7a0b\u5e8f~\n\n");
	printf( "\n\n\t\u6309\u9375\u64cd\u4f5c\u8aaa\u660e: \n\n"
		"\t\t\u9375\u76e4\u6309\u9375\u3010ESC\u3011\u6216\u8005\u3010Q\u3011- \u9000\u51fa\u7a0b\u5e8f\n"
		"\t\t\u9375\u76e4\u6309\u9375\u30101\u3011\u6216\u8005\u3010W\u3011- \u9032\u884c\u57fa\u4e8e\u3010resize\u3011\u51fd\u6578\u7684\u5716\u5f62\u653e\u5927\n"
		"\t\t\u9375\u76e4\u6309\u9375\u30102\u3011\u6216\u8005\u3010S\u3011- \u9032\u884c\u57fa\u4e8e\u3010resize\u3011\u51fd\u6578\u7684\u5716\u5f62\u7e2e\u5c0f\n"
		"\t\t\u9375\u76e4\u6309\u9375\u30103\u3011\u6216\u8005\u3010A\u3011- \u9032\u884c\u57fa\u4e8e\u3010pyrUp\u3011\u51fd\u6578\u7684\u5716\u5f62\u653e\u5927\n"
		"\t\t\u9375\u76e4\u6309\u9375\u30104\u3011\u6216\u8005\u3010D\u3011- \u9032\u884c\u57fa\u4e8e\u3010pyrDown\u3011\u51fd\u6578\u7684\u5716\u5f62\u7e2e\u5c0f\n"
		);
}
