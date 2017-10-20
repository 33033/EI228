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
	cvNamedWindow("win1");
	cvShowImage("win1", img); //显示原始图像
	cvNamedWindow("win2");
	cvShowImage("win2", transimg); //显示变换后的图像
	cvWaitKey();
	//************************************************************


	/************************二值化*************************
	*
	*
	*
	*/

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
	return 0;
}