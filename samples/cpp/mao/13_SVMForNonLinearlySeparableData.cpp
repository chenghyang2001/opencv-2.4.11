#include <stdio.h>
//:read /home/peter/mao/13_SVMForNonLinearlySeparableData.cpp

//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序13
//		程序描述：來自OpenCV安裝目錄下Samples文件夾中的官方範例程序-支持向量機SVM之處理線性不可分資料
//		測試所用操作系統： Windows 7 64bit
//		測試所用IDE版本：Visual Studio 2010
//		測試所用OpenCV版本：	2.4.9
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------



//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#define NTRAINING_SAMPLES   100         // 每類別訓練樣本的數量
#define FRAC_LINEAR_SEP     0.9f        //  部分(Fraction)線性可分的樣本組成部分

using namespace cv;
using namespace std;




//-----------------------------------【ShowHelpText( )函數】----------------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第13個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}

//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-------------------------------------------------------------------------------------------------
int main()
{
	//設定視覺表達的參數
	const int WIDTH = 512, HEIGHT = 512;
	Mat I = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);
	ShowHelpText();

	//--------------------- 【1】隨機建立訓練資料 ---------------------------------------
	Mat trainData(2*NTRAINING_SAMPLES, 2, CV_32FC1);
	Mat labels   (2*NTRAINING_SAMPLES, 1, CV_32FC1);

	RNG rng(100); // 隨機產生值

	//建立訓練資料的線性可分的組成部分
	int nLinearSamples = (int) (FRAC_LINEAR_SEP * NTRAINING_SAMPLES);

	// 為Class1產生隨機點
	Mat trainClass = trainData.rowRange(0, nLinearSamples);
	// 點的x坐標為[0,0.4)
	Mat c = trainClass.colRange(0, 1);
	rng.fill(c, RNG::UNIFORM, Scalar(1), Scalar(0.4 * WIDTH));
	// 點的Y坐標為[0,1)
	c = trainClass.colRange(1,2);
	rng.fill(c, RNG::UNIFORM, Scalar(1), Scalar(HEIGHT));

	// 為Class2產生隨機點
	trainClass = trainData.rowRange(2*NTRAINING_SAMPLES-nLinearSamples, 2*NTRAINING_SAMPLES);
	// 點的x坐標為[0.6, 1]
	c = trainClass.colRange(0 , 1); 
	rng.fill(c, RNG::UNIFORM, Scalar(0.6*WIDTH), Scalar(WIDTH));
	// 點的Y坐標為[0, 1)
	c = trainClass.colRange(1,2);
	rng.fill(c, RNG::UNIFORM, Scalar(1), Scalar(HEIGHT));

	//------------------建立訓練資料的非線性可分組成部分 ---------------

	// 隨機產生Class1和Class2的點
	trainClass = trainData.rowRange(  nLinearSamples, 2*NTRAINING_SAMPLES-nLinearSamples);
	// 點的x坐標為[0.4, 0.6)
	c = trainClass.colRange(0,1);
	rng.fill(c, RNG::UNIFORM, Scalar(0.4*WIDTH), Scalar(0.6*WIDTH)); 
	// 點的y坐標為[0, 1)
	c = trainClass.colRange(1,2);
	rng.fill(c, RNG::UNIFORM, Scalar(1), Scalar(HEIGHT));

	//-------------------------設定類別標簽 ---------------------------------
	labels.rowRange(                0,   NTRAINING_SAMPLES).setTo(1);  // Class 1
	labels.rowRange(NTRAINING_SAMPLES, 2*NTRAINING_SAMPLES).setTo(2);  // Class 2

	//------------------------ 2. 設定支持向量機的參數 --------------------
	CvSVMParams params;
	params.svm_type    = SVM::C_SVC;
	params.C           = 0.1;
	params.kernel_type = SVM::LINEAR;
	params.term_crit   = TermCriteria(CV_TERMCRIT_ITER, (int)1e7, 1e-6);

	//------------------------ 3. 訓練支持向量機 ----------------------------------------------------
	cout << "Starting training process" << endl;
	CvSVM svm;
	svm.train(trainData, labels, Mat(), Mat(), params);
	cout << "Finished training process" << endl;

	//------------------------ 4. 標出決策區域（decision regions） ----------------------------------------
	Vec3b green(0,100,0), blue (100,0,0);
	for (int i = 0; i < I.rows; ++i)
		for (int j = 0; j < I.cols; ++j)
		{
			Mat sampleMat = (Mat_<float>(1,2) << i, j);
			float response = svm.predict(sampleMat);

			if      (response == 1)    I.at<Vec3b>(j, i)  = green;
			else if (response == 2)    I.at<Vec3b>(j, i)  = blue;
		}

		//----------------------- 5. 顯示訓練資料（training data） --------------------------------------------
		int thick = -1;
		int lineType = 8;
		float px, py;
		// Class 1
		for (int i = 0; i < NTRAINING_SAMPLES; ++i)
		{
			px = trainData.at<float>(i,0);
			py = trainData.at<float>(i,1);
			circle(I, Point( (int) px,  (int) py ), 3, Scalar(0, 255, 0), thick, lineType);
		}
		// Class 2
		for (int i = NTRAINING_SAMPLES; i <2*NTRAINING_SAMPLES; ++i)
		{
			px = trainData.at<float>(i,0);
			py = trainData.at<float>(i,1);
			circle(I, Point( (int) px, (int) py ), 3, Scalar(255, 0, 0), thick, lineType);
		}

		//------------------------- 6. 顯示支持向量（support vectors） --------------------------------------------
		thick = 2;
		lineType  = 8;
		int x     = svm.get_support_vector_count();

		for (int i = 0; i < x; ++i)
		{
			const float* v = svm.get_support_vector(i);
			circle( I,  Point( (int) v[0], (int) v[1]), 6, Scalar(128, 128, 128), thick, lineType);
		}

		imwrite("result.png", I);                      //儲存圖像到文件
		imshow("SVM for Non-Linear Training Data", I); // 顯示最終視窗
		waitKey(0);
}
