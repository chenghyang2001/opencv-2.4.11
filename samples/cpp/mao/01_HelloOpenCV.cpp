// file :   ~/opencv-2.4.11/samples/cpp/mao/01_HelloOpenCV.cpp

#include <stdio.h>
#include <opencv2/opencv.hpp> //頭文件
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>

using namespace cv; //包含cv命名空間
using namespace std; 
 
int main()
{

	cout<<"11111111111  " << endl;  

#if 0

    1.
	:!nautilus /home/peter/Downloads

    2.
	/* 
	:!nautilus /home/peter/Downloads
	 */

    3.
	<url:vimscript:!nautilus /home/peter/Downloads> 

    4. 
  
        :!eog /home/peter/Downloads/eye_images_05.jpg  &

        <url:vimscript:!eog /home/peter/Downloads/eye_images_05.jpg  &>

	    
#endif
     cv::Mat src  ; 

    char index = '1' ; 

    cout << "Enter a number ( 1 ~ 5 ) : "    ; 
    cin >> index ; 

   
    switch ( index  )  {

	case '1' :
	    src = cv::imread("/home/peter/Downloads/eye_images_05.jpg");  // <url:vimscript:!eog /home/peter/Downloads/eye_images_05.jpg  &>
	    break ; 
	case '2' :
	    src = cv::imread("/home/peter/Downloads/eye_images_04.jpg");  // <url:vimscript:!eog /home/peter/Downloads/eye_images_04.jpg  &>
	    break ;
	case '3' :
	    src = cv::imread("/home/peter/Downloads/eye_images_03.jpg");  // <url:vimscript:!eog /home/peter/Downloads/eye_images_03.jpg  &>
	    break ;
	case '4' :
	    src = cv::imread("/home/peter/Downloads/eye_images_04.jpg");  // <url:vimscript:!eog /home/peter/Downloads/eye_images_04.jpg  &>
	    break ;
	case '5' :
	    src = cv::imread("/home/peter/Downloads/eye_images_05.jpg");  // <url:vimscript:!eog /home/peter/Downloads/eye_images_05.jpg  &>
	    break ;
	default  :
	    src = cv::imread("/home/peter/Downloads/eye_images_05.jpg");  // <url:vimscript:!eog /home/peter/Downloads/eye_images_05.jpg  &>
	    break ;

    }



     if (src.empty())
         return -1;


     cv::Mat gray;
     cv::cvtColor(~src, gray, CV_BGR2GRAY);

     // Convert to binary image by thresholding it
//
//     cv::threshold(gray, gray, 150, 255, cv::THRESH_BINARY);     // contours size = 121
     cv::threshold(gray, gray, 220, 255, cv::THRESH_BINARY);       // contours size = 83
//     cv::threshold(gray, gray, 230, 255, cv::THRESH_BINARY);       // contours size = 212
//     cv::threshold(gray, gray, 240, 255, cv::THRESH_BINARY);       // contours size = 161

     //¦Ç¶¥²´·ú 220->150 ¬õ¦â²´·ú¥Î220 

     // peter. show gray image    20170511 
     cv::imshow("BinaryImage", gray);
     moveWindow("BinaryImage",500,0);
     

     std::vector<std::vector<cv::Point> > contours;
     cv::findContours(gray.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

     // Fill holes in each contour
     cv::drawContours(gray, contours, -1, CV_RGB(255,255,255), -1);

      cout<<" contours size  :   " <<   contours.size() <<  endl;  

     for (int i = 0; i < contours.size(); i++)
     {
         double area = cv::contourArea(contours[i]);
         cv::Rect rect = cv::boundingRect(contours[i]);
         int radius = rect.width/2;


         if ( area >= 30 ) {

	     cout  <<  "    i.=" << i << "   area = " << area ;  
	     cout  <<  "    1.=" << std::abs(1 - ((double)rect.width / (double)rect.height)) ;  
	     cout  <<  "    2.=" << std::abs(1 - (area / (CV_PI * std::pow(radius, 2))))     <<   endl;  
	 }

         // If contour is big enough
         // Then it is the pupil
         if (area >= 30 && 
             std::abs(1 - ((double)rect.width / (double)rect.height)) <= 0.2 &&
             std::abs(1 - (area / (CV_PI * std::pow(radius, 2))))     <= 0.4)    
         {
              cv::circle(src, cv::Point(rect.x + radius, rect.y + radius), radius, CV_RGB(255,0,0), 2);

	      cout<<"x :   " <<   rect.x + radius <<  endl;  
	      cout<<"y :   " <<   rect.y + radius <<  endl;  

              // (rect.x/2,rect.y/2)¬°Àû¤Õ¤¤¤ßÂI®y¼Ð radius¬°­nµe¶êªº¥b®| ¦p¥u­n®y¼Ð¦¹­È¥i¥H¤£¥Î
         }
     }

     cv::imshow("image", src);
     cv::waitKey(0);


#if 0
	//【3】記錄起始時間
//        double time0 = static_cast<double>(getTickCount());  
	double time0 = static_cast<double>(getTickCount());  

	// 【1】讀入一張圖形 
	Mat img=imread("/home/peter/eye_01.jpg");

//        Mat img=imread("/home/peter/opencv-2.4.11/samples/cpp/mao/rain.jpg");
//        Mat img=imread("/home/peter/opencv-2.4.11/samples/cpp/mao/1.jpg");
//        Mat img=imread("/home/peter/opencv-2.4.11/samples/cpp/mao/2.jpg");

	// 【2】在視窗中顯示載入的圖形
	imshow("【載入的圖形】",img);
	moveWindow("【載入的圖形】",100,100);

	// 【3】等待6000 ms後視窗自動關閉
	cout << " rows =  " << img.rows   << endl ; 
	cout << " cols =  " << img.cols   << endl ; 
//        cout << " type =  " << img.type() << endl ; 
	//【5】計算執行時間並輸出
	time0 = ((double)getTickCount() - time0)/getTickFrequency();
	cout<<"\t此方法執行時間為： "<<time0<<"秒"<<endl;  //輸出執行時間


//        waitKey(6000);
//        waitKey(3000);
	waitKey(0);

#endif


}



