#include <stdio.h>
//:read /home/peter/mao/29_Write_XML_and_YAML_File.cpp
//--------------------------------------【程式說明】-------------------------------------------
//		程式說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程式29
//		程式描述：XML和YAML檔案的寫入
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------


//---------------------------------【頭檔案、命名空間包含部分】-------------------------------
//		描述：包含程式所使用的頭檔案和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/opencv.hpp"  
#include <time.h>  
using namespace cv;  


//-----------------------------------【ShowHelpText( )函數】----------------------------------
//		 描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第29個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


//-----------------------------------【main( )函數】--------------------------------------------
//	描述：控制臺應用程式的入口函數，我們的程式從這里開始
//-----------------------------------------------------------------------------------------------
int main( )  
{  
	//改變console字體顏色
	system("color 5F"); 

	ShowHelpText();

	//初始化
	FileStorage fs("test.yaml", FileStorage::WRITE);  

	//開始檔案寫入
	fs << "frameCount" << 5;  
	time_t rawtime; time(&rawtime);  
	fs << "calibrationDate" << asctime(localtime(&rawtime));  
	Mat cameraMatrix = (Mat_<double>(3,3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);  
	Mat distCoeffs = (Mat_<double>(5,1) << 0.1, 0.01, -0.001, 0, 0);  
	fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;  
	fs << "features" << "[";  
	for( int i = 0; i < 3; i++ )  
	{  
		int x = rand() % 640;  
		int y = rand() % 480;  
		uchar lbp = rand() % 256;  

		fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";  
		for( int j = 0; j < 8; j++ )  
			fs << ((lbp >> j) & 1);  
		fs << "]" << "}";  
	}  
	fs << "]";  
	fs.release();  

	printf("\n檔案讀寫完畢，請在專案目錄下查看產生的檔案~");
	getchar();

	return 0;  
}  
