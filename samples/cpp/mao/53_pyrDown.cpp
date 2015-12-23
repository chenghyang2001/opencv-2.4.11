#include <stdio.h>
#include <stdio.h>
//:read /home/peter/mao/53_pyrDown.cpp




//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

//-----------------------------------【main( )函數】-----------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-----------------------------------------------------------------------------------------------
int main( )
{
	//載入原始圖   
	Mat srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");  //專案目錄下應該有一張名為1.jpg的素材圖
	Mat tmpImage,dstImage;//臨時變數和目標圖的定義
	tmpImage=srcImage;//將原始圖賦給臨時變數

	//顯示原始圖  
	imshow("【原始圖】", srcImage);  
	//進行向下取樣操作
	pyrDown( tmpImage, dstImage, Size( tmpImage.cols/2, tmpImage.rows/2 ) );
	//顯示效果圖  
	imshow("【效果圖】", dstImage);  

	waitKey(0);  

	return 0;  
}
