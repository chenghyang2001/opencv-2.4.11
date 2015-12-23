#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/62_HoughLinesP.cpp




//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;



//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-------------------------------------------------------------------------------------------------
int main( )
{
	//【1】載入原始圖和Mat變數定義   
	Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");  //專案目錄下應該有一張名為1.jpg的素材圖
	Mat midImage,dstImage;//臨時變數和目標圖的定義

	//【2】進行邊緣檢測和轉化為灰度圖
	Canny(srcImage, midImage, 50, 200, 3);//進行一此canny邊緣檢測
	cvtColor(midImage,dstImage, CV_GRAY2BGR);//轉化邊緣檢測後的圖為灰度圖

	//【3】進行霍夫線變換
	vector<Vec4i> lines;//定義一個矢量結構lines用于存放得到的線段矢量集合
	HoughLinesP(midImage, lines, 1, CV_PI/180, 80, 50, 10 );

	//【4】依次在圖中繪製出每條線段
	for( size_t i = 0; i < lines.size(); i++ )
	{
		Vec4i l = lines[i];
		line( dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186,88,255), 1, CV_AA);
	}

	//【5】顯示原始圖  
	imshow("【原始圖】", srcImage);  
	moveWindow("【原始圖】", 100, 100 );  

	//【6】邊緣檢測後的圖 
	imshow("【邊緣檢測後的圖】", midImage);  
	moveWindow("【邊緣檢測後的圖】", 1000,1000);  

	//【7】顯示效果圖  
	imshow("【效果圖】", dstImage);  
	moveWindow("【效果圖】", 100,1000);  

	waitKey(0);  

	return 0;  
}


