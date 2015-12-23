#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/41_DilationEX.cpp


//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;


//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main( )
{
	//載入原始圖   
	Mat image = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");  //專案目錄下應該有一張名為1.jpg的素材圖
	//建立視窗   
	namedWindow("【原始圖】膨脹");  
	namedWindow("【效果圖】膨脹");  
	//顯示原始圖  
	imshow("【原始圖】膨脹", image);  
	//定義核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  
	//進行形態學操作
	morphologyEx(image, image, MORPH_DILATE, element);
	//顯示效果圖  
	imshow("【效果圖】膨脹", image);  

	waitKey(0);  

	return 0;  
}
