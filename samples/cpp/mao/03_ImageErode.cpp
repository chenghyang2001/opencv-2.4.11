#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/03_ImageErode.cpp


//-----------------------------------【頭文件包含部分】---------------------------------------
//		描述：包含程序所依賴的頭文件
//---------------------------------------------------------------------------------------------- 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//-----------------------------------【命名空間宣告部分】---------------------------------------
//		描述：包含程序所使用的命名空間
//-----------------------------------------------------------------------------------------------  
using namespace cv;

//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main(   )
{
	//載入原圖  
//        Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");
	Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/rain.jpg");
	//顯示原圖
	imshow("【原圖】腐蝕操作", srcImage);
	moveWindow("【原圖】腐蝕操作", 100,100);
	
	//進行腐蝕操作 
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat dstImage;
	erode(srcImage, dstImage, element);

	//顯示效果圖 
	imshow("【效果圖】腐蝕操作", dstImage);
	moveWindow("【效果圖】腐蝕操作", 1000,100);
	waitKey(0); 

	return 0;
}
