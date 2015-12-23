
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;


int main( )
{
	//-----------------------------------【一、圖像的載入和顯示】---------------------------------
	//	描述：以下三行程式碼用于完成圖像的載入和顯示
	//--------------------------------------------------------------------------------------------------

#if 0
	Mat girl=imread("/home/peter/opencv-2.4.11/samples/cpp/mao/girl.jpg"); //載入圖像到Mat
	namedWindow("【1】動漫圖"); //建立一個名為 "【1】動漫圖"的視窗  
	imshow("【1】動漫圖",girl);//顯示名為 "【1】動漫圖"的視窗  
	moveWindow("【1】動漫圖",100,100);//顯示名為 "【1】動漫圖"的視窗  
#endif

	//-----------------------------------【二、初級圖像混合】--------------------------------------
	//	描述：二、初級圖像混合
	//--------------------------------------------------------------------------------------------------
	//載入圖形
	Mat image= imread("/home/peter/opencv-2.4.11/samples/cpp/mao/dota.jpg",199);
	Mat logo= imread("/home/peter/opencv-2.4.11/samples/cpp/mao/dota_logo.jpg");

	//載入後先顯示
	namedWindow("【2】原畫圖");
	imshow("【2】原畫圖",image);
	moveWindow("【2】原畫圖",100,100);

	namedWindow("【3】logo圖");
	imshow("【3】logo圖",logo);
	moveWindow("【3】logo圖",1000,100);

	// 定義一個Mat類別型，用于存放，圖像的ROI
	Mat imageROI;
	//方法一
//        imageROI= image(Rect(800,350,logo.cols,logo.rows));
	imageROI= image(Rect(100,100,logo.cols,logo.rows));
	//方法二
	//imageROI= image(Range(350,350+logo.rows),Range(800,800+logo.cols));

	// 將logo加到原圖上
//        addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);
//        addWeighted(imageROI, 1.0, logo, 0.3, 0., imageROI);
//        addWeighted(imageROI, 0.0, logo, 1.0, 0., imageROI);
//        addWeighted(imageROI, 0.0, logo, 0.5, 0., imageROI);
	addWeighted(imageROI, 0.5, logo, 0.5, 0., imageROI);

	//顯示結果
	namedWindow("【4】原畫+logo圖");
	imshow("【4】原畫+logo圖",image);
	moveWindow("【4】原畫+logo圖",1000,400);

	//-----------------------------------【三、圖像的輸出】--------------------------------------
	//	描述：將一個Mat圖像輸出到圖像文件
	//-----------------------------------------------------------------------------------------------
	//輸出一張jpg圖形到專案目錄下
	imwrite("由imwrite產生的圖形.jpg",image);

	waitKey();

	return 0;
}
