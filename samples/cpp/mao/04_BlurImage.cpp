
#include <stdio.h>

//---------------------------------【頭文件、命名空間包含部分】---------------------------
//		描述：包含程序所使用的頭文件和命名空間
//-----------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp" 
using namespace cv; 

//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main( )
{ 
	//【1】載入原始圖
	Mat srcImage=imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg"); 

	//【2】顯示原始圖
	imshow( "均值濾波【原圖】", srcImage ); 
	moveWindow( "均值濾波【原圖】", 100,100 ); 

	//【3】進行均值濾波操作
	Mat dstImage; 
	blur( srcImage, dstImage, Size(7, 7)); 
//        blur( srcImage, dstImage, Size(1, 1)); 

	//【4】顯示效果圖
	imshow( "均值濾波【效果圖】" ,dstImage ); 
	moveWindow( "均值濾波【效果圖】" ,1000,100 ); 

	waitKey( 0 );     
} 
