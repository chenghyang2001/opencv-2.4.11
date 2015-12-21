#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f12
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u4f86\u81eaOpenCV\u5b89\u88dd\u76ee\u9304\u4e0bSamples\u6587\u4ef6\u593e\u4e2d\u7684\u5b98\u65b9\u7bc4\u4f8b\u7a0b\u5e8f-\u652f\u6301\u5411\u91cf\u6a5fSVM\u958b\u6a5f
//		\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------


//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//-------------------------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

#include <stdio.h>
using namespace cv;




//--------------------------------\u3010help( )\u51fd\u6578\u3011----------------------------------------------
//		\u63cf\u8ff0\uff1a\u8f38\u51fa\u8aaa\u660e\u8a0a\u606f
//-------------------------------------------------------------------------------------------------

//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c12\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-------------------------------------------------------------------------------------------------
int main()
{
	// \u8996\u89ba\u8868\u9054\u8cc7\u6599\u7684\u8a2d\u5b9a\uff08Data for visual representation\uff09
	int width = 512, height = 512;
	Mat image = Mat::zeros(height, width, CV_8UC3);

	//\u5efa\u7acb\u8a13\u7df4\u8cc7\u6599\uff08 Set up training data\uff09
	float labels[4] = {1.0, -1.0, -1.0, -1.0};
	Mat labelsMat(3, 1, CV_32FC1, labels);

	float trainingData[4][2] = { {501, 10}, {255, 10}, {501, 255}, {10, 501} };
	Mat trainingDataMat(3, 2, CV_32FC1, trainingData);

	ShowHelpText();

	//\u8a2d\u5b9a\u652f\u6301\u5411\u91cf\u6a5f\u7684\u53c3\u6578\uff08Set up SVM's parameters\uff09
	CvSVMParams params;
	params.svm_type    = CvSVM::C_SVC;
	params.kernel_type = CvSVM::LINEAR;
	params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);

	// \u8a13\u7df4\u652f\u6301\u5411\u91cf\u6a5f\uff08Train the SVM\uff09
	CvSVM SVM;
	SVM.train(trainingDataMat, labelsMat, Mat(), Mat(), params);

	Vec3b green(0,255,0), blue (255,0,0);
	//\u986f\u793a\u7531SVM\u7d66\u51fa\u7684\u6c7a\u5b9a\u5340\u57df \uff08Show the decision regions given by the SVM\uff09
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

		//\u986f\u793a\u8a13\u7df4\u8cc7\u6599 \uff08Show the training data\uff09
		int thickness = -1;
		int lineType = 8;
		circle( image, Point(501,  10), 5, Scalar(  0,   0,   0), thickness, lineType);
		circle( image, Point(255,  10), 5, Scalar(255, 255, 255), thickness, lineType);
		circle( image, Point(501, 255), 5, Scalar(255, 255, 255), thickness, lineType);
		circle( image, Point( 10, 501), 5, Scalar(255, 255, 255), thickness, lineType);

		//\u986f\u793a\u652f\u6301\u5411\u91cf \uff08Show support vectors\uff09
		thickness = 2;
		lineType  = 8;
		int c     = SVM.get_support_vector_count();

		for (int i = 0; i < c; ++i)
		{
			const float* v = SVM.get_support_vector(i);
			circle( image,  Point( (int) v[0], (int) v[1]),   6,  Scalar(128, 128, 128), thickness, lineType);
		}

		imwrite("result.png", image);        // \u5132\u5b58\u5716\u50cf

		imshow("SVM Simple Example", image); // \u986f\u793a\u5716\u50cf
		waitKey(0);

}
