
#include <stdio.h>
#include <opencv2/opencv.hpp> //頭文件
using namespace cv; //包含cv命名空間
using namespace std; 
 
int main()
{
	//【3】記錄起始時間
//        double time0 = static_cast<double>(getTickCount());  
	double time0 = static_cast<double>(getTickCount());  

	// 【1】讀入一張圖形 
//        Mat img=imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");
	Mat img=imread("/home/peter/opencv-2.4.11/samples/cpp/mao/2.jpg");

	// 【2】在視窗中顯示載入的圖形
	imshow("【載入的圖形】",img);
	moveWindow("【載入的圖形】",100,100);

	// 【3】等待6000 ms後視窗自動關閉
	cout << " rows =  " << img.rows   << endl ; 
	cout << " cols =  " << img.cols   << endl ; 
	cout << " type =  " << img.type() << endl ; 
	//【5】計算執行時間並輸出
	time0 = ((double)getTickCount() - time0)/getTickFrequency();
	cout<<"\t此方法執行時間為： "<<time0<<"秒"<<endl;  //輸出執行時間


//        waitKey(6000);
	waitKey(3000);
}



