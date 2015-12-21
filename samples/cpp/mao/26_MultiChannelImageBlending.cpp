#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f26
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1a\u5206\u96e2\u984f\u8272\u901a\u9053&\u591a\u901a\u9053\u5716\u50cf\u6df7\u5408
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------

//-----------------------------------\u3010\u982d\u6587\u4ef6\u5305\u542b\u90e8\u5206\u3011---------------------------------------
//	\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f9d\u8cf4\u7684\u982d\u6587\u4ef6
//------------------------------------------------------------------------------------------------                                                                                     
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

//-----------------------------------\u3010\u547d\u540d\u7a7a\u9593\u5ba3\u544a\u90e8\u5206\u3011---------------------------------------
//	\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5e8f\u6240\u4f7f\u7528\u7684\u547d\u540d\u7a7a\u9593
//-------------------------------------------------------------------------------------------------   
using namespace cv;
using namespace std;


//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//	\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
bool  MultiChannelBlending();
void ShowHelpText();


//-----------------------------------\u3010main( )\u51fd\u6578\u3011------------------------------------------
//	\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5e8f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5e8f\u5f9e\u9019\u91cc\u958b\u59cb
//-----------------------------------------------------------------------------------------------
int main(   )
{
	system("color 9F");

	ShowHelpText( );

	if(MultiChannelBlending( ))
	{
		cout<<endl<<"\n\u57f7\u884c\u6210\u529f\uff0c\u5f97\u51fa\u4e86\u9700\u8981\u7684\u5716\u50cf~! ";
	}

	waitKey(0);
	return 0;
}



//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------
//		 \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c26\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}






