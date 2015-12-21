#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f19
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1a\u57fa\u790e\u5716\u50cf\u5bb9\u5668Mat\u985e\u5225\u7684\u4f7f\u7528
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7412\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------


//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011---------------------------
//          \u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//-----------------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace std;
using namespace cv;



//-----------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u8f38\u51fa\u8aaa\u660e\u8a0a\u606f
//-------------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c19\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
	printf("\n\n\n\t\u6b61\u8fce\u4f86\u5230\u3010\u57fa\u672c\u5716\u50cf\u5bb9\u5668-Mat\u985e\u5225\u3011\u7bc4\u4f8b\u7a0b\u5f0f~\n\n"); 	
	printf("\n\n\t\u7a0b\u5f0f\u8aaa\u660e\uff1a\n\n\t\u6b64\u7bc4\u4f8b\u7a0b\u5f0f\u7528\u65bc\u793a\u7bc4Mat\u985e\u5225\u7684\u683c\u5f0f\u5316\u8f38\u51fa\u529f\u80fd\uff0c\u8f38\u51fa\u98a8\u683c\u53ef\u70ba\uff1a");
	printf("\n\n\n\t\u30101\u3011OpenCV\u9810\u8a2d\u98a8\u683c");
	printf("\n\n\t\u30102\u3011Python\u98a8\u683c");
	printf("\n\n\t\u30103\u3011\u9017\u865f\u5206\u9694\u98a8\u683c");
	printf("\n\n\t\u30104\u3011Numpy\u98a8\u683c");
	printf("\n\n\t\u30105\u3011C\u8a9e\u8a00\u98a8\u683c\n\n");
	printf("\n  --------------------------------------------------------------------------\n");



}


//--------------------------------------\u3010main( )\u51fd\u6578\u3011-----------------------------------------
//          \u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main(int,char**)
{
	//\u6539\u8b8a\u63a7\u5236\u81fa\u7684\u524d\u666f\u8272\u548c\u80cc\u666f\u8272
	system("color 8F"); 

	//\u986f\u793a\u8aaa\u660e\u6587\u5b57
	ShowHelpText();

	Mat I = Mat::eye(4, 4, CV_64F);
	I.at<double>(1,1) = CV_PI;
	cout << "\nI = " << I << ";\n" << endl;

	Mat r = Mat(10, 3, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));

	cout << "r (OpenCV\u9810\u8a2d\u98a8\u683c) = " << r << ";" << endl << endl;
	cout << "r (Python\u98a8\u683c) = " << format(r,"python") << ";" << endl << endl;
	cout << "r (Numpy\u98a8\u683c) = " << format(r,"numpy") << ";" << endl << endl;
	cout << "r (\u9017\u865f\u5206\u9694\u98a8\u683c) = " << format(r,"csv") << ";" << endl<< endl;
	cout << "r (C\u8a9e\u8a00\u98a8\u683c) = " << format(r,"C") << ";" << endl << endl;

	Point2f p(6, 2);
	cout << "\u30102\u7dad\u9ede\u3011p = " << p << ";\n" << endl;

	Point3f p3f(8, 2, 0);
	cout << "\u30103\u7dad\u9ede\u3011p3f = " << p3f << ";\n" << endl;

	vector<float> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);

	cout << "\u3010\u57fa\u4e8eMat\u7684vector\u3011shortvec = " << Mat(v) << ";\n"<<endl;

	vector<Point2f> points(20);
	for (size_t i = 0; i < points.size(); ++i)
		points[i] = Point2f((float)(i * 5), (float)(i % 7));

	cout << "\u3010\u4e8c\u7dad\u9ede\u5411\u91cf\u3011points = " << points<<";";

	getchar();//\u6309\u4efb\u610f\u9375\u9000\u51fa

	return 0;


}
