#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/71_convexHull.cpp




//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;


//-----------------------------------【ShowHelpText( )函數】----------------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第71個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//輸出一些說明訊息
	printf("\n\t歡迎來到【凸包檢測】範例程序~\n\n"); 
	printf("\n\t按鍵操作說明: \n\n" 
		"\t\t鍵盤按鍵【ESC】、【Q】、【q】- 退出程序\n\n" 
		"\t\t鍵盤按鍵任意鍵 - 重新產生隨機點，並進行凸包檢測\n"  );  

}


//--------------------------------------【main( )函數】-----------------------------------------
//          描述：控制臺應用程序的入口函數，我們的程序從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( )
{
	//改變console字體顏色
	system("color 1F"); 

	//顯示說明文字
	ShowHelpText();

	//初始化變數和隨機值
	Mat image(600, 600, CV_8UC3);
	RNG& rng = theRNG();

	//循環，按下ESC,Q,q鍵程序退出，否則有鍵按下便一直更新
	while(1)
	{
		//參數初始化
		char key;//鍵值
		int count = (unsigned)rng%100 + 3;//隨機產生點的數量
		vector<Point> points; //點值

		//隨機產生點坐標
		for(int i = 0; i < count; i++ )
		{
			Point point;
			point.x = rng.uniform(image.cols/4, image.cols*3/4);
			point.y = rng.uniform(image.rows/4, image.rows*3/4);

			points.push_back(point);
		}

		//檢測凸包
		vector<int> hull;
		convexHull(Mat(points), hull, true);

		//繪製出隨機顏色的點
		image = Scalar::all(0);
		for(int i = 0; i < count; i++ )
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), CV_FILLED, CV_AA);

		//準備參數
		int hullcount = (int)hull.size();//凸包的邊數
		Point point0 = points[hull[hullcount-1]];//連接凸包邊的坐標點

		//繪製凸包的邊
		for(int  i = 0; i < hullcount; i++ )
		{
			Point point = points[hull[i]];
			line(image, point0, point, Scalar(255, 255, 255), 2, CV_AA);
			point0 = point;
		}

		//顯示效果圖
		imshow("凸包檢測範例", image);
		moveWindow("凸包檢測範例", 100,100);

		//按下ESC,Q,或者q，程序退出
		key = (char)waitKey();
		if( key == 27 || key == 'q' || key == 'Q' ) 
			break;
	}

	return 0;
}
