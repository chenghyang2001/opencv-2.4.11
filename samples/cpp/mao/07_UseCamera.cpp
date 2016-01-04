
#include <stdio.h>
//---------------------------------【頭文件、命名空間包含部分】----------------------------
//		描述：包含程序所使用的頭文件和命名空間
//-------------------------------------------------------------------------------------------------
#include <opencv2/opencv.hpp>  
using namespace cv;  
using namespace std;  

//-----------------------------------【main( )函數】--------------------------------------------
//		描述：控制臺應用程序的入口函數，我們的程序從這里開始
//-------------------------------------------------------------------------------------------------
int main( )  
{  
	//【1】從攝影機讀入視訊
	VideoCapture capture(0);
//        VideoCapture capture("/home/peter/opencv-2.4.11/samples/cpp/mao/1.avi");


	//【2】循環顯示每一幅
	while(1)  
	{  
		Mat frame;  //定義一個Mat變數，用于存儲每一幅的圖像
		capture>>frame;  //讀取現在幅

		resize(frame, frame,Size(1024,768),0,0,INTER_CUBIC)  ;

		imshow("讀取視訊",frame);  //顯示現在幅
		moveWindow("讀取視訊",100,100);  //顯示現在幅
//                resizeWindow("讀取視訊",1024, 768 );  //顯示現在幅
		waitKey(30);  //延時30ms
	}  
	return 0;     
}  



#if 0
===============================================================


//        bool result ;
//        result = capture.set( CV_CAP_PROP_FRAME_WIDTH , 640/2        ) ;
//        cout << "1. result  = "   <<  result  <<  endl ;
//        result = capture.set( CV_CAP_PROP_FRAME_HEIGHT , 480/2        ) ;
//        cout << "2. result  = "   <<  result  <<  endl ;

