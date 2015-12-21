#include <stdio.h>
//:read /home/peter/mao/54_PyrAndResize.cpp

//--------------------------------------¿¿¿¿¿¿-------------------------------------------
//		¿¿¿¿¿¿OpenCV3¿¿¿¿¿¿¿OpenCV2¿¿¿¿¿¿¿¿¿54
//		¿¿¿¿¿¿¿¿¿¿¿resize¿¿¿¿
//		¿¿¿¿¿¿¿¿¿¿¿ Windows 7 64bit
//		¿¿¿¿¿¿IDE¿¿¿Visual Studio 2010
//		¿¿¿¿¿¿OpenCV¿¿¿	2.4.9
//		2014¿06¿ Created by @¿¿_¿¿¿
//		2014¿11¿ Revised by @¿¿_¿¿¿
//------------------------------------------------------------------------------------------------



//---------------------------------¿¿¿¿¿¿¿¿¿¿¿¿¿¿----------------------------
//		¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
//------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;


//-----------------------------------¿¿¿¿¿¿¿¿--------------------------------------------
//	¿¿¿¿¿¿¿¿¿¿¿
//------------------------------------------------------------------------------------------------
#define WINDOW_NAME "¿¿¿¿¿¿"		//¿¿¿¿¿¿¿¿¿¿


//-----------------------------------¿¿¿¿¿¿¿¿¿¿--------------------------------------
//		¿¿¿¿¿¿¿¿¿
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage, g_tmpImage;


//-----------------------------------¿¿¿¿¿¿¿¿¿¿--------------------------------------
//		¿¿¿¿¿¿¿¿¿
//-----------------------------------------------------------------------------------------------
static void ShowHelpText();

