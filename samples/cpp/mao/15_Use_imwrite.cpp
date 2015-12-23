
#include <stdio.h>
//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//-------------------------------------------------------------------------------------------------
#include <vector>
#include <stdio.h>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;


//--------------------------------【createAlphaMat( )函數】--------------------------------
//		描述：建立帶alpha通道的Mat
//-------------------------------------------------------------------------------------------------
void createAlphaMat(Mat &mat)
{
	for(int i = 0; i < mat.rows; ++i) {
		for(int j = 0; j < mat.cols; ++j) {
			Vec4b&rgba = mat.at<Vec4b>(i, j);
			rgba[0]= UCHAR_MAX;
			rgba[1]= saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) *UCHAR_MAX);
			rgba[2]= saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) *UCHAR_MAX);
			rgba[3]= saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
		}
	}
}



//-----------------------------------【ShowHelpText( )函數】----------------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV2版的第15個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}



int main( )
{
	//建立帶alpha通道的Mat
	Mat mat(480, 640, CV_8UC4);
	createAlphaMat(mat);

	ShowHelpText();

	vector<int>compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	//顯示圖形
//        try{
		imwrite("透明Alpha值圖.png", mat, compression_params);
		imshow("產生的png圖",mat);
		moveWindow("產生的png圖",100,100);
		fprintf(stdout,"PNG圖形文件的alpha資料儲存完畢~\n可以在專案目錄下查看由imwrite函數產生的圖形\n");
		waitKey(0);
//        }
//        catch(runtime_error& ex) {
//                fprintf(stderr,"圖像轉換成PNG格式發生錯誤：%s\n", ex.what());
//                return 1;
//        }

	return 0;
}
