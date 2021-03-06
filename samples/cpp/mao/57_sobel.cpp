#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/57_sobel.cpp



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------


//-----------------------------------【頭文件包含部分】---------------------------------------
//            描述：包含程序所依賴的頭文件
//----------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

//-----------------------------------【命名空間宣告部分】---------------------------------------
//            描述：包含程序所使用的命名空間
//-----------------------------------------------------------------------------------------------
using namespace cv;
//-----------------------------------【main( )函數】--------------------------------------------
//            描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main( )
{
	//【0】建立 grad_x 和 grad_y 矩陣
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y,dst;

	//【1】載入原始圖  
	Mat src = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");  //專案目錄下應該有一張名為1.jpg的素材圖

	//【2】顯示原始圖 
	imshow("【原始圖】sobel邊緣檢測", src); 
	moveWindow("【原始圖】sobel邊緣檢測", 100,100); 

	//【3】求 X方向梯度
	Sobel( src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
	convertScaleAbs( grad_x, abs_grad_x );
	imshow("【效果圖】 X方向Sobel", abs_grad_x); 
	moveWindow("【效果圖】 X方向Sobel", 1000,100); 

	//【4】求Y方向梯度
	Sobel( src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT );
	convertScaleAbs( grad_y, abs_grad_y );
	imshow("【效果圖】Y方向Sobel", abs_grad_y); 
	moveWindow("【效果圖】Y方向Sobel", 1000,1000); 

	//【5】合並梯度(近似)
	addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst );
	imshow("【效果圖】整體方向Sobel", dst); 
	moveWindow("【效果圖】整體方向Sobel", 100,1000); 

	waitKey(0); 
	return 0; 
}