//        cout << " CV_CAP_PROP_FRAME_WIDTH        = "   <<  capture.get( CV_CAP_PROP_FRAME_WIDTH         ) <<  endl ;
//        cout << " CV_CAP_PROP_FRAME_HEIGHT       = "   <<  capture.get( CV_CAP_PROP_FRAME_HEIGHT        ) <<  endl ;


	cout << " CV_CAP_PROP_POS_MSEC           = "   <<  capture.get( CV_CAP_PROP_POS_MSEC            ) <<  endl ;
	cout << " CV_CAP_PROP_POS_FRAMES         = "   <<  capture.get( CV_CAP_PROP_POS_FRAMES          ) <<  endl ;
	cout << " CV_CAP_PROP_POS_AVI_RATIO      = "   <<  capture.get( CV_CAP_PROP_POS_AVI_RATIO       ) <<  endl ;
	cout << " CV_CAP_PROP_FRAME_WIDTH        = "   <<  capture.get( CV_CAP_PROP_FRAME_WIDTH         ) <<  endl ;
	cout << " CV_CAP_PROP_FRAME_HEIGHT       = "   <<  capture.get( CV_CAP_PROP_FRAME_HEIGHT        ) <<  endl ;
	cout << " CV_CAP_PROP_FPS                = "   <<  capture.get( CV_CAP_PROP_FPS                 ) <<  endl ;
	cout << " CV_CAP_PROP_FOURCC             = "   <<  capture.get( CV_CAP_PROP_FOURCC              ) <<  endl ;
	cout << " CV_CAP_PROP_FRAME_COUNT        = "   <<  capture.get( CV_CAP_PROP_FRAME_COUNT         ) <<  endl ;
	cout << " CV_CAP_PROP_FORMAT             = "   <<  capture.get( CV_CAP_PROP_FORMAT              ) <<  endl ;
	cout << " CV_CAP_PROP_MODE               = "   <<  capture.get( CV_CAP_PROP_MODE                ) <<  endl ;
	cout << " CV_CAP_PROP_BRIGHTNESS         = "   <<  capture.get( CV_CAP_PROP_BRIGHTNESS         ) <<  endl ;
	cout << " CV_CAP_PROP_CONTRAST           = "   <<  capture.get( CV_CAP_PROP_CONTRAST           ) <<  endl ;
	cout << " CV_CAP_PROP_SATURATION         = "   <<  capture.get( CV_CAP_PROP_SATURATION         ) <<  endl ;
	cout << " CV_CAP_PROP_HUE                = "   <<  capture.get( CV_CAP_PROP_HUE                ) <<  endl ;
	cout << " CV_CAP_PROP_GAIN               = "   <<  capture.get( CV_CAP_PROP_GAIN               ) <<  endl ;
	cout << " CV_CAP_PROP_EXPOSURE           = "   <<  capture.get( CV_CAP_PROP_EXPOSURE           ) <<  endl ;
	cout << " CV_CAP_PROP_CONVERT_RGB        = "   <<  capture.get( CV_CAP_PROP_CONVERT_RGB        ) <<  endl ;
	cout << " CV_CAP_PROP_WHITE_BALANCE_U    = "   <<  capture.get( CV_CAP_PROP_WHITE_BALANCE_U    ) <<  endl ;
	cout << " CV_CAP_PROP_RECTIFICATION      = "   <<  capture.get( CV_CAP_PROP_RECTIFICATION      ) <<  endl ;
	cout << " CV_CAP_PROP_MONOCROME          = "   <<  capture.get( CV_CAP_PROP_MONOCROME          ) <<  endl ;
	cout << " CV_CAP_PROP_SHARPNESS          = "   <<  capture.get( CV_CAP_PROP_SHARPNESS          ) <<  endl ;
	cout << " CV_CAP_PROP_AUTO_EXPOSURE      = "   <<  capture.get( CV_CAP_PROP_AUTO_EXPOSURE      ) <<  endl ;
	cout << " CV_CAP_PROP_GAMMA              = "   <<  capture.get( CV_CAP_PROP_GAMMA              ) <<  endl ;
	cout << " CV_CAP_PROP_TEMPERATURE        = "   <<  capture.get( CV_CAP_PROP_TEMPERATURE        ) <<  endl ;
	cout << " CV_CAP_PROP_TRIGGER            = "   <<  capture.get( CV_CAP_PROP_TRIGGER            ) <<  endl ;
	cout << " CV_CAP_PROP_TRIGGER_DELAY      = "   <<  capture.get( CV_CAP_PROP_TRIGGER_DELAY      ) <<  endl ;
	cout << " CV_CAP_PROP_WHITE_BALANCE_V    = "   <<  capture.get( CV_CAP_PROP_WHITE_BALANCE_V    ) <<  endl ;
	cout << " CV_CAP_PROP_ZOOM               = "   <<  capture.get( CV_CAP_PROP_ZOOM               ) <<  endl ;
	cout << " CV_CAP_PROP_FOCUS              = "   <<  capture.get( CV_CAP_PROP_FOCUS              ) <<  endl ;
	cout << " CV_CAP_PROP_GUID               = "   <<  capture.get( CV_CAP_PROP_GUID               ) <<  endl ;
	cout << " CV_CAP_PROP_ISO_SPEED          = "   <<  capture.get( CV_CAP_PROP_ISO_SPEED          ) <<  endl ;
	cout << " CV_CAP_PROP_MAX_DC1394         = "   <<  capture.get( CV_CAP_PROP_MAX_DC1394         ) <<  endl ;
	cout << " CV_CAP_PROP_BACKLIGHT          = "   <<  capture.get( CV_CAP_PROP_BACKLIGHT          ) <<  endl ;
	cout << " CV_CAP_PROP_PAN                = "   <<  capture.get( CV_CAP_PROP_PAN                ) <<  endl ;
	cout << " CV_CAP_PROP_TILT               = "   <<  capture.get( CV_CAP_PROP_TILT               ) <<  endl ;
	cout << " CV_CAP_PROP_ROLL               = "   <<  capture.get( CV_CAP_PROP_ROLL               ) <<  endl ;
	cout << " CV_CAP_PROP_IRIS               = "   <<  capture.get( CV_CAP_PROP_IRIS               ) <<  endl ;
	cout << " CV_CAP_PROP_SETTINGS           = "   <<  capture.get( CV_CAP_PROP_SETTINGS           ) <<  endl ;
	cout << " CV_CAP_PROP_BUFFERSIZE         = "   <<  capture.get( CV_CAP_PROP_BUFFERSIZE         ) <<  endl ;

#endif

