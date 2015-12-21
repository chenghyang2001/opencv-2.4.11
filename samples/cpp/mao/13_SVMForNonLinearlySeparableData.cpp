#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f13
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u4f86\u81eaOpenCV\u5b89\u88dd\u76ee\u9304\u4e0bSamples\u6587\u4ef6\u593e\u4e2d\u7684\u5b98\u65b9\u7bc4\u4f8b\u7a0b\u5e8f-\u652f\u6301\u5411\u91cf\u6a5fSVM\u4e4b\u8655\u7406\u7dda\u6027\u4e0d\u53ef\u5206\u8cc7\u6599
//		\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <stdio.h>

#define NTRAINING_SAMPLES   100         // \u6bcf\u985e\u5225\u8a13\u7df4\u6a23\u672c\u7684\u6578\u91cf
#define FRAC_LINEAR_SEP     0.9f        //  \u90e8\u5206(Fraction)\u7dda\u6027\u53ef\u5206\u7684\u6a23\u672c\u7d44\u6210\u90e8\u5206

using namespace cv;
using namespace std;




//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c13\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-------------------------------------------------------------------------------------------------
int main()
{
	//\u8a2d\u5b9a\u8996\u89ba\u8868\u9054\u7684\u53c3\u6578
	const int WIDTH = 512, HEIGHT = 512;
	Mat I = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);
	ShowHelpText();

	//--------------------- \u30101\u3011\u96a8\u6a5f\u5efa\u7acb\u8a13\u7df4\u8cc7\u6599 ---------------------------------------
	Mat trainData(2*NTRAINING_SAMPLES, 2, CV_32FC1);
	Mat labels   (2*NTRAINING_SAMPLES, 1, CV_32FC1);

	RNG rng(100); // \u96a8\u6a5f\u7522\u751f\u503c

	//\u5efa\u7acb\u8a13\u7df4\u8cc7\u6599\u7684\u7dda\u6027\u53ef\u5206\u7684\u7d44\u6210\u90e8\u5206
	int nLinearSamples = (int) (FRAC_LINEAR_SEP * NTRAINING_SAMPLES);

	// \u70baClass1\u7522\u751f\u96a8\u6a5f\u9ede
	Mat trainClass = trainData.rowRange(0, nLinearSamples);
	// \u9ede\u7684x\u5750\u6a19\u70ba[0,0.4)
	Mat c = trainClass.colRange(0, 1);
	rng.fill(c, RNG::UNIFORM, Scalar(1), Scalar(0.4 * WIDTH));
	// \u9ede\u7684Y\u5750\u6a19\u70ba[0,1)
	c = trainClass.colRange(1,2);
	rng.fill(c, RNG::UNIFORM, Scalar(1), Scalar(HEIGHT));

	// \u70baClass2\u7522\u751f\u96a8\u6a5f\u9ede
	trainClass = trainData.rowRange(2*NTRAINING_SAMPLES-nLinearSamples, 2*NTRAINING_SAMPLES);
	// \u9ede\u7684x\u5750\u6a19\u70ba[0.6, 1]
	c = trainClass.colRange(0 , 1); 
	rng.fill(c, RNG::UNIFORM, Scalar(0.6*WIDTH), Scalar(WIDTH));
	// \u9ede\u7684Y\u5750\u6a19\u70ba[0, 1)
	c = trainClass.colRange(1,2);
	rng.fill(c, RNG::UNIFORM, Scalar(1), Scalar(HEIGHT));

	//------------------\u5efa\u7acb\u8a13\u7df4\u8cc7\u6599\u7684\u975e\u7dda\u6027\u53ef\u5206\u7d44\u6210\u90e8\u5206 ---------------

	// \u96a8\u6a5f\u7522\u751fClass1\u548cClass2\u7684\u9ede
	trainClass = trainData.rowRange(  nLinearSamples, 2*NTRAINING_SAMPLES-nLinearSamples);
	// \u9ede\u7684x\u5750\u6a19\u70ba[0.4, 0.6)
	c = trainClass.colRange(0,1);
	rng.fill(c, RNG::UNIFORM, Scalar(0.4*WIDTH), Scalar(0.6*WIDTH)); 
	// \u9ede\u7684y\u5750\u6a19\u70ba[0, 1)
	c = trainClass.colRange(1,2);
	rng.fill(c, RNG::UNIFORM, Scalar(1), Scalar(HEIGHT));

	//-------------------------\u8a2d\u5b9a\u985e\u5225\u6a19\u7c3d ---------------------------------
	labels.rowRange(                0,   NTRAINING_SAMPLES).setTo(1);  // Class 1
	labels.rowRange(NTRAINING_SAMPLES, 2*NTRAINING_SAMPLES).setTo(2);  // Class 2

	//------------------------ 2. \u8a2d\u5b9a\u652f\u6301\u5411\u91cf\u6a5f\u7684\u53c3\u6578 --------------------
	CvSVMParams params;
	params.svm_type    = SVM::C_SVC;
	params.C           = 0.1;
	params.kernel_type = SVM::LINEAR;
	params.term_crit   = TermCriteria(CV_TERMCRIT_ITER, (int)1e7, 1e-6);

	//------------------------ 3. \u8a13\u7df4\u652f\u6301\u5411\u91cf\u6a5f ----------------------------------------------------
	cout << "Starting training process" << endl;
	CvSVM svm;
	svm.train(trainData, labels, Mat(), Mat(), params);
	cout << "Finished training process" << endl;

	//------------------------ 4. \u6a19\u51fa\u6c7a\u7b56\u5340\u57df\uff08decision regions\uff09 ----------------------------------------
	Vec3b green(0,100,0), blue (100,0,0);
	for (int i = 0; i < I.rows; ++i)
		for (int j = 0; j < I.cols; ++j)
		{
			Mat sampleMat = (Mat_<float>(1,2) << i, j);
			float response = svm.predict(sampleMat);

			if      (response == 1)    I.at<Vec3b>(j, i)  = green;
			else if (response == 2)    I.at<Vec3b>(j, i)  = blue;
		}

		//----------------------- 5. \u986f\u793a\u8a13\u7df4\u8cc7\u6599\uff08training data\uff09 --------------------------------------------
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

		//------------------------- 6. \u986f\u793a\u652f\u6301\u5411\u91cf\uff08support vectors\uff09 --------------------------------------------
		thick = 2;
		lineType  = 8;
		int x     = svm.get_support_vector_count();

		for (int i = 0; i < x; ++i)
		{
			const float* v = svm.get_support_vector(i);
			circle( I,  Point( (int) v[0], (int) v[1]), 6, Scalar(128, 128, 128), thick, lineType);
		}

		imwrite("result.png", I);                      //\u5132\u5b58\u5716\u50cf\u5230\u6587\u4ef6
		imshow("SVM for Non-Linear Training Data", I); // \u986f\u793a\u6700\u7d42\u8996\u7a97
		waitKey(0);
}
