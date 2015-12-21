#include <stdio.h>

//--------------------------------------\u3010\u7a0b\u5f0f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5f0f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f94
//		\u7a0b\u5f0f\u63cf\u8ff0\uff1a\u4f7f\u7528\u4e8c\u7dad\u7279\u5fb5\u9ede(Features2D)\u548c\u55ae\u6620\u5c04(Homography)\u5c0b\u627e\u5df2\u77e5\u7269\u9ad4
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------



//---------------------------------\u3010\u982d\u6587\u4ef6\u3001\u547d\u540d\u7a7a\u9593\u5305\u542b\u90e8\u5206\u3011----------------------------
//		\u63cf\u8ff0\uff1a\u5305\u542b\u7a0b\u5f0f\u6240\u4f7f\u7528\u7684\u982d\u6587\u4ef6\u548c\u547d\u540d\u7a7a\u9593
//------------------------------------------------------------------------------------------------
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <iostream>
using namespace cv;
using namespace std;

//-----------------------------------\u3010\u5168\u5c40\u51fd\u6578\u5ba3\u544a\u90e8\u5206\u3011--------------------------------------
//		\u63cf\u8ff0\uff1a\u5168\u5c40\u51fd\u6578\u7684\u5ba3\u544a
//-----------------------------------------------------------------------------------------------
static void ShowHelpText( );//\u8f38\u51fa\u8aaa\u660e\u6587\u5b57

