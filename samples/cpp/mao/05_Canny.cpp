
#include <stdio.h>
//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//-------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-------------------------------------------------------------------------------------------------
int main( )
{
	//【0】載入原始圖  
	Mat imageSrc = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");  //專案目錄下應該有一張名為1.jpg的素材圖
	imshow("【原始圖】Canny邊緣檢測", imageSrc); 	//顯示原始圖 
	moveWindow("【原始圖】Canny邊緣檢測", 100,100); 	//顯示原始圖 

	Mat imageDst ; 
	//【1】建立與src同類別型和大小的矩陣(dst)
	imageDst.create( imageSrc.size(), imageSrc.type() );

	//【2】將原圖像轉換為灰度圖像
	Mat imageGray;	//參數定義
	cvtColor( imageSrc, imageGray, CV_BGR2GRAY );

	//【3】先用使用 3x3核心來降噪
	Mat imageEdge ;
//        blur( imageGray, imageEdge, Size(3,3) );
	blur( imageGray, imageEdge, Size(20,20) );
//        blur( imageGray, imageEdge, Size(9,9) );

	//【4】執行Canny算子
	Canny( imageEdge, imageEdge, 3, 9,3 );

	//【5】顯示效果圖 
	imshow("【效果圖】Canny邊緣檢測", imageEdge); 
	moveWindow("【效果圖】Canny邊緣檢測", 1000,100); 

	waitKey(0); 

	return 0; 
}
