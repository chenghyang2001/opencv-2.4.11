#include <stdio.h>
//:read /home/peter/mao/61_HoughLines.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序61
//		程序描述：HoughLines函數用法範例
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;



//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main( )
{
	//【1】載入原始圖和Mat變數定義   
	Mat srcImage = imread("/home/peter/1.jpg");  //專案目錄下應該有一張名為1.jpg的素材圖
	Mat midImage,dstImage;//臨時變數和目標圖的定義

	//【2】進行邊緣檢測和轉化為灰度圖
	Canny(srcImage, midImage, 50, 200, 3);//進行一此canny邊緣檢測
	cvtColor(midImage,dstImage, CV_GRAY2BGR);//轉化邊緣檢測後的圖為灰度圖

	//【3】進行霍夫線變換
	vector<Vec2f> lines;//定義一個矢量結構lines用于存放得到的線段矢量集合
	HoughLines(midImage, lines, 1, CV_PI/180, 150, 0, 0 );

	//【4】依次在圖中繪製出每條線段
	for( size_t i = 0; i < lines.size(); i++ )
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		line( dstImage, pt1, pt2, Scalar(55,100,195), 1, CV_AA);
	}

	//【5】顯示原始圖  
	imshow("【原始圖】", srcImage);  

	//【6】邊緣檢測後的圖 
	imshow("【邊緣檢測後的圖】", midImage);  

	//【7】顯示效果圖  
	imshow("【效果圖】", dstImage);  

	waitKey(0);  

	return 0;  
}


