#include <stdio.h>
//:read /home/peter/mao/92_FLANN_and_SURF.cpp
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序92
//		程序描述：FLANN結合SURF進行關鍵點的描述和比對
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


//-----------------------------------【ShowHelpText( )函數】-----------------------------
//		 描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第92個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}


//--------------------------------------【main( )函數】-----------------------------------------
//          描述：控制臺應用程序的入口函數，我們的程序從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( ) 
{
	//【0】改變console字體顏色
	system("color 6F"); 

	void ShowHelpText();

	//【1】載入圖像、顯示並轉化為灰度圖
	Mat trainImage = imread("1.jpg"), trainImage_gray;
	imshow("原始圖",trainImage);
	cvtColor(trainImage, trainImage_gray, CV_BGR2GRAY);

	//【2】檢測Surf關鍵點、提取訓練圖像描述表
	vector<KeyPoint> train_keyPoint;
	Mat trainDescriptor;
	SurfFeatureDetector featureDetector(80);
	featureDetector.detect(trainImage_gray, train_keyPoint);
	SurfDescriptorExtractor featureExtractor;
	featureExtractor.compute(trainImage_gray, train_keyPoint, trainDescriptor);

	//【3】建立基于FLANN的描述表比對對象
	FlannBasedMatcher matcher;
	vector<Mat> train_desc_collection(1, trainDescriptor);
	matcher.add(train_desc_collection);
	matcher.train();

	//【4】建立視訊對象、定義幅率
	VideoCapture cap(0);
	unsigned int frameCount = 0;//幅數

	//【5】不斷循環，直到q鍵被按下
	while(char(waitKey(1)) != 'q')
	{
		//<1>參數設定
		int64 time0 = getTickCount();
		Mat testImage, testImage_gray;
		cap >> testImage;//採集視訊到testImage中
		if(testImage.empty())
			continue;

		//<2>轉化圖像到灰度
		cvtColor(testImage, testImage_gray, CV_BGR2GRAY);

		//<3>檢測S關鍵點、提取測試圖像描述表
		vector<KeyPoint> test_keyPoint;
		Mat testDescriptor;
		featureDetector.detect(testImage_gray, test_keyPoint);
		featureExtractor.compute(testImage_gray, test_keyPoint, testDescriptor);

		//<4>比對訓練和測試描述表
		vector<vector<DMatch> > matches;
		matcher.knnMatch(testDescriptor, matches, 2);

		// <5>根據勞氏算法（Lowe's algorithm），得到優秀的比對點
		vector<DMatch> goodMatches;
		for(unsigned int i = 0; i < matches.size(); i++)
		{
			if(matches[i][0].distance < 0.6 * matches[i][1].distance)
				goodMatches.push_back(matches[i][0]);
		}

		//<6>繪製比對點並顯示視窗
		Mat dstImage;
		drawMatches(testImage, test_keyPoint, trainImage, train_keyPoint, goodMatches, dstImage);
		imshow("比對視窗", dstImage);

		//<7>輸出幅率訊息
		cout << "現在幅率為：" << getTickFrequency() / (getTickCount() - time0) << endl;
	}

	return 0;
}
