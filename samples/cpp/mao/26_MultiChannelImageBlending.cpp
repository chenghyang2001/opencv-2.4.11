#include <stdio.h>
//:read /home/peter/mao/26_MultiChannelImageBlending.cpp

//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序26
//		程序描述：分離顏色通道&多通道圖像混合
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------

//-----------------------------------【頭文件包含部分】---------------------------------------
//	描述：包含程序所依賴的頭文件
//------------------------------------------------------------------------------------------------                                                                                     
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

//-----------------------------------【命名空間宣告部分】---------------------------------------
//	描述：包含程序所使用的命名空間
//-------------------------------------------------------------------------------------------------   
using namespace cv;
using namespace std;


//-----------------------------------【全局函數宣告部分】--------------------------------------
//	描述：全局函數宣告
//-----------------------------------------------------------------------------------------------
bool  MultiChannelBlending();
void ShowHelpText();


//-----------------------------------【main( )函數】------------------------------------------
//	描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main(   )
{
	system("color 9F");

	ShowHelpText( );

	if(MultiChannelBlending( ))
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
	printf("\n\n\t\t\t此為本書OpenCV2版的第26個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}






//-----------------------------【MultiChannelBlending( )函數】--------------------------------
//	描述：多通道混合的實現函數
//-----------------------------------------------------------------------------------------------
bool  MultiChannelBlending()
{
	//【0】定義相關變數
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	Mat  imageBlueChannel;

	//=================【藍色通道部分】=================
	//	描述：多通道混合-藍色分量部分
	//============================================

	// 【1】讀入圖形
	logoImage= imread("/home/peter/opencv-2.4.11/samples/cpp/mao/dota_logo.jpg",0);
	srcImage= imread("/home/peter/opencv-2.4.11/samples/cpp/mao/dota_jugg.jpg");

	if( !logoImage.data ) { printf("Oh，no，讀取logoImage錯誤~！ \n"); return false; }
	if( !srcImage.data ) { printf("Oh，no，讀取srcImage錯誤~！ \n"); return false; }

	//【2】把一個3通道圖像轉換成3個單通道圖像
	split(srcImage,channels);//分離色彩通道

	//【3】將原圖的藍色通道引用返回給imageBlueChannel，注意是引用，相當于兩者等價，修改其中一個另一個跟著變
	imageBlueChannel= channels.at(0);
	//【4】將原圖的藍色通道的（500,250）坐標處右下方的一塊區域和logo圖進行加權操作，將得到的混合結果存到imageBlueChannel中
	addWeighted(imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,0,imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)));

	//【5】將三個單通道重新合並成一個三通道
	merge(channels,srcImage);

	//【6】顯示效果圖
	namedWindow(" <1>游戲原畫+logo藍色通道");
	imshow(" <1>游戲原畫+logo藍色通道",srcImage);
	moveWindow(" <1>游戲原畫+logo藍色通道",100,100);


	//=================【綠色通道部分】=================
	//	描述：多通道混合-綠色分量部分
	//============================================

	//【0】定義相關變數
	Mat  imageGreenChannel;

	//【1】重新讀入圖形
	logoImage= imread("/home/peter/opencv-2.4.11/samples/cpp/mao/dota_logo.jpg",0);
	srcImage= imread("/home/peter/opencv-2.4.11/samples/cpp/mao/dota_jugg.jpg");

	if( !logoImage.data ) { printf("讀取logoImage錯誤~！ \n"); return false; }
	if( !srcImage.data ) { printf("讀取srcImage錯誤~！ \n"); return false; }

	//【2】將一個三通道圖像轉換成三個單通道圖像
	split(srcImage,channels);//分離色彩通道

	//【3】將原圖的綠色通道的引用返回給imageBlueChannel，注意是引用，相當于兩者等價，修改其中一個另一個跟著變
	imageGreenChannel= channels.at(1);
	//【4】將原圖的綠色通道的（500,250）坐標處右下方的一塊區域和logo圖進行加權操作，將得到的混合結果存到imageGreenChannel中
	addWeighted(imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,0.,imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)));

	//【5】將三個獨立的單通道重新合並成一個三通道
	merge(channels,srcImage);

	//【6】顯示效果圖
	namedWindow("<2>游戲原畫+logo綠色通道");
	imshow("<2>游戲原畫+logo綠色通道",srcImage);
	moveWindow("<2>游戲原畫+logo綠色通道",1000,100);



	//=================【紅色通道部分】=================
	//	描述：多通道混合-紅色分量部分
	//============================================

	//【0】定義相關變數
	Mat  imageRedChannel;

	//【1】重新讀入圖形
	logoImage= imread("/home/peter/opencv-2.4.11/samples/cpp/mao/dota_logo.jpg",0);
	srcImage= imread("/home/peter/opencv-2.4.11/samples/cpp/mao/dota_jugg.jpg");

	if( !logoImage.data ) { printf("Oh，no，讀取logoImage錯誤~！ \n"); return false; }
	if( !srcImage.data ) { printf("Oh，no，讀取srcImage錯誤~！ \n"); return false; }

	//【2】將一個三通道圖像轉換成三個單通道圖像
	split(srcImage,channels);//分離色彩通道

	//【3】將原圖的紅色通道引用返回給imageBlueChannel，注意是引用，相當于兩者等價，修改其中一個另一個跟著變
	imageRedChannel= channels.at(2);
	//【4】將原圖的紅色通道的（500,250）坐標處右下方的一塊區域和logo圖進行加權操作，將得到的混合結果存到imageRedChannel中
	addWeighted(imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,0.,imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)));

	//【5】將三個獨立的單通道重新合並成一個三通道
	merge(channels,srcImage);

	//【6】顯示效果圖
	namedWindow("<3>游戲原畫+logo紅色通道 ");
	imshow("<3>游戲原畫+logo紅色通道 ",srcImage);
	moveWindow("<3>游戲原畫+logo紅色通道 ",300,300);

	return true;
}


