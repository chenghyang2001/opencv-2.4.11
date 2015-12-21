#include <stdio.h>
//:read /home/peter/mao/66_remap2.cpp
//--------------------------------------【程式說明】-------------------------------------------
//		程式說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程式66
//		程式描述：實現多種重映射綜合範例
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程式所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;


//-----------------------------------【巨集定義部分】-------------------------------------------- 
//  描述：定義一些輔助巨集 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME "【程式視窗】"        //為視窗標題定義的巨集 


//-----------------------------------【全局變數宣告部分】--------------------------------------
//          描述：全局變數的宣告
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage;
Mat g_map_x, g_map_y;


//-----------------------------------【全局函數宣告部分】--------------------------------------
//          描述：全局函數的宣告
//-----------------------------------------------------------------------------------------------
int update_map( int key);
static void ShowHelpText( );//輸出說明文字

//-----------------------------------【main( )函數】--------------------------------------------
//          描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( int argc, char** argv )
{
	//改變console字體顏色
	system("color 5F"); 

	//顯示說明文字
	ShowHelpText();

	//【1】載入原始圖
	g_srcImage = imread( "/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", 1 );
	if(!g_srcImage.data ) { printf("讀取圖形錯誤，請確定目錄下是否有imread函數指定的圖形存在~！ \n"); return false; }  
	imshow("原始圖",g_srcImage);

	//【2】建立和原始圖一樣的效果圖，x重映射圖，y重映射圖
	g_dstImage.create( g_srcImage.size(), g_srcImage.type() );
	g_map_x.create( g_srcImage.size(), CV_32FC1 );
	g_map_y.create( g_srcImage.size(), CV_32FC1 );

	//【3】建立視窗並顯示
	namedWindow( WINDOW_NAME, CV_WINDOW_AUTOSIZE );
	imshow(WINDOW_NAME,g_srcImage);

	//【4】輪詢按鍵，更新map_x和map_y的值，進行重映射操作並顯示效果圖
	while( 1 )
	{
		//取得鍵盤按鍵  
		int key = waitKey(0);  

		//判斷ESC是否按下，若按下便退出  
		if( (key & 255) == 27 )  
		{  
			cout << "程式退出...........\n";  
			break;  
		}  

		//根據按下的鍵盤按鍵來更新 map_x & map_y的值. 然後使用remap( )進行重映射
		update_map(key);
		remap( g_srcImage, g_dstImage, g_map_x, g_map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0, 0) );

		//顯示效果圖
		imshow( WINDOW_NAME, g_dstImage );
	}
	return 0;
}

//-----------------------------------【update_map( )函數】--------------------------------
//          描述：根據按鍵來更新map_x與map_x的值
//----------------------------------------------------------------------------------------------
int update_map( int key )
{
	//雙層循環，瀏覽每一個像素點
	for( int j = 0; j < g_srcImage.rows;j++)
	{ 
		for( int i = 0; i < g_srcImage.cols;i++)
		{
			switch(key)
			{
			case '1': // 鍵盤【1】鍵按下，進行第一種重映射操作
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
			case '2':// 鍵盤【2】鍵按下，進行第二種重映射操作
				g_map_x.at<float>(j,i) = static_cast<float>(i);
				g_map_y.at<float>(j,i) = static_cast<float>(g_srcImage.rows - j);
				break;
			case '3':// 鍵盤【3】鍵按下，進行第三種重映射操作
				g_map_x.at<float>(j,i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j,i) = static_cast<float>(j);
				break;
			case '4':// 鍵盤【4】鍵按下，進行第四種重映射操作
				g_map_x.at<float>(j,i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j,i) = static_cast<float>(g_srcImage.rows - j);
				break;
			} 
		}
	}
	return 1;
}

//-----------------------------------【ShowHelpText( )函數】----------------------------------  
//      描述：輸出一些說明訊息  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第66個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//輸出一些說明訊息  
	printf("\n\t歡迎來到重映射範例程式~\n\n");  
	printf( "\n\t按鍵操作說明: \n\n"  
		"\t\t鍵盤按鍵【ESC】- 退出程式\n"  
		"\t\t鍵盤按鍵【1】-  第一種映射方式\n"  
		"\t\t鍵盤按鍵【2】- 第二種映射方式\n"  
		"\t\t鍵盤按鍵【3】- 第三種映射方式\n"  
		"\t\t鍵盤按鍵【4】- 第四種映射方式\n" 	 );  
}  
