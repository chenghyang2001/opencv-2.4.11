#include <stdio.h>
//:read /home/peter/mao/30_Read_XML_and_YAML_File.cpp
//--------------------------------------【程式說明】-------------------------------------------
//		程式說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程式30
//		程式描述：XML和YAML檔案的讀取
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年06月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------


//---------------------------------【頭檔案、命名空間包含部分】-------------------------------
//		描述：包含程式所使用的頭檔案和命名空間
//------------------------------------------------------------------------------------------------       
#include "opencv2/opencv.hpp"  
#include <time.h>  
using namespace cv;  
using namespace std;  


//-----------------------------------【ShowHelpText( )函數】----------------------------------
//		 描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第30個配套範例程式\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n\n");
}




int main( )  
{  
	//改變console字體顏色
	system("color 6F"); 

	ShowHelpText();

	//初始化
	FileStorage fs2("test.yaml", FileStorage::READ);  

	// 第一種方法，對FileNode操作
	int frameCount = (int)fs2["frameCount"];  

	std::string date;  
	// 第二種方法，使用FileNode運算表> > 
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

	//使用FileNodeIterator瀏覽序列
	for( ; it != it_end; ++it, idx++ )  
	{  
		cout << "feature #" << idx << ": ";  
		cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";  
		// 我們也可以使用使用filenode > > std::vector操作表很容易的讀數值陣列
		(*it)["lbp"] >> lbpval;  
		for( int i = 0; i < (int)lbpval.size(); i++ )  
			cout << " " << (int)lbpval[i];  
		cout << ")" << endl;  
	}  
	fs2.release();  

	//程式結束，輸出一些說明文字
	printf("\n檔案讀取完畢，請輸入任意鍵結束程式~");
	getchar();

	return 0;  
}  
