#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/58_Laplacian.cpp



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;


//-----------------------------------【main( )函數】--------------------------------------------
//            描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main( )
{
	//【0】變數的定義
	Mat src,src_gray,dst, abs_dst;

	//【1】載入原始圖  
	src = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");  //專案目錄下應該有一張名為1.jpg的素材圖

	//【2】顯示原始圖 
	imshow("【原始圖】圖像Laplace變換", src); 
	moveWindow("【原始圖】圖像Laplace變換", 100,100); 

	//【3】使用高斯濾波消除噪聲
	GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

	//【4】轉換為灰度圖
	cvtColor( src, src_gray, CV_RGB2GRAY );

	//【5】使用Laplace函數
	Laplacian( src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT );

	//【6】計算絕對值，並將結果轉換成8位
	convertScaleAbs( dst, abs_dst );

	//【7】顯示效果圖
	imshow( "【效果圖】圖像Laplace變換", abs_dst );
	moveWindow( "【效果圖】圖像Laplace變換", 1000,1000 );

	waitKey(0); 

	return 0; 
}
