#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f85
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1acornerHarris\u51fd\u6578\u7528\u6cd5\u7bc4\u4f8b
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------   
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;  

int main()  
{  
	//\u4ee5\u7070\u5ea6\u6a21\u5f0f\u8f09\u5165\u5716\u50cf\u4e26\u986f\u793a
	Mat srcImage = imread("1.jpg", 0);  
	imshow("\u539f\u59cb\u5716", srcImage);  

	//\u9032\u884cHarris\u89d2\u9ede\u6aa2\u6e2c\u627e\u51fa\u89d2\u9ede
	Mat cornerStrength;  
	cornerHarris(srcImage, cornerStrength, 2, 3, 0.01);

	//\u5c0d\u7070\u5ea6\u5716\u9032\u884c\u95be\u503c\u64cd\u4f5c\uff0c\u5f97\u5230\u4e8c\u503c\u5716\u4e26\u986f\u793a  
	Mat harrisCorner;  
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);  
	imshow("\u89d2\u9ede\u6aa2\u6e2c\u5f8c\u7684\u4e8c\u503c\u6548\u679c\u5716", harrisCorner);  

	waitKey(0);  
	return 0;  
}  
