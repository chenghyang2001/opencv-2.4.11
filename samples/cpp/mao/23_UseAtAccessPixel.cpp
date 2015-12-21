#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f23
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1a\u7528\u52d5\u614b\u4f4d\u5740\u8a08\u7b97\u914d\u5408at\u8a2a\u554f\u50cf\u7d20
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------




//-----------------------------\u3010\u982d\u6a94\u6848\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011------------------------------
//          \u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6a94\u6848\u548c\u547d\u540d\u7a7a\u9593
//-----------------------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  
using namespace std;  
using namespace cv;  

//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011-----------------------------------
//          \u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
void colorReduce(Mat& inputImage, Mat& outputImage, int div);  
void ShowHelpText();


//--------------------------------------\u3010main( )\u51fd\u6578\u3011---------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main( )  
{  
	//\u30101\u3011\u5efa\u7acb\u539f\u59cb\u5716\u4e26\u986f\u793a
	Mat srcImage = imread("1.jpg");  
	imshow("\u539f\u59cb\u5716\u50cf",srcImage);  

	//\u30102\u3011\u6309\u539f\u59cb\u5716\u7684\u53c3\u6578\u898f\u683c\u4f86\u5efa\u7acb\u5efa\u7acb\u6548\u679c\u5716
	Mat dstImage;
	dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());//\u6548\u679c\u5716\u7684\u5927\u5c0f\u3001\u985e\u5225\u5225\u578b\u8207\u539f\u5716\u5f62\u76f8\u540c 

	ShowHelpText();

	//\u30103\u3011\u8a18\u9304\u8d77\u59cb\u6642\u9593
	double time0 = static_cast<double>(getTickCount());  

	//\u30104\u3011\u4f7f\u7528\u984f\u8272\u7a7a\u9593\u7e2e\u6e1b\u51fd\u6578
	colorReduce(srcImage,dstImage,32);  

	//\u30105\u3011\u8a08\u7b97\u57f7\u884c\u6642\u9593\u4e26\u8f38\u51fa
	time0 = ((double)getTickCount() - time0)/getTickFrequency();
	cout<<"\u6b64\u65b9\u6cd5\u57f7\u884c\u6642\u9593\u70ba\uff1a "<<time0<<"\u79d2"<<endl;  //\u8f38\u51fa\u57f7\u884c\u6642\u9593

	//\u30106\u3011\u986f\u793a\u6548\u679c\u5716
	imshow("\u6548\u679c\u5716",dstImage);  
	waitKey(0);  
}  


//----------------------------------\u3010colorReduce( )\u51fd\u6578\u3011-------------------------------
//          \u63cf\u8ff0\uff1a\u4f7f\u7528\u3010\u52d5\u614b\u4f4d\u5740\u904b\u7b97\u914d\u5408at\u3011\u65b9\u6cd5\u7248\u672c\u7684\u984f\u8272\u7a7a\u9593\u7e2e\u6e1b\u51fd\u6578
//----------------------------------------------------------------------------------------------
void colorReduce(Mat& inputImage, Mat& outputImage, int div)  
{  
	//\u53c3\u6578\u6e96\u5099
	outputImage = inputImage.clone();  //\u62f7\u8c9d\u5be6\u53c3\u5230\u81e8\u6642\u8b8a\u6578
	int rowNumber = outputImage.rows;  //\u884c\u6578
	int colNumber = outputImage.cols;  //\u5217\u6578

	//\u5b58\u53d6\u5f69\u8272\u5716\u50cf\u50cf\u7d20
	for(int i = 0;i < rowNumber;i++)  
	{  
		for(int j = 0;j < colNumber;j++)  
		{  	
			// ------------------------\u3010\u958b\u59cb\u8655\u7406\u6bcf\u500b\u50cf\u7d20\u3011--------------------
			outputImage.at<Vec3b>(i,j)[0] =  outputImage.at<Vec3b>(i,j)[0]/div*div + div/2;  //\u85cd\u8272\u901a\u9053
			outputImage.at<Vec3b>(i,j)[1] =  outputImage.at<Vec3b>(i,j)[1]/div*div + div/2;  //\u7da0\u8272\u901a\u9053
			outputImage.at<Vec3b>(i,j)[2] =  outputImage.at<Vec3b>(i,j)[2]/div*div + div/2;  //\u7d05\u662f\u901a\u9053
			// -------------------------\u3010\u8655\u7406\u7d50\u675f\u3011----------------------------
		}  // \u884c\u8655\u7406\u7d50\u675f     
	}  
}  


//-------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011--------------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c23\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}




