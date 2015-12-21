#include <stdio.h>
//:read /home/peter/mao/25_ImageBlending.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序25
//		程序描述：初級圖像混合
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------


//---------------------------------【頭文件、命名空間包含部分】-------------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------                                                                                 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


//-----------------------------------【全局函數宣告部分】--------------------------------------
//	描述：全局函數宣告
//-----------------------------------------------------------------------------------------------
bool  ROI_AddImage();
bool  LinearBlending();
bool  ROI_LinearBlending();
void   ShowHelpText();

//-----------------------------------【main( )函數】--------------------------------------------
//	描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main(   )
{
	system("color 6F");
 
	ShowHelpText();

	if(ROI_AddImage( )&& LinearBlending( )&&ROI_LinearBlending( ))
	{
		cout<<endl<<"\n執行成功，得出了需要的圖像~! ";
	}

	waitKey(0);
	return 0;
}


//-----------------------------------【ShowHelpText( )函數】----------------------------------
//		 描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第25個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}




//----------------------------------【ROI_AddImage( )函數】----------------------------------
// 函數名：ROI_AddImage（）
//	描述：利用感興趣區域ROI實現圖像疊加
//----------------------------------------------------------------------------------------------
bool  ROI_AddImage()
{

	// 【1】讀入圖像
	Mat srcImage1= imread("dota_pa.jpg");
	Mat logoImage= imread("dota_logo.jpg");
	if( !srcImage1.data ) { printf("讀取srcImage1錯誤~！ \n"); return false; }
	if( !logoImage.data ) { printf("讀取logoImage錯誤~！ \n"); return false; }

	// 【2】定義一個Mat類別型並給其設定ROI區域
	Mat imageROI= srcImage1(Rect(200,250,logoImage.cols,logoImage.rows));

	// 【3】加載掩模（必須是灰度圖）
	Mat mask= imread("dota_logo.jpg",0);

	//【4】將掩膜拷貝到ROI
	logoImage.copyTo(imageROI,mask);

	// 【5】顯示結果
	namedWindow("<1>利用ROI實現圖像疊加範例視窗");
	imshow("<1>利用ROI實現圖像疊加範例視窗",srcImage1);

	return true;
}


//---------------------------------【LinearBlending（）函數】-------------------------------------
// 函數名：LinearBlending（）
// 描述：利用cv::addWeighted（）函數實現圖像線性混合
//--------------------------------------------------------------------------------------------
bool  LinearBlending()
{
	//【0】定義一些局部變數
	double alphaValue = 0.5; 
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	// 【1】讀取圖像 ( 兩幅圖形需為同樣的類別型和尺寸 )
	srcImage2 = imread("mogu.jpg");
	srcImage3 = imread("rain.jpg");

	if( !srcImage2.data ) { printf("讀取srcImage2錯誤！ \n"); return false; }
	if( !srcImage3.data ) { printf("讀取srcImage3錯誤！ \n"); return false; }

	// 【2】進行圖像混合加權操作
	betaValue = ( 1.0 - alphaValue );
	addWeighted( srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	// 【3】顯示原圖視窗
	imshow( "<2>線性混合範例視窗【原圖】", srcImage2 );
	imshow( "<3>線性混合範例視窗【效果圖】", dstImage );

	return true;

}

//---------------------------------【ROI_LinearBlending（）】-------------------------------------
// 函數名：ROI_LinearBlending（）
// 描述：線性混合實現函數,指定區域線性圖像混合.利用cv::addWeighted（）函數結合定義
//			  感興趣區域ROI，實現自定義區域的線性混合
//--------------------------------------------------------------------------------------------
bool  ROI_LinearBlending()
{

	//【1】讀取圖像
	Mat srcImage4= imread("dota_pa.jpg",1);
	Mat logoImage= imread("dota_logo.jpg");

	if( !srcImage4.data ) { printf("讀取srcImage4錯誤~！ \n"); return false; }
	if( !logoImage.data ) { printf("讀取logoImage錯誤~！ \n"); return false; }

	//【2】定義一個Mat類別型並給其設定ROI區域
	Mat imageROI;
	//方法一
	imageROI= srcImage4(Rect(200,250,logoImage.cols,logoImage.rows));
	//方法二
	//imageROI= srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));

	//【3】將logo加到原圖上
	addWeighted(imageROI,0.5,logoImage,0.3,0.,imageROI);

	//【4】顯示結果
	imshow("<4>區域線性圖像混合範例視窗",srcImage4);

	return true;
}

