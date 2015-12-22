#include <stdio.h>
//:read /home/peter/mao/73_minAreaRect.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序73
//		程序描述：建立包圍輪廓的矩形邊界
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;



//-----------------------------------【ShowHelpText( )函數】-----------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{

	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第73個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//輸出一些說明訊息
	printf("\n\n\n\t\t\t歡迎來到【矩形包圍範例】範例程序~\n\n"); 
	printf("\n\n\t按鍵操作說明: \n\n" 
		"\t\t鍵盤按鍵【ESC】、【Q】、【q】- 退出程序\n\n" 
		"\t\t鍵盤按鍵任意鍵 - 重新產生隨機點，並尋找最小面積的包圍矩形\n" );  
}

int main(  )
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
		int count = rng.uniform(3, 103);//隨機產生點的數量
		vector<Point> points;//點值

		//隨機產生點坐標
		for(int  i = 0; i < count; i++ )
		{

			Point point;
			point.x = rng.uniform(image.cols/4, image.cols*3/4);
			point.y = rng.uniform(image.rows/4, image.rows*3/4);

			points.push_back(point);
		}

		//對給定的 2D 點集，尋找最小面積的包圍矩形
		RotatedRect box = minAreaRect(Mat(points));
		Point2f vertex[4];
		box.points(vertex);

		//繪製出隨機顏色的點
		image = Scalar::all(0);
		for( int i = 0; i < count; i++ )
			circle( image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), CV_FILLED, CV_AA );


		//繪製出最小面積的包圍矩形
		for( int i = 0; i < 4; i++ )
			line(image, vertex[i], vertex[(i+1)%4], Scalar(100, 200, 211), 2, CV_AA);

		//顯示視窗
		imshow( "矩形包圍範例", image );
		moveWindow( "矩形包圍範例", 100,100 );

		//按下ESC,Q,或者q，程序退出
		char key = (char)waitKey();
		if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
			break;
	}

	return 0;
}
