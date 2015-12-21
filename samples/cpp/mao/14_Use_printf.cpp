#include <stdio.h>
//--------------------------------------\u3010\u7a0b\u5e8f\u8aaa\u660e\u3011-------------------------------------------
//		\u7a0b\u5e8f\u8aaa\u660e\uff1a\u300aOpenCV3\u7a0b\u5f0f\u8a2d\u8a08\u5165\u9580\u300bOpenCV2\u7248\u66f8\u672c\u914d\u5957\u7bc4\u4f8b\u7a0b\u5e8f14
//		\u7a0b\u5e8f\u63cf\u8ff0\uff1aprintf\u51fd\u6578\u7528\u6cd5\u7bc4\u4f8b
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528\u64cd\u4f5c\u7cfb\u7d71\uff1a Windows 7 64bit
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528IDE\u7248\u672c\uff1aVisual Studio 2010
//		\u958b\u767c\u6e2c\u8a66\u6240\u7528OpenCV\u7248\u672c\uff1a	2.4.9
//		2014\u5e7406\u6708 Created by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//		2014\u5e7411\u6708 Revised by @\u6dfa\u58a8_\u6bdb\u661f\u4e91
//------------------------------------------------------------------------------------------------

#include <opencv2/opencv.hpp>
#include <stdio.h>
using namespace cv;

int main( )
{
	int a=66,b=68;
	printf("\n\t%d %d\n",a,b);//\u8f38\u51fa\u5341\u9032\u5236\u6574\u578b
	printf("\n\t%06d,%06d\n",a,b);//\u8f38\u51fa6\u4f4d\u5341\u9032\u5236\u6574\u578b
	printf("\n\t%c,%c\n",a,b);//\u6309\u5b57\u8868\u578b\u8f38\u51fa
	printf("\n\t\u7d50\u679c\u70ba\uff1aa=%d,b=%d",a,b);//\u53ef\u4ee5\u914d\u5408\u5176\u4ed6\u5167\u5bb9\u4e00\u540c\u8f38\u51fa
	getchar();//\u7b49\u5f85\u8b80\u5165\u4efb\u610f\u5b57\u8868\u800c\u7d50\u675f\uff0c\u5728\u6b64\u7528\u4e8e\u4fdd\u6301\u8996\u7a97\u986f\u793a\uff0c\u76f4\u5230\u4efb\u610f\u6309\u9375\u6309\u4e0b
}
