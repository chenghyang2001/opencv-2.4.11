#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f15
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u5229\u7528imwrite\u51fd\u6578\u7522\u751f\u5e36\u900f\u660e\u901a\u9053\u7684png\u5716\u50cf
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7403\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------


//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//-------------------------------------------------------------------------------------------------
#include <vector>
#include <stdio.h>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;


//--------------------------------\u3010createAlphaMat( )\u51fd\u6578\u3011--------------------------------
//		\u63cf\u8ff0\uff1a\u5efa\u7acb\u5e36alpha\u901a\u9053\u7684Mat
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



//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//          \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c15\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}



int main( )
{
	//\u5efa\u7acb\u5e36alpha\u901a\u9053\u7684Mat
	Mat mat(480, 640, CV_8UC4);
	createAlphaMat(mat);

	ShowHelpText();

	vector<int>compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	//\u986f\u793a\u5716\u5f62
//        try{
//                imwrite("\u900f\u660eAlpha\u503c\u5716.png", mat, compression_params);
//                imshow("\u7522\u751f\u7684png\u5716",mat);
//                fprintf(stdout,"PNG\u5716\u5f62\u6587\u4ef6\u7684alpha\u8cc7\u6599\u5132\u5b58\u5b8c\u7562~\n\u53ef\u4ee5\u5728\u5c08\u6848\u76ee\u9304\u4e0b\u67e5\u770b\u7531imwrite\u51fd\u6578\u7522\u751f\u7684\u5716\u5f62\n");
//                waitKey(0);
//        }
//        catch(runtime_error& ex) {
//                fprintf(stderr,"\u5716\u50cf\u8f49\u63db\u6210PNG\u683c\u5f0f\u767c\u751f\u932f\u8aa4\uff1a%s\n", ex.what());
//                return 1;
//        }

	return 0;
}
