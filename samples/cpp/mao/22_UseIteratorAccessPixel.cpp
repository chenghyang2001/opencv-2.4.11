#include <stdio.h>
//:read /home/peter/mao/22_UseIteratorAccessPixel.cpp

//--------------------------------------【程式說明】-------------------------------------------
//		程式說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程式22
//		程式描述：用反覆運算器操作像素
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭檔案、命名空間包含部分】---------------------------
//		描述：包含程式所使用的頭檔案和命名空間
//-----------------------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  
using namespace std;  
using namespace cv;  



//-----------------------------------【全局函數宣告部分】-----------------------------------
//		描述：全局函數宣告
//-----------------------------------------------------------------------------------------------
void colorReduce(Mat& inputImage, Mat& outputImage, int div);  
void ShowHelpText();



//--------------------------------------【main( )函數】--------------------------------------
//		描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( )  
{  
	//【1】建立原始圖並顯示
	Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");  
	imshow("原始圖像",srcImage);  
	moveWindow("原始圖像",100,100);  

	//【2】按原始圖的參數規格來建立建立效果圖
	Mat dstImage;
	dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());//效果圖的大小、類別別型與原圖形相同 

	ShowHelpText();

	//【3】記錄起始時間
	double time0 = static_cast<double>(getTickCount());  

	//【4】使用顏色空間縮減函數
	colorReduce(srcImage,dstImage,32);  

	//【5】計算執行時間並輸出
	time0 = ((double)getTickCount() - time0)/getTickFrequency();
	cout<<"此方法執行時間為： "<<time0<<"秒"<<endl;  //輸出執行時間

	//【6】顯示效果圖
	imshow("效果圖",dstImage);  
	moveWindow("效果圖",1000,100);  
	waitKey(0);  
}  




//-------------------------------------【colorReduce( )函數】-----------------------------
//		描述：使用【疊代器】方法版的顏色空間縮減函數
//----------------------------------------------------------------------------------------------
void colorReduce(Mat& inputImage, Mat& outputImage, int div)  
{  
	//參數準備
	outputImage = inputImage.clone();  //拷貝實參到臨時變數
	//取得疊代器
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();  //初始位置的疊代器
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();  //終止位置的疊代器

	//存取彩色圖像像素
	for(;it != itend;++it)  
	{  
		// ------------------------【開始處理每個像素】--------------------
		(*it)[0] = (*it)[0]/div*div + div/2;  
		(*it)[1] = (*it)[1]/div*div + div/2;  
		(*it)[2] = (*it)[2]/div*div + div/2;  
		// ------------------------【處理結束】----------------------------
	}  
}  



//-----------------------------------【ShowHelpText( )函數】----------------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第22個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


