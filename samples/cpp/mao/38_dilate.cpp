#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/38_dilate.cpp


//-----------------------------------【頭文件包含部分】---------------------------------------
//	描述：包含程序所依賴的頭文件
//---------------------------------------------------------------------------------------------- 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

//-----------------------------------【命名空間宣告部分】---------------------------------------
//	描述：包含程序所使用的命名空間
//-----------------------------------------------------------------------------------------------  
using namespace std;
using namespace cv;

//-----------------------------------【main( )函數】--------------------------------------------
//	描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main(   )
{

	//載入原圖  
	Mat image = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");

	//建立視窗  
	namedWindow("【原圖】膨脹操作");
	namedWindow("【效果圖】膨脹操作");

	//顯示原圖
	imshow("【原圖】膨脹操作", image);

	//進行膨脹操作 
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out;
	dilate(image, out, element);

	//顯示效果圖 
	imshow("【效果圖】膨脹操作", out);

	waitKey(0); 

	return 0;
}
