#include <stdio.h>
//:read /home/peter/mao/12_SupportVectorMachines.cpp
//


//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//-------------------------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
using namespace cv;

//--------------------------------【help( )函數】----------------------------------------------
//		描述：輸出說明訊息
//-------------------------------------------------------------------------------------------------

//-----------------------------------【ShowHelpText( )函數】----------------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第12個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}

//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-------------------------------------------------------------------------------------------------
int main()
{
	// 視覺表達資料的設定（Data for visual representation）
	int width = 512, height = 512;
	Mat image = Mat::zeros(height, width, CV_8UC3);

	//建立訓練資料（ Set up training data）
	float labels[4] = {1.0, -1.0, -1.0, -1.0};
	Mat labelsMat(3, 1, CV_32FC1, labels);

	float trainingData[4][2] = { {501, 10}, {255, 10}, {501, 255}, {10, 501} };
	Mat trainingDataMat(3, 2, CV_32FC1, trainingData);

	ShowHelpText();

	//設定支持向量機的參數（Set up SVM's parameters）
	CvSVMParams params;
	params.svm_type    = CvSVM::C_SVC;
	params.kernel_type = CvSVM::LINEAR;
	params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);

	// 訓練支持向量機（Train the SVM）
	CvSVM SVM;
	SVM.train(trainingDataMat, labelsMat, Mat(), Mat(), params);

	Vec3b green(0,255,0), blue (255,0,0);
	//顯示由SVM給出的決定區域 （Show the decision regions given by the SVM）
	for (int i = 0; i < image.rows; ++i)
		for (int j = 0; j < image.cols; ++j)
		{
			Mat sampleMat = (Mat_<float>(1,2) << i,j);
			float response = SVM.predict(sampleMat);

			if (response == 1)
				image.at<Vec3b>(j, i)  = green;
			else if (response == -1) 
				image.at<Vec3b>(j, i)  = blue;
		}

	//顯示訓練資料 （Show the training data）
	int thickness = -1;
	int lineType = 8;
	circle( image, Point(501,  10), 5, Scalar(  0,   0,   0), thickness, lineType);
	circle( image, Point(255,  10), 5, Scalar(255, 255, 255), thickness, lineType);
	circle( image, Point(501, 255), 5, Scalar(255, 255, 255), thickness, lineType);
	circle( image, Point( 10, 501), 5, Scalar(255, 255, 255), thickness, lineType);

	//顯示支持向量 （Show support vectors）
	thickness = 2;
	lineType  = 8;
	int c     = SVM.get_support_vector_count();

	for (int i = 0; i < c; ++i)
	{
	    const float* v = SVM.get_support_vector(i);
	    circle( image,  Point( (int) v[0], (int) v[1]),   6,  Scalar(128, 128, 128), thickness, lineType);
	}

	imwrite("result.png", image);        // 儲存圖像

	imshow("SVM Simple Example", image); // 顯示圖像
	moveWindow("SVM Simple Example", 100, 100 ); // 顯示圖像
	waitKey(0);

}