//-----------------------------\u3010MultiChannelBlending( )\u51fd\u6578\u3011--------------------------------
//	\u63cf\u8ff0\uff1a\u591a\u901a\u9053\u6df7\u5408\u7684\u5be6\u73fe\u51fd\u6578
//-----------------------------------------------------------------------------------------------
bool  MultiChannelBlending()
{
	//\u30100\u3011\u5b9a\u7fa9\u76f8\u95dc\u8b8a\u6578
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	Mat  imageBlueChannel;

	//=================\u3010\u85cd\u8272\u901a\u9053\u90e8\u5206\u3011=================
	//	\u63cf\u8ff0\uff1a\u591a\u901a\u9053\u6df7\u5408-\u85cd\u8272\u5206\u91cf\u90e8\u5206
	//============================================

	// \u30101\u3011\u8b80\u5165\u5716\u5f62
	logoImage= imread("dota_logo.jpg",0);
	srcImage= imread("dota_jugg.jpg");

	if( !logoImage.data ) { printf("Oh\uff0cno\uff0c\u8b80\u53d6logoImage\u932f\u8aa4~\uff01 \n"); return false; }
	if( !srcImage.data ) { printf("Oh\uff0cno\uff0c\u8b80\u53d6srcImage\u932f\u8aa4~\uff01 \n"); return false; }

	//\u30102\u3011\u628a\u4e00\u500b3\u901a\u9053\u5716\u50cf\u8f49\u63db\u62103\u500b\u55ae\u901a\u9053\u5716\u50cf
	split(srcImage,channels);//\u5206\u96e2\u8272\u5f69\u901a\u9053

	//\u30103\u3011\u5c07\u539f\u5716\u7684\u85cd\u8272\u901a\u9053\u5f15\u7528\u8fd4\u56de\u7d66imageBlueChannel\uff0c\u6ce8\u610f\u662f\u5f15\u7528\uff0c\u76f8\u7576\u4e8e\u5169\u8005\u7b49\u50f9\uff0c\u4fee\u6539\u5176\u4e2d\u4e00\u500b\u53e6\u4e00\u500b\u8ddf\u8457\u8b8a
	imageBlueChannel= channels.at(0);
	//\u30104\u3011\u5c07\u539f\u5716\u7684\u85cd\u8272\u901a\u9053\u7684\uff08500,250\uff09\u5750\u6a19\u8655\u53f3\u4e0b\u65b9\u7684\u4e00\u584a\u5340\u57df\u548clogo\u5716\u9032\u884c\u52a0\u6b0a\u64cd\u4f5c\uff0c\u5c07\u5f97\u5230\u7684\u6df7\u5408\u7d50\u679c\u5b58\u5230imageBlueChannel\u4e2d
	addWeighted(imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,0,imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)));

	//\u30105\u3011\u5c07\u4e09\u500b\u55ae\u901a\u9053\u91cd\u65b0\u5408\u4e26\u6210\u4e00\u500b\u4e09\u901a\u9053
	merge(channels,srcImage);

	//\u30106\u3011\u986f\u793a\u6548\u679c\u5716
	namedWindow(" <1>\u6e38\u6232\u539f\u756b+logo\u85cd\u8272\u901a\u9053");
	imshow(" <1>\u6e38\u6232\u539f\u756b+logo\u85cd\u8272\u901a\u9053",srcImage);


	//=================\u3010\u7da0\u8272\u901a\u9053\u90e8\u5206\u3011=================
	//	\u63cf\u8ff0\uff1a\u591a\u901a\u9053\u6df7\u5408-\u7da0\u8272\u5206\u91cf\u90e8\u5206
	//============================================

	//\u30100\u3011\u5b9a\u7fa9\u76f8\u95dc\u8b8a\u6578
	Mat  imageGreenChannel;

	//\u30101\u3011\u91cd\u65b0\u8b80\u5165\u5716\u5f62
	logoImage= imread("dota_logo.jpg",0);
	srcImage= imread("dota_jugg.jpg");

	if( !logoImage.data ) { printf("\u8b80\u53d6logoImage\u932f\u8aa4~\uff01 \n"); return false; }
	if( !srcImage.data ) { printf("\u8b80\u53d6srcImage\u932f\u8aa4~\uff01 \n"); return false; }

	//\u30102\u3011\u5c07\u4e00\u500b\u4e09\u901a\u9053\u5716\u50cf\u8f49\u63db\u6210\u4e09\u500b\u55ae\u901a\u9053\u5716\u50cf
	split(srcImage,channels);//\u5206\u96e2\u8272\u5f69\u901a\u9053

	//\u30103\u3011\u5c07\u539f\u5716\u7684\u7da0\u8272\u901a\u9053\u7684\u5f15\u7528\u8fd4\u56de\u7d66imageBlueChannel\uff0c\u6ce8\u610f\u662f\u5f15\u7528\uff0c\u76f8\u7576\u4e8e\u5169\u8005\u7b49\u50f9\uff0c\u4fee\u6539\u5176\u4e2d\u4e00\u500b\u53e6\u4e00\u500b\u8ddf\u8457\u8b8a
	imageGreenChannel= channels.at(1);
	//\u30104\u3011\u5c07\u539f\u5716\u7684\u7da0\u8272\u901a\u9053\u7684\uff08500,250\uff09\u5750\u6a19\u8655\u53f3\u4e0b\u65b9\u7684\u4e00\u584a\u5340\u57df\u548clogo\u5716\u9032\u884c\u52a0\u6b0a\u64cd\u4f5c\uff0c\u5c07\u5f97\u5230\u7684\u6df7\u5408\u7d50\u679c\u5b58\u5230imageGreenChannel\u4e2d
	addWeighted(imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,0.,imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)));

	//\u30105\u3011\u5c07\u4e09\u500b\u7368\u7acb\u7684\u55ae\u901a\u9053\u91cd\u65b0\u5408\u4e26\u6210\u4e00\u500b\u4e09\u901a\u9053
	merge(channels,srcImage);

	//\u30106\u3011\u986f\u793a\u6548\u679c\u5716
	namedWindow("<2>\u6e38\u6232\u539f\u756b+logo\u7da0\u8272\u901a\u9053");
	imshow("<2>\u6e38\u6232\u539f\u756b+logo\u7da0\u8272\u901a\u9053",srcImage);



	//=================\u3010\u7d05\u8272\u901a\u9053\u90e8\u5206\u3011=================
	//	\u63cf\u8ff0\uff1a\u591a\u901a\u9053\u6df7\u5408-\u7d05\u8272\u5206\u91cf\u90e8\u5206
	//============================================

	//\u30100\u3011\u5b9a\u7fa9\u76f8\u95dc\u8b8a\u6578
	Mat  imageRedChannel;

	//\u30101\u3011\u91cd\u65b0\u8b80\u5165\u5716\u5f62
	logoImage= imread("dota_logo.jpg",0);
	srcImage= imread("dota_jugg.jpg");

	if( !logoImage.data ) { printf("Oh\uff0cno\uff0c\u8b80\u53d6logoImage\u932f\u8aa4~\uff01 \n"); return false; }
	if( !srcImage.data ) { printf("Oh\uff0cno\uff0c\u8b80\u53d6srcImage\u932f\u8aa4~\uff01 \n"); return false; }

	//\u30102\u3011\u5c07\u4e00\u500b\u4e09\u901a\u9053\u5716\u50cf\u8f49\u63db\u6210\u4e09\u500b\u55ae\u901a\u9053\u5716\u50cf
	split(srcImage,channels);//\u5206\u96e2\u8272\u5f69\u901a\u9053

	//\u30103\u3011\u5c07\u539f\u5716\u7684\u7d05\u8272\u901a\u9053\u5f15\u7528\u8fd4\u56de\u7d66imageBlueChannel\uff0c\u6ce8\u610f\u662f\u5f15\u7528\uff0c\u76f8\u7576\u4e8e\u5169\u8005\u7b49\u50f9\uff0c\u4fee\u6539\u5176\u4e2d\u4e00\u500b\u53e6\u4e00\u500b\u8ddf\u8457\u8b8a
	imageRedChannel= channels.at(2);
	//\u30104\u3011\u5c07\u539f\u5716\u7684\u7d05\u8272\u901a\u9053\u7684\uff08500,250\uff09\u5750\u6a19\u8655\u53f3\u4e0b\u65b9\u7684\u4e00\u584a\u5340\u57df\u548clogo\u5716\u9032\u884c\u52a0\u6b0a\u64cd\u4f5c\uff0c\u5c07\u5f97\u5230\u7684\u6df7\u5408\u7d50\u679c\u5b58\u5230imageRedChannel\u4e2d
	addWeighted(imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
		logoImage,0.5,0.,imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)));

	//\u30105\u3011\u5c07\u4e09\u500b\u7368\u7acb\u7684\u55ae\u901a\u9053\u91cd\u65b0\u5408\u4e26\u6210\u4e00\u500b\u4e09\u901a\u9053
	merge(channels,srcImage);

	//\u30106\u3011\u986f\u793a\u6548\u679c\u5716
	namedWindow("<3>\u6e38\u6232\u539f\u756b+logo\u7d05\u8272\u901a\u9053 ");
	imshow("<3>\u6e38\u6232\u539f\u756b+logo\u7d05\u8272\u901a\u9053 ",srcImage);

	return true;
}


