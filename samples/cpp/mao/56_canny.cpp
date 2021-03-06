#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/56_canny.cpp




//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;


//-----------------------------------【main( )函數】-------------------------------------------
//            描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main( )
{
	//載入原始圖  
	Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");  //專案目錄下應該有一張名為1.jpg的素材圖
	Mat srcImage1=srcImage.clone();

	//顯示原始圖 
	imshow("【原始圖】Canny邊緣檢測", srcImage); 
	moveWindow("【原始圖】Canny邊緣檢測", 100,100); 

	//----------------------------------------------------------------------------------
	//	一、最簡單的canny用法，拿到原圖後直接用。
	//----------------------------------------------------------------------------------
	Canny( srcImage, srcImage, 150, 100,3 );
	imshow("【效果圖】Canny邊緣檢測", srcImage); 
	moveWindow("【效果圖】Canny邊緣檢測", 1000,100); 


	//----------------------------------------------------------------------------------
	//	二、高階的canny用法，轉成灰度圖，降噪，用canny，最後將得到的邊緣作為掩碼，拷貝原圖到效果圖上，得到彩色的邊緣圖
	//----------------------------------------------------------------------------------
	Mat dstImage,edge,grayImage;

	// 【1】建立與src同類別型和大小的矩陣(dst)
	dstImage.create( srcImage1.size(), srcImage1.type() );

	// 【2】將原圖像轉換為灰度圖像
	cvtColor( srcImage1, grayImage, CV_BGR2GRAY );

	// 【3】先用使用 3x3核心來降噪
	blur( grayImage, edge, Size(3,3) );

	// 【4】執行Canny算子
	Canny( edge, edge, 3, 9,3 );

	//【5】將g_dstImage內的所有元素設定為0 
	dstImage = Scalar::all(0);

	//【6】使用Canny算子輸出的邊緣圖g_cannyDetectedEdges作為掩碼，來將原圖g_srcImage拷到目標圖g_dstImage中
	srcImage1.copyTo( dstImage, edge);

	//【7】顯示效果圖 
	imshow("【效果圖】Canny邊緣檢測2", dstImage); 
	moveWindow("【效果圖】Canny邊緣檢測2", 1000,1000 ); 


	waitKey(0); 

	return 0; 
}
