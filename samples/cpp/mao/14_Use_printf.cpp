#include <stdio.h>
//:read /home/peter/mao/14_Use_printf.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序14
//		程序描述：printf函數用法範例
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------

#include <opencv2/opencv.hpp>
using namespace cv;

int main( )
{
	int a=66,b=68;
	printf("\n\t%d %d\n",a,b);//輸出十進制整型
	printf("\n\t%06d,%06d\n",a,b);//輸出6位十進制整型
	printf("\n\t%c,%c\n",a,b);//按字表型輸出
	printf("\n\t結果為：a=%d,b=%d",a,b);//可以配合其他內容一同輸出
	getchar();//等待讀入任意字表而結束，在此用于保持視窗顯示，直到任意按鍵按下
}