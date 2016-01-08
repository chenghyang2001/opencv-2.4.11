
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui_c.h"
#include <stdio.h>

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <sys/time.h>

#define PRINT_COUNT 10

#define w 500
int levels = 3;
CvSeq* contours = 0;

void showCameraProperty(CvCapture *camera) {

    printf(" showCameraProperty called.\n" );

    CvSize video_size;
    video_size.height = (int) cvGetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT);
    video_size.width  = (int) cvGetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH);

    int frame_per_second  = (int) cvGetCaptureProperty(camera, CV_CAP_PROP_FPS);

    printf("1. height = %d width = %d fps = %d .\n" , video_size.height , video_size.width, frame_per_second );

     cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT, video_size.height/2 );
     cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH, video_size.width/2 );

    video_size.height = (int) cvGetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT);
    video_size.width  = (int) cvGetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH);

    printf("2. height = %d width = %d.\n" , video_size.height , video_size.width);

    // ok. can show camera	
//     cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH, 640 );
//     cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT, 480 );

    // not ok. will not show camera	
     cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH, 1280 );
     cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT, 720 );

//     cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH, 1024 );
//     cvSetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT, 768 );

    video_size.height = (int) cvGetCaptureProperty(camera, CV_CAP_PROP_FRAME_HEIGHT);
    video_size.width  = (int) cvGetCaptureProperty(camera, CV_CAP_PROP_FRAME_WIDTH);

    printf("3. height = %d width = %d.\n" , video_size.height , video_size.width);



}

