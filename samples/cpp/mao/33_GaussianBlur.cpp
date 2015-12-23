#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/33_GaussianBlur.cpp




//---------------------------------【頭文件、命名空間包含部分】-------------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp" 
using namespace cv; 

//-----------------------------------【main( )函數】--------------------------------------------
//	描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main( )
{ 
	// 載入原圖
	Mat image=imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg"); 

	//建立視窗
	namedWindow( "高斯濾波【原圖】" ); 
	namedWindow( "高斯濾波【效果圖】"); 

	//顯示原圖
	imshow( "高斯濾波【原圖】", image ); 
	moveWindow( "高斯濾波【原圖】", 100,100 ); 

	//進行高斯濾波操作
	Mat out; 
	GaussianBlur( image, out, Size( 5, 5 ), 0, 0 ); 

	//顯示效果圖
	imshow( "高斯濾波【效果圖】" ,out ); 
	moveWindow( "高斯濾波【效果圖】" ,1000,100 ); 

	waitKey( 0 );     
} 
