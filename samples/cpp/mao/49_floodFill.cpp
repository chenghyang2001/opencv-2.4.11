#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/49_floodFill.cpp



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;  



//-----------------------------------【main( )函數】--------------------------------------------  
//      描述：控制臺應用程序的入口函數，我們的程序從這里開始  
//----------------------------------------------------------------------------------------------- 
int main( )
{    
	Mat src = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg"); 
	imshow("【原始圖】",src);
	moveWindow("【原始圖】",100,100);
	Rect ccomp;
	floodFill(src, Point(50,300), Scalar(155, 255,55), &ccomp, Scalar(20, 20, 20),Scalar(20, 20, 20));
	imshow("【效果圖】",src);
	moveWindow("【效果圖】",1000,100);
	waitKey(0);
	return 0;    
}  
