
#include <stdio.h>


//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------   
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;  

int main()  
{  
	//以灰度模式載入圖像並顯示
	Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/rain.jpg", 0);  // must use grayscale one
//        Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg", 0);  // must use grayscale one
//        Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");    // can not use color one
	imshow("原始圖", srcImage);  
	moveWindow("原始圖", 100,100);  

	//進行Harris角點檢測找出角點
	Mat cornerStrength;  
	cornerHarris(srcImage, cornerStrength, 2, 3, 0.01);

	//對灰度圖進行閾值操作，得到二值圖並顯示  
	Mat harrisCorner;  
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);  
	imshow("角點檢測後的二值效果圖", harrisCorner);  
	moveWindow("角點檢測後的二值效果圖", 1000,100 );  

	waitKey(0);  
	return 0;  
}  