//-----------------------------------¿main( )¿¿¿--------------------------------------------
//		¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
//-----------------------------------------------------------------------------------------------
int main( )
{
	//¿¿console¿¿¿¿
	system("color 2F");  

	//¿¿¿¿¿¿
	ShowHelpText();

	//¿¿¿¿
	g_srcImage = imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");//¿¿¿¿¿¿¿¿¿¿¿¿1.jpg¿¿¿¿¿¿¿¿¿¿¿¿2¿N¿¿¿¿¿N¿¿¿¿¿¿¿¿
	if( !g_srcImage.data ) { printf("Oh¿no¿¿¿srcImage¿¿~¿ \n"); return false; }

	// ¿¿¿¿¿¿
	namedWindow( WINDOW_NAME, CV_WINDOW_AUTOSIZE );
	imshow(WINDOW_NAME, g_srcImage);

	//¿¿¿¿
	g_tmpImage = g_srcImage;
	g_dstImage = g_tmpImage;

	int key =0;

	//¿¿¿¿¿¿¿¿
	while(1)
	{
		key=waitKey(9) ;//¿¿¿¿¿key¿¿¿

		//¿¿key¿¿¿¿¿¿¿¿¿¿¿¿
		switch(key)
		{
			//======================¿¿¿¿¿¿¿¿¿¿¿¿=======================  
		case 27://¿¿ESC
			return 0;
			break; 

		case 'q'://¿¿Q
			return 0;
			break; 

			//======================¿¿¿¿¿¿¿¿¿¿¿¿=======================  
		case 'a'://¿¿A¿¿¿¿¿pyrUp¿¿
			pyrUp( g_tmpImage, g_dstImage, Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ) );
			printf( ">¿¿¿¿¿¿A¿¿¿¿¿¿¿¿¿¿¿¿pyrUp¿¿¿¿¿¿¿¿¿¿¿¿¿×2 \n" );		
			break; 

		case 'w'://¿¿W¿¿¿¿¿resize¿¿
			resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ));
			printf( ">¿¿¿¿¿¿W¿¿¿¿¿¿¿¿¿¿¿¿resize¿¿¿¿¿¿¿¿¿¿¿¿¿×2 \n" );		
			break; 

		case '1'://¿¿1¿¿¿¿¿resize¿¿
			resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ));
			printf( ">¿¿¿¿¿¿1¿¿¿¿¿¿¿¿¿¿¿¿resize¿¿¿¿¿¿¿¿¿¿¿¿¿×2 \n" );
			break; 

		case '3': //¿¿3¿¿¿¿¿pyrUp¿¿
			pyrUp( g_tmpImage, g_dstImage, Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ));
			printf( ">¿¿¿¿¿¿3¿¿¿¿¿¿¿¿¿¿¿¿pyrUp¿¿¿¿¿¿¿¿¿¿¿¿¿×2 \n" );
			break; 
			//======================¿¿¿¿¿¿¿¿¿¿¿¿=======================  
		case 'd': //¿¿D¿¿¿¿¿pyrDown¿¿
			pyrDown( g_tmpImage, g_dstImage, Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ));
			printf( ">¿¿¿¿¿¿D¿¿¿¿¿¿¿¿¿¿¿¿pyrDown¿¿¿¿¿¿¿¿¿¿¿¿¿/2\n" );
			break; 

		case  's' : //¿¿S¿¿¿¿¿resize¿¿
			resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ));
			printf( ">¿¿¿¿¿¿S¿¿¿¿¿¿¿¿¿¿¿¿resize¿¿¿¿¿¿¿¿¿¿¿¿¿/2\n" );
			break; 

		case '2'://¿¿2¿¿¿¿¿resize¿¿
			resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ));
			printf( ">¿¿¿¿¿¿2¿¿¿¿¿¿¿¿¿¿¿¿resize¿¿¿¿¿¿¿¿¿¿¿¿¿/2\n" );
			break; 

		case '4': //¿¿4¿¿¿¿¿pyrDown¿¿
			pyrDown( g_tmpImage, g_dstImage, Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ) );
			printf( ">¿¿¿¿¿¿4¿¿¿¿¿¿¿¿¿¿¿¿pyrDown¿¿¿¿¿¿¿¿¿¿¿¿¿/2\n" );
			break; 
		}

		//¿¿¿¿¿¿¿¿¿¿¿¿¿
		imshow( WINDOW_NAME, g_dstImage );

		//¿g_dstImage¿¿g_tmpImage¿¿¿¿¿¿¿¿
		g_tmpImage = g_dstImage;
	}

	return 0;
}

//-----------------------------------¿ShowHelpText( )¿¿¿----------------------------------
//		¿¿¿¿¿¿¿¿¿¿¿
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{

	//¿¿¿¿¿¿¿OpenCV¿¿
	printf("\n\n\t\t\t¿¿¿¿¿¿¿OpenCV3¿¿¿¿¿¿¿¿¿¿\n");
	printf("\n\n\t\t\t¿¿¿¿OpenCV2¿¿¿54¿¿¿¿¿¿¿\n");
	printf("\n\n\t\t\t   ¿¿¿¿¿OpenCV¿¿¿¿" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//¿¿¿¿¿¿¿¿
	printf("\n\t¿¿¿¿OpenCV¿¿¿¿¿¿resize¿¿¿¿~\n\n");
	printf( "\n\n\t¿¿¿¿¿¿: \n\n"
		"\t\t¿¿¿¿¿ESC¿¿¿¿Q¿- ¿¿¿¿\n"
		"\t\t¿¿¿¿¿1¿¿¿¿W¿- ¿¿¿¿¿resize¿¿¿¿¿¿¿¿\n"
		"\t\t¿¿¿¿¿2¿¿¿¿S¿- ¿¿¿¿¿resize¿¿¿¿¿¿¿¿\n"
		"\t\t¿¿¿¿¿3¿¿¿¿A¿- ¿¿¿¿¿pyrUp¿¿¿¿¿¿¿¿\n"
		"\t\t¿¿¿¿¿4¿¿¿¿D¿- ¿¿¿¿¿pyrDown¿¿¿¿¿¿¿¿\n"
		);
}
