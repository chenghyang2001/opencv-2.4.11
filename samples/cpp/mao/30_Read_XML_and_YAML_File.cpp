#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f30
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1aXML\u548cYAML\u6a94\u6848\u7684\u8b80\u53d6
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------


//---------------------------------\u3010\u982d\u6a94\u6848\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011-------------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6a94\u6848\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------       
#include "opencv2/opencv.hpp"  
#include <time.h>  
using namespace cv;  
using namespace std;  


//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//		 \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c30\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n\n");
}




int main( )  
{  
	//\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 6F"); 

	ShowHelpText();

	//\u521d\u59cb\u5316
	FileStorage fs2("test.yaml", FileStorage::READ);  

	// \u7b2c\u4e00\u7a2e\u65b9\u6cd5\uff0c\u5c0dFileNode\u64cd\u4f5c
	int frameCount = (int)fs2["frameCount"];  

	std::string date;  
	// \u7b2c\u4e8c\u7a2e\u65b9\u6cd5\uff0c\u4f7f\u7528FileNode\u904b\u7b97\u8868> > 
	fs2["calibrationDate"] >> date;  

	Mat cameraMatrix2, distCoeffs2;  
	fs2["cameraMatrix"] >> cameraMatrix2;  
	fs2["distCoeffs"] >> distCoeffs2;  

	cout << "frameCount: " << frameCount << endl  
		<< "calibration date: " << date << endl  
		<< "camera matrix: " << cameraMatrix2 << endl  
		<< "distortion coeffs: " << distCoeffs2 << endl;  

	FileNode features = fs2["features"];  
	FileNodeIterator it = features.begin(), it_end = features.end();  
	int idx = 0;  
	std::vector<uchar> lbpval;  

	//\u4f7f\u7528FileNodeIterator\u700f\u89bd\u5e8f\u5217
	for( ; it != it_end; ++it, idx++ )  
	{  
		cout << "feature #" << idx << ": ";  
		cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";  
		// \u6211\u5011\u4e5f\u53ef\u4ee5\u4f7f\u7528\u4f7f\u7528filenode > > std::vector\u64cd\u4f5c\u8868\u5f88\u5bb9\u6613\u7684\u8b80\u6578\u503c\u9663\u5217
		(*it)["lbp"] >> lbpval;  
		for( int i = 0; i < (int)lbpval.size(); i++ )  
			cout << " " << (int)lbpval[i];  
		cout << ")" << endl;  
	}  
	fs2.release();  

	//\u7a0b\u5f0f\u7d50\u675f\uff0c\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u6587\u5b57
	printf("\n\u6a94\u6848\u8b80\u53d6\u5b8c\u7562\uff0c\u8acb\u8f38\u5165\u4efb\u610f\u9375\u7d50\u675f\u7a0b\u5f0f~");
	getchar();

	return 0;  
}  
