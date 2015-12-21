#include <stdio.h>
//:read /home/peter/mao/28_DFT.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序28
//		程序描述：離散傅立葉變換
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】-----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//-------------------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;


//-----------------------------------【ShowHelpText( )函數】----------------------------------
//		 描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第28個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}



//--------------------------------------【main( )函數】-----------------------------------------
//          描述：控制臺應用程序的入口函數，我們的程序從這里開始執行
//-------------------------------------------------------------------------------------------------
int main( )
{

	//【1】以灰度模式讀取原始圖像並顯示
	Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", 0);
	if(!srcImage.data ) { printf("讀取圖形錯誤，請確定目錄下是否有imread函數指定圖形存在~！ \n"); return false; } 
	imshow("原始圖像" , srcImage);   

	ShowHelpText();

	//【2】將輸入圖像延擴到最佳的尺寸，邊界用0補充
	int m = getOptimalDFTSize( srcImage.rows );
	int n = getOptimalDFTSize( srcImage.cols ); 
	//將新增的像素初始化為0.
	Mat padded;  
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

	//【3】為傅立葉變換的結果(實部和虛部)分配存儲空間。
	//將planes數組組合合並成一個多通道的數組complexI
	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
	Mat complexI;
	merge(planes, 2, complexI);         

	//【4】進行就地離散傅立葉變換
	dft(complexI, complexI);           

	//【5】將復數轉換為幅值，即=> log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes); // 將多通道數組complexI分離成幾個單通道數組，planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude  
	Mat magnitudeImage = planes[0];

	//【6】進行對數尺度(logarithmic scale)縮放
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);//求自然對數

	//【7】剪切和重分布幅度圖象限
	//若有奇數行或奇數列，進行頻譜裁剪      
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));
	//重新排列傅立葉圖像中的象限，使得原點位于圖像中心  
	int cx = magnitudeImage.cols/2;
	int cy = magnitudeImage.rows/2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));   // ROI區域的左上
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));  // ROI區域的右上
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));  // ROI區域的左下
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); // ROI區域的右下
	//交換象限（左上與右下進行交換）
	Mat tmp;                           
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//交換象限（右上與左下進行交換）
	q1.copyTo(tmp);                 
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//【8】歸一化，用0到1之間的浮點值將矩陣變換為可視的圖像格式
	normalize(magnitudeImage, magnitudeImage, 0, 1, CV_MINMAX); 

	//【9】顯示效果圖
	imshow("頻譜幅值", magnitudeImage);    
	waitKey();

	return 0;
}
