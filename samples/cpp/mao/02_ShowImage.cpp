
#include <stdio.h>

#include <opencv2/opencv.hpp>  //頭文件
using namespace cv;  //包含cv命名空間

int main( )
{    
	// 【1】讀入一張圖形，載入圖像
//        Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");
//        Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg",CV_LOAD_IMAGE_GRAYSCALE); //  CV_LOAD_IMAGE_GRAYSCALE
	Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg",CV_LOAD_IMAGE_COLOR ); //  CV_LOAD_IMAGE_GRAYSCALE

	// 【2】顯示載入的圖形
	imshow("【原始圖】",srcImage);
	moveWindow("【原始圖】",100,100);

	// 【3】等待任意按鍵按下
	waitKey(0);
}  