int main(int argc, char* argv[])
{
    printf("1. peter \n");
    printf("2. peter \n");
    printf("3. peter \n");
    printf("4. peter \n");

    CvCapture *input_video = cvCaptureFromCAM(-1);

    if (input_video == NULL) {
	fprintf(stderr, "Error: Can't open video\n");
	return -1;
    }

    showCameraProperty(input_video ) ;


    int    key_pressed = 0;
    int count = 0 ;
    IplImage *frame    = NULL;

    while(key_pressed != 27) {

	count = count + 1; 
/*        double t = (double)getTickCount();*/


	frame = cvQueryFrame(input_video);
	if (frame == NULL) {
	    fprintf(stderr, "Error: null frame received\n");
	    return -1;
	}

/*        double t_per_line  = (double)getTickCount();*/

	cvShowImage("Grey",frame);  //顯示現在幅

#if 0
	cvPyrDown(frame, half_frame, CV_GAUSSIAN_5x5); // Reduce the image by 2  
//        cvCvtColor(temp_frame, grey, CV_BGR2GRAY); // convert to grayscale

	// we're interested only in road below horizont - so crop top image portion off
	crop(frame, temp_frame, cvRect(0,frame_size.height,frame_size.width,frame_size.height));
	cvCvtColor(temp_frame, grey, CV_BGR2GRAY); // convert to grayscale

	// Perform a Gaussian blur ( Convolving with 5 X 5 Gaussian) & detect edges
	cvSmooth(grey, grey, CV_GAUSSIAN, 5, 5);
	cvCanny(grey, edges, CANNY_MIN_TRESHOLD, CANNY_MAX_TRESHOLD);

	// do Hough transform to find lanes
	double rho = 1;
	double theta = CV_PI/180;
	CvSeq* lines = cvHoughLines2(edges, houghStorage, CV_HOUGH_PROBABILISTIC, rho, theta, HOUGH_TRESHOLD, HOUGH_MIN_LINE_LENGTH, HOUGH_MAX_LINE_GAP);

	processLanes(lines, edges, temp_frame);
	// show middle line
	cvLine(temp_frame, cvPoint(frame_size.width/2,0), cvPoint(frame_size.width/2,frame_size.height), CV_RGB(255, 255, 0), 1);

	t_per_line = 1000*((double)getTickCount() - t)/getTickFrequency();
	if ( count < PRINT_COUNT ) 
	    printf("\t time taken per processing one line = %lf milliseconds.\n", t_per_line );


        cvResize (grey, grey2, CV_INTER_LINEAR);
	cvShowImage("Grey",  grey2);
	cvMoveWindow("Grey",  0, 0); 

	cvResize (edges, edges2, CV_INTER_LINEAR);
	cvShowImage("Edges", edges2);
	cvMoveWindow("Edges", 0, frame_size.height+25);

	cvResize (temp_frame, temp_frame2, CV_INTER_LINEAR);
	cvShowImage("Color", temp_frame2);
	cvMoveWindow("Color", 100, 2*(frame_size.height+25)); 
#endif

	key_pressed = cvWaitKey(15);

/*        t = 1000*((double)getTickCount() - t)/getTickFrequency();*/
/*        if ( count < PRINT_COUNT ) */
/*            printf("\tcount = %d  time taken per frame = %lf milliseconds.\n\n", count, t );*/

    }



























#if 0
    int i, j;
    CvMemStorage* storage = cvCreateMemStorage(0);
    IplImage* img = cvCreateImage( cvSize(w,w), 8, 1 );
    IplImage* img32f = cvCreateImage( cvSize(w,w), IPL_DEPTH_32F, 1 );
    IplImage* img32s = cvCreateImage( cvSize(w,w), IPL_DEPTH_32S, 1 );
    IplImage* img3 = cvCreateImage( cvSize(w,w), 8, 3 );
    (void)argc; (void)argv;

    cvZero( img );

    for( i=0; i < 6; i++ )
    {
        int dx = (i%2)*250 - 30;
        int dy = (i/2)*150;
        CvScalar white = cvRealScalar(255);
        CvScalar black = cvRealScalar(0);

        if( i == 0 )
        {
	    for( j = 0; j <= 10; j++ )
            {
                double angle = (j+5)*CV_PI/21;
                cvLine(img, cvPoint(cvRound(dx+100+j*10-80*cos(angle)),
                    cvRound(dy+100-90*sin(angle))),
                    cvPoint(cvRound(dx+100+j*10-30*cos(angle)),
                    cvRound(dy+100-30*sin(angle))), white, 3, 8, 0);
            }
        }

	cvEllipse( img, cvPoint(dx+150, dy+100), cvSize(100,70), 0, 0, 360, white, -1, 8, 0 );
	cvEllipse( img, cvPoint(dx+115, dy+70), cvSize(30,20), 0, 0, 360, black, -1, 8, 0 );
	cvEllipse( img, cvPoint(dx+185, dy+70), cvSize(30,20), 0, 0, 360, black, -1, 8, 0 );
	cvEllipse( img, cvPoint(dx+115, dy+70), cvSize(15,15), 0, 0, 360, white, -1, 8, 0 );
	cvEllipse( img, cvPoint(dx+185, dy+70), cvSize(15,15), 0, 0, 360, white, -1, 8, 0 );
	cvEllipse( img, cvPoint(dx+115, dy+70), cvSize(5,5), 0, 0, 360, black, -1, 8, 0 );
	cvEllipse( img, cvPoint(dx+185, dy+70), cvSize(5,5), 0, 0, 360, black, -1, 8, 0 );
	cvEllipse( img, cvPoint(dx+150, dy+100), cvSize(10,5), 0, 0, 360, black, -1, 8, 0 );
	cvEllipse( img, cvPoint(dx+150, dy+150), cvSize(40,10), 0, 0, 360, black, -1, 8, 0 );
	cvEllipse( img, cvPoint(dx+27, dy+100), cvSize(20,35), 0, 0, 360, white, -1, 8, 0 );
	cvEllipse( img, cvPoint(dx+273, dy+100), cvSize(20,35), 0, 0, 360, white, -1, 8, 0 );
    }

    cvNamedWindow( "image", 1 );
    cvShowImage( "image", img );

    cvWaitKey(0);
#endif


    return 0;
}
