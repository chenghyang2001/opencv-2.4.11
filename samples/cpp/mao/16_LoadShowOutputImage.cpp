#include <stdio.h>
//:read /home/peter/mao/16_LoadShowOutputImage.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序16
//		程序描述：圖像的載入、顯示和輸出範例
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年03月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;


int main( )
{
	//-----------------------------------【一、圖像的載入和顯示】---------------------------------
	//	描述：以下三行程式碼用于完成圖像的載入和顯示
	//--------------------------------------------------------------------------------------------------

//        Mat girl=imread("girl.jpg"); //載入圖像到Mat
	Mat girl=imread("/home/peter/opencv-2.4.11/samples/cpp/mao/girl.jpg"); //載入圖像到Mat
	namedWindow("【1】動漫圖"); //建立一個名為 "【1】動漫圖"的視窗  
	imshow("【1】動漫圖",girl);//顯示名為 "【1】動漫圖"的視窗  

	//-----------------------------------【二、初級圖像混合】--------------------------------------
	//	描述：二、初級圖像混合
	//--------------------------------------------------------------------------------------------------
	//載入圖形
	Mat image= imread("/home/peter/opencv-2.4.11/samples/cpp/mao/dota.jpg",199);
	Mat logo= imread("/home/peter/opencv-2.4.11/samples/cpp/mao/dota_logo.jpg");

	//載入後先顯示
	namedWindow("【2】原畫圖");
	imshow("【2】原畫圖",image);

	namedWindow("【3】logo圖");
	imshow("【3】logo圖",logo);

	// 定義一個Mat類別型，用于存放，圖像的ROI
	Mat imageROI;
	//方法一
	imageROI= image(Rect(800,350,logo.cols,logo.rows));
	//方法二
	//imageROI= image(Range(350,350+logo.rows),Range(800,800+logo.cols));

	// 將logo加到原圖上
	addWeighted(imageROI,0.5,logo,0.3,0.,imageROI);

	//顯示結果
	namedWindow("【4】原畫+logo圖");
	imshow("【4】原畫+logo圖",image);

	//-----------------------------------【三、圖像的輸出】--------------------------------------
	//	描述：將一個Mat圖像輸出到圖像文件
	//-----------------------------------------------------------------------------------------------
	//輸出一張jpg圖形到專案目錄下
	imwrite("由imwrite產生的圖形.jpg",image);

	waitKey();

	return 0;
}
