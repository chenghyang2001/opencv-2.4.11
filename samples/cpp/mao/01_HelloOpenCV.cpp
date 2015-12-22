//:read /home/peter/mao/01_HelloOpenCV.cpp
//
//--------------------------------------【程序說明】-------------------------------------------
//		程序說明：《OpenCV3程式設計入門》OpenCV2版書本配套範例程序01
//		程序描述：OpenCV開發環境的設定，載入一張圖形並顯示
//		開發測試所用操作系統： Windows 7 64bit
//		開發測試所用IDE版本：Visual Studio 2010
//		開發測試所用OpenCV版本：	2.4.9
//		2014年03月 Created by @淺墨_毛星云
//		2014年11月 Revised by @淺墨_毛星云
//------------------------------------------------------------------------------------------------

#include <opencv2/opencv.hpp> //頭文件
using namespace cv; //包含cv命名空間
using namespace std; 
 
int main()
{
	//【3】記錄起始時間
	double time0 = static_cast<double>(getTickCount());  

	// 【1】讀入一張圖形 
	Mat img=imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");
	// 【2】在視窗中顯示載入的圖形
	imshow("【載入的圖形】",img);
	moveWindow("【載入的圖形】",100,100);
	// 【3】等待6000 ms後視窗自動關閉
	//
	cout << " rows =  " << img.rows   << endl ; 
	cout << " cols =  " << img.cols   << endl ; 
	cout << " type =  " << img.type() << endl ; 
	//【5】計算執行時間並輸出
	time0 = ((double)getTickCount() - time0)/getTickFrequency();
	cout<<"\t此方法執行時間為： "<<time0<<"秒"<<endl;  //輸出執行時間


	waitKey(6000);
}



