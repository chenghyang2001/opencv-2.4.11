
#include <stdio.h>
#include <stdio.h>

//---------------------------------【頭文件、命名空間包含部分】----------------------------
//          描述：包含程序所使用的頭文件和命名空間
//------------------------------------------------------------------------------------------------
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

//OpenCV3需加入頭文件：
#include <opencv2/imgproc/imgproc.hpp>



//-----------------------------------【巨集定義部分】-------------------------------------------- 
//		描述：定義一些輔助巨集 
//------------------------------------------------------------------------------------------------ 
#define WINDOW_NAME1 "【繪製圖1】"        //為視窗標題定義的巨集 
#define WINDOW_NAME2 "【繪製圖2】"        //為視窗標題定義的巨集 
#define WINDOW_WIDTH 600//定義視窗大小的巨集



//--------------------------------【全局函數宣告部分】-------------------------------------
//		描述：全局函數宣告
//-----------------------------------------------------------------------------------------------
void DrawEllipse( Mat img, double angle );//繪製橢圓
void DrawFilledCircle( Mat img, Point center );//繪製圓
void DrawPolygon( Mat img );//繪製多邊形
void DrawLine( Mat img, Point start, Point end );//繪製線段



//-----------------------------------【ShowHelpText( )函數】----------------------------------
//          描述：輸出一些說明訊息
//----------------------------------------------------------------------------------------------
void ShowHelpText()
{
	system("color 5F");
	//輸出歡迎訊息和OpenCV版本
	printf("\n\n\t\t\t非常感謝購買《OpenCV3程式設計入門》一書！\n");
	printf("\n\n\t\t\t此為本書OpenCV3版的第20個配套範例程序\n");
	printf("\n\n\t\t\t   現在使用的OpenCV版本為：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");
}




