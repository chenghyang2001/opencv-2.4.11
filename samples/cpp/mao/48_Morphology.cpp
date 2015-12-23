#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/48_Morphology.cpp




//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;


//-----------------------------------【全局變數宣告部分】-----------------------------------
//		描述：全局變數宣告
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage;//原始圖和效果圖
int g_nElementShape = MORPH_RECT;//元素結構的形狀

//變數接收的TrackBar位置參數
int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackHatNum = 0;



//-----------------------------------【全局函數宣告部分】--------------------------------------
//		描述：全局函數宣告
//-----------------------------------------------------------------------------------------------
static void on_OpenClose(int, void*);//回調函數
static void on_ErodeDilate(int, void*);//回調函數
static void on_TopBlackHat(int, void*);//回調函數
static void ShowHelpText();


//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main( )
{
	//改變console字體顏色
	system("color 2F");  

	ShowHelpText();

	//載入原圖
	g_srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");
	if( !g_srcImage.data ) { printf("Oh，no，讀取srcImage錯誤~！ \n"); return false; }

	//顯示原始圖
	namedWindow("【原始圖】");
	imshow("【原始圖】", g_srcImage);

	//建立三個視窗
	namedWindow("【開運算/閉運算】",1);
	namedWindow("【腐蝕/膨脹】",1);
	namedWindow("【頂帽/黑帽】",1);

	//參數賦值
	g_nOpenCloseNum=9;
	g_nErodeDilateNum=9;
	g_nTopBlackHatNum=2;

	//分別為三個視窗建立捲軸
	createTrackbar("偏移量", "【開運算/閉運算】",&g_nOpenCloseNum,g_nMaxIterationNum*2+1,on_OpenClose);
	createTrackbar("偏移量", "【腐蝕/膨脹】",&g_nErodeDilateNum,g_nMaxIterationNum*2+1,on_ErodeDilate);
	createTrackbar("偏移量", "【頂帽/黑帽】",&g_nTopBlackHatNum,g_nMaxIterationNum*2+1,on_TopBlackHat);

	//輪詢取得按鍵訊息
	while(1)
	{
		int c;

		//執行回調函數
		on_OpenClose(g_nOpenCloseNum, 0);
		on_ErodeDilate(g_nErodeDilateNum, 0);
		on_TopBlackHat(g_nTopBlackHatNum,0);

		//取得按鍵
		c = waitKey(0);

		//按下鍵盤按鍵Q或者ESC，程序退出
		if( (char)c == 'q'||(char)c == 27 )
			break;
		//按下鍵盤按鍵1，使用橢圓(Elliptic)結構元素結構元素MORPH_ELLIPSE
		if( (char)c == 49 )//鍵盤按鍵1的ASII碼為49
			g_nElementShape = MORPH_ELLIPSE;
		//按下鍵盤按鍵2，使用矩形(Rectangle)結構元素MORPH_RECT
		else if( (char)c == 50 )//鍵盤按鍵2的ASII碼為50
			g_nElementShape = MORPH_RECT;
		//按下鍵盤按鍵3，使用十字形(Cross-shaped)結構元素MORPH_CROSS
		else if( (char)c == 51 )//鍵盤按鍵3的ASII碼為51
			g_nElementShape = MORPH_CROSS;
		//按下鍵盤按鍵space，在矩形、橢圓、十字形結構元素中循環
		else if( (char)c == ' ' )
			g_nElementShape = (g_nElementShape + 1) % 3;
	}

	return 0;
}


//-----------------------------------【on_OpenClose( )函數】----------------------------------
//		描述：【開運算/閉運算】視窗的回調函數
//-----------------------------------------------------------------------------------------------
static void on_OpenClose(int, void*)
{
	//偏移量的定義
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;//偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;//偏移量絕對值
	//自定義核
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset) );
	//進行操作
	if( offset < 0 )
		morphologyEx(g_srcImage, g_dstImage, CV_MOP_OPEN, element);
	else
		morphologyEx(g_srcImage, g_dstImage, CV_MOP_CLOSE, element);
	//顯示圖像
	imshow("【開運算/閉運算】",g_dstImage);
}


//-----------------------------------【on_ErodeDilate( )函數】----------------------------------
//		描述：【腐蝕/膨脹】視窗的回調函數
//-----------------------------------------------------------------------------------------------
static void on_ErodeDilate(int, void*)
{
	//偏移量的定義
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;	//偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;//偏移量絕對值
	//自定義核
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset) );
	//進行操作
	if( offset < 0 )
		erode(g_srcImage, g_dstImage, element);
	else
		dilate(g_srcImage, g_dstImage, element);
	//顯示圖像
	imshow("【腐蝕/膨脹】",g_dstImage);
}


//-----------------------------------【on_TopBlackHat( )函數】--------------------------------
//		描述：【頂帽運算/黑帽運算】視窗的回調函數
//----------------------------------------------------------------------------------------------
static void on_TopBlackHat(int, void*)
{
	//偏移量的定義
	int offset = g_nTopBlackHatNum - g_nMaxIterationNum;//偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;//偏移量絕對值
	//自定義核
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset) );
	//進行操作
	if( offset < 0 )
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT , element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
	//顯示圖像
	imshow("【頂帽/黑帽】",g_dstImage);
}

//-----------------------------------【ShowHelpText( )函數】----------------------------------
//		描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第48個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//輸出一些說明訊息
	printf("\n\t請調整捲軸觀察圖像效果\n\n");
	printf( "\n\t按鍵操作說明: \n\n"
		"\t\t鍵盤按鍵【ESC】或者【Q】- 退出程序\n"
		"\t\t鍵盤按鍵【1】- 使用橢圓(Elliptic)結構元素\n"
		"\t\t鍵盤按鍵【2】- 使用矩形(Rectangle )結構元素\n"
		"\t\t鍵盤按鍵【3】- 使用十字型(Cross-shaped)結構元素\n"
		"\t\t鍵盤按鍵【空格SPACE】- 在矩形、橢圓、十字形結構元素中循環\n"	);
}
