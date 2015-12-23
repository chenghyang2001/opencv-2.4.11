
#include <stdio.h>
#include <stdio.h>
#include <stdio.h>


//---------------------------------【頭檔案、命名空間包含部分】----------------------------
//		描述：包含程式所使用的頭檔案和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;



//-----------------------------------【ShowHelpText( )函數】-----------------------------
//		 描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第79個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


//--------------------------------------【main( )函數】-----------------------------------------
//          描述：控制臺應用程式的入口函數，我們的程式從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( )
{

	//【1】載入源圖，轉化為HSV顏色模型
	Mat srcImage, hsvImage;
	srcImage=imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");
	cvtColor(srcImage,hsvImage, CV_BGR2HSV);

	system("color 2F");
	ShowHelpText();

	//【2】參數準備
	//將色調量化為30個等級，將飽和度量化為32個等級
	int hueBinNum = 30;//色調的直條圖直條數量
	int saturationBinNum = 32;//飽和度的直條圖直條數量
	int histSize[ ] = {hueBinNum, saturationBinNum};
	// 定義色調的變化范圍為0到179
	float hueRanges[] = { 0, 180 };
	//定義飽和度的變化范圍為0（黑、白、灰）到255（純光譜顏色）
	float saturationRanges[] = { 0, 256 };
	const float* ranges[] = { hueRanges, saturationRanges };
	MatND dstHist;
	//參數準備，calcHist函數中將計算第0通道和第1通道的直條圖
	int channels[] = {0, 1};

	//【3】正式使用calcHist，進行直條圖計算
	calcHist( &hsvImage,//輸入的數組
		1, //數組個數為1
		channels,//通道索引
		Mat(), //不使用掩膜
		dstHist, //輸出的目標直條圖
		2, //需要計算的直條圖的維度為2
		histSize, //存放每個維度的直條圖尺寸的數組
		ranges,//每一維數值的取值范圍數組
		true, // 指示直條圖是否均勻的標識表，true表示均勻的直條圖
		false );//累計標識表，false表示直條圖在設定階段會被清零

	//【4】為繪製直條圖準備參數
	double maxValue=0;//最大值
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);//查詢數組和子數組的全局最小值和最大值存入maxValue中
	int scale = 10;
	Mat histImg = Mat::zeros(saturationBinNum*scale, hueBinNum*10, CV_8UC3);

	//【5】雙層循環，進行直條圖繪製
	for( int hue = 0; hue < hueBinNum; hue++ )
		for( int saturation = 0; saturation < saturationBinNum; saturation++ )
		{
			float binValue = dstHist.at<float>(hue, saturation);//直條圖組距的值
			int intensity = cvRound(binValue*255/maxValue);//固定度

			//正式進行繪製
			rectangle( histImg, Point(hue*scale, saturation*scale),
				Point( (hue+1)*scale - 1, (saturation+1)*scale - 1),
				Scalar::all(intensity),
				CV_FILLED );
		}

		//【6】顯示效果圖
		imshow( "素材圖", srcImage );
		moveWindow( "素材圖", 100,100 );

		imshow( "H-S 直條圖", histImg );
		moveWindow( "H-S 直條圖", 1000,100 );

		waitKey();
}
