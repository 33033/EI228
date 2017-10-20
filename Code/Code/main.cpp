#include "cv.h"
#include "highgui.h"
#include<ctype.h>
#include <iostream>

int main()
{

	/************************透视变换*************************
	*
	*
	*
	*/
	IplImage* img = cvLoadImage("2.jpg"); //原始图像
	IplImage* transimg = cvCreateImage(cvSize(400, 400), IPL_DEPTH_8U, 3);
	//创建一个400*400的24位彩色图像，保存变换结果
	CvMat* transmat = cvCreateMat(3, 3, CV_32FC1); //创建一个3*3的单通道32位浮点矩阵保存变换数据
	CvPoint2D32f originpoints[4]; //保存四个点的原始坐标
	CvPoint2D32f newpoints[4]; //保存这四个点的新坐标
	originpoints[0] = cvPoint2D32f(20, 20);
	newpoints[0] = cvPoint2D32f(20, 20);
	originpoints[1] = cvPoint2D32f(380, 20);
	newpoints[1] = cvPoint2D32f(380, 20);
	originpoints[2] = cvPoint2D32f(20, 380);
	newpoints[2] = cvPoint2D32f(20, 380);
	originpoints[3] = cvPoint2D32f(380, 380);
	newpoints[3] = cvPoint2D32f(380, 380);
	cvGetPerspectiveTransform(originpoints, newpoints, transmat); //根据四个点计算变换矩阵
	cvWarpPerspective(img, transimg, transmat); //根据变换矩阵计算图像的变换
	//************************************************************


	/************************二值化*************************
	*
	*
	*
	*/
	int hmax = 0, hmin = 0, vmin = 0, vmax = 0, smin = 0, smax = 0;
	IplImage *hsv, *mask;
	//创建窗口
	cvNamedWindow("image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("hsv", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("mask", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Track", CV_WINDOW_AUTOSIZE);

	cvCreateTrackbar("Hmin", "Track", &hmin, 256, 0);
	cvCreateTrackbar("Hmax", "Track", &hmax, 256, 0);
	cvCreateTrackbar("Smin", "Track", &smin, 256, 0);
	cvCreateTrackbar("Smax", "Track", &smax, 256, 0);
	cvCreateTrackbar("Vmin", "Track", &vmin, 256, 0);
	cvCreateTrackbar("Vmax", "Track", &vmax, 256, 0);


	//分配图像空间
	hsv = cvCreateImage(cvGetSize(img), 8, 3);
	mask = cvCreateImage(cvGetSize(img), 8, 1);
	//将RGB转化为HSV色系
	cvCvtColor(img, hsv, CV_RGB2BGR);
	cvShowImage("image", img);
	cvShowImage("hsv", hsv);
	int _hmax = 0, _hmin = 0, _vmin = 0, _vmax = 0, _smin = 0, _smax = 0, flag = 0;
	while (flag != 'q')
	{
		_hmax = hmax, _hmin = hmin, _vmin = vmin, _vmax = vmax, _smin = smin, _smax = smax;
		//制作掩膜板
		cvInRangeS(hsv, cvScalar(MIN(_hmax, _hmin), MIN(_smax, _smin), MIN(_vmax, _vmin), 0),
			cvScalar(MAX(_hmax, _hmin), MAX(_smax, _smin), MAX(_vmax, _vmin), 0), mask);

		//显示图像
		cvShowImage("mask", mask);
		flag = cvWaitKey(40);
	}
	//*********************************************************


	/************************细化*************************
	*
	*
	*
	*/

	//*********************************************************


	/************************寻找路径*************************
	*
	*
	*
	*/

	//*********************************************************
	cvDestroyAllWindows();
	cvReleaseImage(&img);
	cvReleaseImage(&hsv);
	cvReleaseImage(&mask);
	system("pause");
	return 0;
}