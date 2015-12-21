#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f66
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1a\u5be6\u73fe\u591a\u7a2e\u91cd\u6620\u5c04\u7d9c\u5408\u7bc4\u4f8b
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;


//-----------------------------------\u3010\u5de8\u96c6\u5b9a\u7fa9\u90e8\u5206\u3011-------------------------------------------- 
//  \u63cf\u8ff0\uff1a\u5b9a\u7fa9\u4e00\u4e9b\u8f14\u52a9\u5de8\u96c6 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME "\u3010\u7a0b\u5f0f\u8996\u7a97\u3011"        //\u70ba\u8996\u7a97\u6a19\u984c\u5b9a\u7fa9\u7684\u5de8\u96c6 


//-----------------------------------\u3010\u5168\u5c40\u8b8a\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//          \u63cf\u8ff0\uff1a\u5168\u5c40\u8b8a\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage;
Mat g_map_x, g_map_y;


//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//          \u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
int update_map( int key);
static void ShowHelpText( );//\u8f38\u51fa\u8aaa\u660e\u6587\u5b57

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 5F"); 

	//\u986f\u793a\u8aaa\u660e\u6587\u5b57
	ShowHelpText();

	//\u30101\u3011\u8f09\u5165\u539f\u59cb\u5716
	g_srcImage = imread( "1.jpg", 1 );
	if(!g_srcImage.data ) { printf("\u8b80\u53d6\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u7684\u5716\u5f62\u5b58\u5728~\uff01 \n"); return false; }  
	imshow("\u539f\u59cb\u5716",g_srcImage);

	//\u30102\u3011\u5efa\u7acb\u548c\u539f\u59cb\u5716\u4e00\u6a23\u7684\u6548\u679c\u5716\uff0cx\u91cd\u6620\u5c04\u5716\uff0cy\u91cd\u6620\u5c04\u5716
	g_dstImage.create( g_srcImage.size(), g_srcImage.type() );
	g_map_x.create( g_srcImage.size(), CV_32FC1 );
	g_map_y.create( g_srcImage.size(), CV_32FC1 );

	//\u30103\u3011\u5efa\u7acb\u8996\u7a97\u4e26\u986f\u793a
	namedWindow( WINDOW_NAME, CV_WINDOW_AUTOSIZE );
	imshow(WINDOW_NAME,g_srcImage);

	//\u30104\u3011\u8f2a\u8a62\u6309\u9375\uff0c\u66f4\u65b0map_x\u548cmap_y\u7684\u503c\uff0c\u9032\u884c\u91cd\u6620\u5c04\u64cd\u4f5c\u4e26\u986f\u793a\u6548\u679c\u5716
	while( 1 )
	{
		//\u53d6\u5f97\u9375\u76e4\u6309\u9375  
		int key = waitKey(0);  

		//\u5224\u65b7ESC\u662f\u5426\u6309\u4e0b\uff0c\u82e5\u6309\u4e0b\u4fbf\u9000\u51fa  
		if( (key & 255) == 27 )  
		{  
			cout << "\u7a0b\u5f0f\u9000\u51fa...........\n";  
			break;  
		}  

		//\u6839\u64da\u6309\u4e0b\u7684\u9375\u76e4\u6309\u9375\u4f86\u66f4\u65b0 map_x & map_y\u7684\u503c. \u7136\u5f8c\u4f7f\u7528remap( )\u9032\u884c\u91cd\u6620\u5c04
		update_map(key);
		remap( g_srcImage, g_dstImage, g_map_x, g_map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0, 0) );

		//\u986f\u793a\u6548\u679c\u5716
		imshow( WINDOW_NAME, g_dstImage );
	}
	return 0;
}

//-----------------------------------\u3010update_map( )\u51fd\u6578\u3011--------------------------------
//          \u63cf\u8ff0\uff1a\u6839\u64da\u6309\u9375\u4f86\u66f4\u65b0map_x\u8207map_x\u7684\u503c
//----------------------------------------------------------------------------------------------
int update_map( int key )
{
	//\u96d9\u5c64\u5faa\u74b0\uff0c\u700f\u89bd\u6bcf\u4e00\u500b\u50cf\u7d20\u9ede
	for( int j = 0; j < g_srcImage.rows;j++)
	{ 
		for( int i = 0; i < g_srcImage.cols;i++)
		{
			switch(key)
			{
			case '1': // \u9375\u76e4\u30101\u3011\u9375\u6309\u4e0b\uff0c\u9032\u884c\u7b2c\u4e00\u7a2e\u91cd\u6620\u5c04\u64cd\u4f5c
				if( i > g_srcImage.cols*0.25 && i < g_srcImage.cols*0.75 && j > g_srcImage.rows*0.25 && j < g_srcImage.rows*0.75)
				{
					g_map_x.at<float>(j,i) = static_cast<float>(2*( i - g_srcImage.cols*0.25 ) + 0.5);
					g_map_y.at<float>(j,i) = static_cast<float>(2*( j - g_srcImage.rows*0.25 ) + 0.5);
				}
				else
				{ 
					g_map_x.at<float>(j,i) = 0;
					g_map_y.at<float>(j,i) = 0;
				}
				break;
			case '2':// \u9375\u76e4\u30102\u3011\u9375\u6309\u4e0b\uff0c\u9032\u884c\u7b2c\u4e8c\u7a2e\u91cd\u6620\u5c04\u64cd\u4f5c
				g_map_x.at<float>(j,i) = static_cast<float>(i);
				g_map_y.at<float>(j,i) = static_cast<float>(g_srcImage.rows - j);
				break;
			case '3':// \u9375\u76e4\u30103\u3011\u9375\u6309\u4e0b\uff0c\u9032\u884c\u7b2c\u4e09\u7a2e\u91cd\u6620\u5c04\u64cd\u4f5c
				g_map_x.at<float>(j,i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j,i) = static_cast<float>(j);
				break;
			case '4':// \u9375\u76e4\u30104\u3011\u9375\u6309\u4e0b\uff0c\u9032\u884c\u7b2c\u56db\u7a2e\u91cd\u6620\u5c04\u64cd\u4f5c
				g_map_x.at<float>(j,i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j,i) = static_cast<float>(g_srcImage.rows - j);
				break;
			} 
		}
	}
	return 1;
}

//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------  
//      \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c66\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
	printf("\n\t\u6b61\u8fce\u4f86\u5230\u91cd\u6620\u5c04\u7bc4\u4f8b\u7a0b\u5f0f~\n\n");  
	printf( "\n\t\u6309\u9375\u64cd\u4f5c\u8aaa\u660e: \n\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u3010ESC\u3011- \u9000\u51fa\u7a0b\u5f0f\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30101\u3011-  \u7b2c\u4e00\u7a2e\u6620\u5c04\u65b9\u5f0f\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30102\u3011- \u7b2c\u4e8c\u7a2e\u6620\u5c04\u65b9\u5f0f\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30103\u3011- \u7b2c\u4e09\u7a2e\u6620\u5c04\u65b9\u5f0f\n"  
		"\t\t\u9375\u76e4\u6309\u9375\u30104\u3011- \u7b2c\u56db\u7a2e\u6620\u5c04\u65b9\u5f0f\n" 	 );  
}  