//-----------------------------------\u3010main( )\u51fd\u6578\u3011--------------------------------------------
//		\u63cf\u8ff0\uff1a\u63a7\u5236\u81fa\u61c9\u7528\u7a0b\u5f0f\u7684\u5165\u53e3\u51fd\u6578\uff0c\u6211\u5011\u7684\u7a0b\u5f0f\u5f9e\u9019\u91cc\u958b\u59cb\u57f7\u884c
//-----------------------------------------------------------------------------------------------
int main(  )
{
	//\u30100\u3011\u6539\u8b8aconsole\u5b57\u9ad4\u984f\u8272
	system("color 1F"); 

	//\u30100\u3011\u986f\u793a\u6b61\u8fce\u548c\u8aaa\u660e\u6587\u5b57
	ShowHelpText( );

	//\u30101\u3011\u8f09\u5165\u539f\u59cb\u5716\u5f62
	Mat srcImage1 = imread( "1.jpg", 1 );
	Mat srcImage2 = imread( "2.jpg", 1 );
	if( !srcImage1.data || !srcImage2.data )
	{ printf("\u8b80\u53d6\u5716\u5f62\u932f\u8aa4\uff0c\u8acb\u78ba\u5b9a\u76ee\u9304\u4e0b\u662f\u5426\u6709imread\u51fd\u6578\u6307\u5b9a\u7684\u5716\u5f62\u5b58\u5728~\uff01 \n"); return false; }  

	//\u30102\u3011\u4f7f\u7528SURF\u7b97\u5b50\u6aa2\u6e2c\u95dc\u9375\u9ede
	int minHessian = 400;//SURF\u7b97\u6cd5\u4e2d\u7684hessian\u95be\u503c
	SurfFeatureDetector detector( minHessian );//\u5b9a\u7fa9\u4e00\u500bSurfFeatureDetector\uff08SURF\uff09 \u7279\u5fb5\u6aa2\u6e2c\u985e\u5225\u5c0d\u8c61  
	vector<KeyPoint> keypoints_object, keypoints_scene;//vector\u6a21\u677f\u985e\u5225\uff0c\u5b58\u653e\u4efb\u610f\u985e\u5225\u578b\u7684\u52d5\u614b\u6578\u7d44

	//\u30103\u3011\u4f7f\u7528detect\u51fd\u6578\u6aa2\u6e2c\u51faSURF\u7279\u5fb5\u95dc\u9375\u9ede\uff0c\u5132\u5b58\u5728vector\u5bbf\u4e3b\u4e2d
	detector.detect( srcImage1, keypoints_object );
	detector.detect( srcImage2, keypoints_scene );

	//\u30104\u3011\u8a08\u7b97\u63cf\u8ff0\u8868\uff08\u7279\u5fb5\u5411\u91cf\uff09
	SurfDescriptorExtractor extractor;
	Mat descriptors_object, descriptors_scene;
	extractor.compute( srcImage1, keypoints_object, descriptors_object );
	extractor.compute( srcImage2, keypoints_scene, descriptors_scene );

	//\u30105\u3011\u4f7f\u7528FLANN\u6bd4\u5c0d\u7b97\u5b50\u9032\u884c\u6bd4\u5c0d
	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	matcher.match( descriptors_object, descriptors_scene, matches );
	double max_dist = 0; double min_dist = 100;//\u6700\u5c0f\u8ddd\u96e2\u548c\u6700\u5927\u8ddd\u96e2

	//\u30106\u3011\u8a08\u7b97\u51fa\u95dc\u9375\u9ede\u4e4b\u9593\u8ddd\u96e2\u7684\u6700\u5927\u503c\u548c\u6700\u5c0f\u503c
	for( int i = 0; i < descriptors_object.rows; i++ )
	{ 
		double dist = matches[i].distance;
		if( dist < min_dist ) min_dist = dist;
		if( dist > max_dist ) max_dist = dist;
	}

	printf(">Max dist \u6700\u5927\u8ddd\u96e2 : %f \n", max_dist );
	printf(">Min dist \u6700\u5c0f\u8ddd\u96e2 : %f \n", min_dist );

	//\u30107\u3011\u5b58\u4e0b\u6bd4\u5c0d\u8ddd\u96e2\u5c0f\u4e8e3*min_dist\u7684\u9ede\u5c0d
	std::vector< DMatch > good_matches;
	for( int i = 0; i < descriptors_object.rows; i++ )
	{ 
		if( matches[i].distance < 3*min_dist )
		{ 
			good_matches.push_back( matches[i]);
		}
	}

	//\u7e6a\u88fd\u51fa\u6bd4\u5c0d\u5230\u7684\u95dc\u9375\u9ede
	Mat img_matches;
	drawMatches( srcImage1, keypoints_object, srcImage2, keypoints_scene,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

	//\u5b9a\u7fa9\u5169\u500b\u5c40\u90e8\u8b8a\u6578
	vector<Point2f> obj;
	vector<Point2f> scene;

	//\u5f9e\u6bd4\u5c0d\u6210\u529f\u7684\u6bd4\u5c0d\u5c0d\u4e2d\u53d6\u5f97\u95dc\u9375\u9ede
	for( unsigned int i = 0; i < good_matches.size(); i++ )
	{
		obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
		scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
	}

	Mat H = findHomography( obj, scene, CV_RANSAC );//\u8a08\u7b97\u900f\u8996\u8b8a\u63db 

	//\u5f9e\u5f85\u6e2c\u5716\u5f62\u4e2d\u53d6\u5f97\u89d2\u9ede
	vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( srcImage1.cols, 0 );
	obj_corners[2] = cvPoint( srcImage1.cols, srcImage1.rows ); obj_corners[3] = cvPoint( 0, srcImage1.rows );
	vector<Point2f> scene_corners(4);

	//\u9032\u884c\u900f\u8996\u8b8a\u63db
	perspectiveTransform( obj_corners, scene_corners, H);

	//\u7e6a\u88fd\u51fa\u89d2\u9ede\u4e4b\u9593\u7684\u76f4\u7dda
	line( img_matches, scene_corners[0] + Point2f( static_cast<float>(srcImage1.cols), 0), scene_corners[1] + Point2f( static_cast<float>(srcImage1.cols), 0), Scalar(255, 0, 123), 4 );
	line( img_matches, scene_corners[1] + Point2f( static_cast<float>(srcImage1.cols), 0), scene_corners[2] + Point2f( static_cast<float>(srcImage1.cols), 0), Scalar( 255, 0, 123), 4 );
	line( img_matches, scene_corners[2] + Point2f( static_cast<float>(srcImage1.cols), 0), scene_corners[3] + Point2f( static_cast<float>(srcImage1.cols), 0), Scalar( 255, 0, 123), 4 );
	line( img_matches, scene_corners[3] + Point2f( static_cast<float>(srcImage1.cols), 0), scene_corners[0] + Point2f( static_cast<float>(srcImage1.cols), 0), Scalar( 255, 0, 123), 4 );

	//\u986f\u793a\u6700\u7d42\u7d50\u679c
	imshow( "\u6548\u679c\u5716", img_matches );

	waitKey(0);
	return 0;
}



//-----------------------------------\u3010ShowHelpText( )\u51fd\u6578\u3011----------------------------------  
//      \u63cf\u8ff0\uff1a\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
	//\u8f38\u51fa\u6b61\u8fce\u8a0a\u606f\u548cOpenCV\u7248\u672c
	printf("\n\n\t\t\t\u975e\u5e38\u611f\u8b1d\u8cfc\u8cb7\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300b\u4e00\u66f8\uff01\n");
	printf("\n\n\t\t\t\u6b64\u70ba\u672c\u66f8OpenCV2\u7248\u7684\u7b2c94\u500b\u914d\u5957\u7bc4\u4f8b\u7a0b\u5f0f\n");
	printf("\n\n\t\t\t   \u73fe\u5728\u4f7f\u7528\u7684OpenCV\u7248\u672c\u70ba\uff1a" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
	//\u8f38\u51fa\u4e00\u4e9b\u8aaa\u660e\u8a0a\u606f  
	printf(  "\n\t\u6b61\u8fce\u4f86\u5230\u3010feature2D\u914d\u5408\u55ae\u6620\u5c04\u5c0b\u627e\u5df2\u77e5\u9ede\u3011\u7bc4\u4f8b\u7a0b\u5f0f\n\n");  
}  
