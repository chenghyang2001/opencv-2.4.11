#include <stdio.h>
//:read /home/peter/mao/95_OrbFeatureDetector.cpp

//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序95
//		程序描述：ORB的關鍵點和描述表的提取，使用FLANN-LSH進行比對
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>
using namespace cv;
using namespace std;



//-----------------------------------【ShowHelpText( )函數】----------------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第72個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//輸出一些說明訊息
	printf("\n\t歡迎來到【ORB算法描述提取，配合FLANN-LSH進行比對】範例程序\n"); 
	printf( "\n\n\t按鍵操作說明: \n\n" 
		"\t\t鍵盤按鍵【ESC】- 退出程序\n" );
}


//--------------------------------------【main( )函數】-----------------------------------------
//          描述：控制臺應用程序的入口函數，我們的程序從這里開始執行
//-----------------------------------------------------------------------------------------------
int main(	) 
{
	//【0】改變console字體顏色
	system("color 2F"); 

	//【0】顯示說明文字
	ShowHelpText();

	//【0】載入源圖，顯示並轉化為灰度圖
	Mat srcImage = imread("1.jpg");
	imshow("原始圖",srcImage);
	Mat grayImage;
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	//------------------檢測SIFT特徵點並在圖像中提取物體的描述表----------------------

	//【1】參數定義
	OrbFeatureDetector featureDetector;
	vector<KeyPoint> keyPoints;
	Mat descriptors;

	//【2】使用detect函數檢測出特徵關鍵點，儲存在vector宿主中
	featureDetector.detect(grayImage, keyPoints);

	//【3】計算描述表（特徵向量）
	OrbDescriptorExtractor featureExtractor;
	featureExtractor.compute(grayImage, keyPoints, descriptors);

	//【4】基于FLANN的描述表對象比對
	flann::Index flannIndex(descriptors, flann::LshIndexParams(12, 20, 2), cvflann::FLANN_DIST_HAMMING);

	//【5】初始化視訊採集對象
	VideoCapture cap(0);

	unsigned int frameCount = 0;//幅數

	//【6】輪詢，直到按下ESC鍵退出循環
	while(1)
	{
		double time0 = static_cast<double>(getTickCount( ));//記錄起始時間
		Mat  captureImage, captureImage_gray;//定義兩個Mat變數，用于視訊採集
		cap >>  captureImage;//採集視訊幅
		if( captureImage.empty())//採集為空的處理
			continue;

		//轉化圖像到灰度
		cvtColor( captureImage, captureImage_gray, CV_BGR2GRAY);//採集的視訊幅轉化為灰度圖

		//【7】檢測SIFT關鍵點並提取測試圖像中的描述表
		vector<KeyPoint> captureKeyPoints;
		Mat captureDescription;

		//【8】使用detect函數檢測出特徵關鍵點，儲存在vector宿主中
		featureDetector.detect(captureImage_gray, captureKeyPoints);

		//【9】計算描述表
		featureExtractor.compute(captureImage_gray, captureKeyPoints, captureDescription);

		//【10】比對和測試描述表，取得兩個最鄰近的描述表
		Mat matchIndex(captureDescription.rows, 2, CV_32SC1), matchDistance(captureDescription.rows, 2, CV_32FC1);
		flannIndex.knnSearch(captureDescription, matchIndex, matchDistance, 2, flann::SearchParams());//使用K鄰近算法

		//【11】根據勞氏算法（Lowe's algorithm）選出優秀的比對
		vector<DMatch> goodMatches;
		for(int i = 0; i < matchDistance.rows; i++) 
		{
			if(matchDistance.at<float>(i, 0) < 0.6 * matchDistance.at<float>(i, 1)) 
			{
				DMatch dmatches(i, matchIndex.at<int>(i, 0), matchDistance.at<float>(i, 0));
				goodMatches.push_back(dmatches);
			}
		}

		//【12】繪製並顯示比對視窗
		Mat resultImage;
		drawMatches( captureImage, captureKeyPoints, srcImage, keyPoints, goodMatches, resultImage);
		imshow("比對視窗", resultImage);

		//【13】顯示幅率
		cout << ">幅率= " << getTickFrequency() / (getTickCount() - time0) << endl;

		//按下ESC鍵，則程序退出
		if(char(waitKey(1)) == 27) break;
	}

	return 0;
}