//---------------------------------------【main( )函數】--------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始執行
//-----------------------------------------------------------------------------------------------
int main( void )
{

	// 建立空白的Mat圖像
	Mat atomImage = Mat::zeros( WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3 );
	Mat rookImage = Mat::zeros( WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3 );

	ShowHelpText();
	// ---------------------<1>繪製化學中的原子範例圖------------------------

	//【1.1】先繪製出橢圓
	DrawEllipse( atomImage, 90 );
	DrawEllipse( atomImage, 0 );
	DrawEllipse( atomImage, 45 );
	DrawEllipse( atomImage, -45 );

	//【1.2】再繪製圓心
	DrawFilledCircle( atomImage, Point( WINDOW_WIDTH/2, WINDOW_WIDTH/2) );

	// ----------------------------<2>繪製組合圖-----------------------------
	//【2.1】先繪製出橢圓
	DrawPolygon( rookImage );

	// 【2.2】繪製矩形
	rectangle( rookImage,
		Point( 0, 7*WINDOW_WIDTH/8 ),
		Point( WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar( 0, 255, 255 ),
		-1,
		8 );

	// 【2.3】繪製一些線段
	DrawLine( rookImage, Point( 0, 15*WINDOW_WIDTH/16 ), Point( WINDOW_WIDTH, 15*WINDOW_WIDTH/16 ) );
	DrawLine( rookImage, Point( WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8 ), Point( WINDOW_WIDTH/4, WINDOW_WIDTH ) );
	DrawLine( rookImage, Point( WINDOW_WIDTH/2, 7*WINDOW_WIDTH/8 ), Point( WINDOW_WIDTH/2, WINDOW_WIDTH ) );
	DrawLine( rookImage, Point( 3*WINDOW_WIDTH/4, 7*WINDOW_WIDTH/8 ), Point( 3*WINDOW_WIDTH/4, WINDOW_WIDTH ) );

	// ---------------------------<3>顯示繪製出的圖像------------------------
	imshow( WINDOW_NAME1, atomImage );
	moveWindow( WINDOW_NAME1, 0, 200 );

	imshow( WINDOW_NAME2, rookImage );
	moveWindow( WINDOW_NAME2, WINDOW_WIDTH+50, 200 );

	waitKey( 0 );
	return(0);
}



//-------------------------------【DrawEllipse( )函數】--------------------------------
//		描述：自定義的繪製函數，實現了繪製不同角度、相同尺寸的橢圓
//-----------------------------------------------------------------------------------------
void DrawEllipse( Mat img, double angle )
{
	int thickness = 2;
	int lineType = 8;

	ellipse( img,
		Point( WINDOW_WIDTH/2, WINDOW_WIDTH/2 ),
		Size( WINDOW_WIDTH/4, WINDOW_WIDTH/16 ),
		angle,
		0,
		360,
		Scalar( 255, 129, 0 ),
		thickness,
		lineType );
}


//-----------------------------------【DrawFilledCircle( )函數】---------------------------
//		描述：自定義的繪製函數，實現了實心圓的繪製
//-----------------------------------------------------------------------------------------
void DrawFilledCircle( Mat img, Point center )
{
	int thickness = -1;
	int lineType = 8;

	circle( img,
		center,
		WINDOW_WIDTH/32,
		Scalar( 0, 0, 255 ),
		thickness,
		lineType );
}


//-----------------------------------【DrawPolygon( )函數】--------------------------
//		描述：自定義的繪製函數，實現了凹多邊形的繪製
//--------------------------------------------------------------------------------------
void DrawPolygon( Mat img )
{
	int lineType = 8;

	//建立一些點
	Point rookPoints[1][20];
	rookPoints[0][0]  = Point(    WINDOW_WIDTH/4,   7*WINDOW_WIDTH/8 );
	rookPoints[0][1]  = Point(  3*WINDOW_WIDTH/4,   7*WINDOW_WIDTH/8 );
	rookPoints[0][2]  = Point(  3*WINDOW_WIDTH/4,  13*WINDOW_WIDTH/16 );
	rookPoints[0][3]  = Point( 11*WINDOW_WIDTH/16, 13*WINDOW_WIDTH/16 );
	rookPoints[0][4]  = Point( 19*WINDOW_WIDTH/32,  3*WINDOW_WIDTH/8 );
	rookPoints[0][5]  = Point(  3*WINDOW_WIDTH/4,   3*WINDOW_WIDTH/8 );
	rookPoints[0][6]  = Point(  3*WINDOW_WIDTH/4,     WINDOW_WIDTH/8 );
	rookPoints[0][7]  = Point( 26*WINDOW_WIDTH/40,    WINDOW_WIDTH/8 );
	rookPoints[0][8]  = Point( 26*WINDOW_WIDTH/40,    WINDOW_WIDTH/4 );
	rookPoints[0][9]  = Point( 22*WINDOW_WIDTH/40,    WINDOW_WIDTH/4 );
	rookPoints[0][10] = Point( 22*WINDOW_WIDTH/40,    WINDOW_WIDTH/8 );
	rookPoints[0][11] = Point( 18*WINDOW_WIDTH/40,    WINDOW_WIDTH/8 );
	rookPoints[0][12] = Point( 18*WINDOW_WIDTH/40,    WINDOW_WIDTH/4 );
	rookPoints[0][13] = Point( 14*WINDOW_WIDTH/40,    WINDOW_WIDTH/4 );
	rookPoints[0][14] = Point( 14*WINDOW_WIDTH/40,    WINDOW_WIDTH/8 );
	rookPoints[0][15] = Point(    WINDOW_WIDTH/4,     WINDOW_WIDTH/8 );
	rookPoints[0][16] = Point(    WINDOW_WIDTH/4,   3*WINDOW_WIDTH/8 );
	rookPoints[0][17] = Point( 13*WINDOW_WIDTH/32,  3*WINDOW_WIDTH/8 );
	rookPoints[0][18] = Point(  5*WINDOW_WIDTH/16, 13*WINDOW_WIDTH/16 );
	rookPoints[0][19] = Point(    WINDOW_WIDTH/4,  13*WINDOW_WIDTH/16 );

	const Point* ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };

	fillPoly( img,
		ppt,
		npt,
		1,
		Scalar( 255, 255, 255 ),
		lineType );
}


//-----------------------------------【DrawLine( )函數】--------------------------
//		描述：自定義的繪製函數，實現了線的繪製
//---------------------------------------------------------------------------------
void DrawLine( Mat img, Point start, Point end )
{
	int thickness = 2;
	int lineType = 8;
	line( img,
		start,
		end,
		Scalar( 0, 0, 0 ),
		thickness,
		lineType );
}
