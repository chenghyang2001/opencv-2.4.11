
#include <stdio.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

int main( )
{
	int a=66,b=68;
	printf("\n\t%d %d\n",a,b);//輸出十進制整型
	printf("\n\t%06d,%06d\n",a,b);//輸出6位十進制整型
	printf("\n\t%c,%c\n",a,b);//按字表型輸出
	printf("\n\t結果為：a=%d,b=%d",a,b);//可以配合其他內容一同輸出
	printf("\n\tCV version = " CV_VERSION);  //
	printf("\n\tCV version = " CV_VERSION);  //
	printf("\n");  
	getchar();//等待讀入任意字表而結束，在此用于保持視窗顯示，直到任意按鍵按下
}
