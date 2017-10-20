#include "cv.h"
#include "highgui.h"
#include<ctype.h>
#include <iostream>

int main()
{

	/************************͸�ӱ任*************************
	*
	*
	*
	*/
	IplImage* img = cvLoadImage("2.jpg"); //ԭʼͼ��
	IplImage* transimg = cvCreateImage(cvSize(400, 400), IPL_DEPTH_8U, 3);
	//����һ��400*400��24λ��ɫͼ�񣬱���任���
	CvMat* transmat = cvCreateMat(3, 3, CV_32FC1); //����һ��3*3�ĵ�ͨ��32λ������󱣴�任����
	CvPoint2D32f originpoints[4]; //�����ĸ����ԭʼ����
	CvPoint2D32f newpoints[4]; //�������ĸ����������
	originpoints[0] = cvPoint2D32f(20, 20);
	newpoints[0] = cvPoint2D32f(20, 20);
	originpoints[1] = cvPoint2D32f(380, 20);
	newpoints[1] = cvPoint2D32f(380, 20);
	originpoints[2] = cvPoint2D32f(20, 380);
	newpoints[2] = cvPoint2D32f(20, 380);
	originpoints[3] = cvPoint2D32f(380, 380);
	newpoints[3] = cvPoint2D32f(380, 380);
	cvGetPerspectiveTransform(originpoints, newpoints, transmat); //�����ĸ������任����
	cvWarpPerspective(img, transimg, transmat); //���ݱ任�������ͼ��ı任
	//************************************************************


	/************************��ֵ��*************************
	*
	*
	*
	*/
	int hmax = 0, hmin = 0, vmin = 0, vmax = 0, smin = 0, smax = 0;
	IplImage *hsv, *mask;
	//��������
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


	//����ͼ��ռ�
	hsv = cvCreateImage(cvGetSize(img), 8, 3);
	mask = cvCreateImage(cvGetSize(img), 8, 1);
	//��RGBת��ΪHSVɫϵ
	cvCvtColor(img, hsv, CV_RGB2BGR);
	cvShowImage("image", img);
	cvShowImage("hsv", hsv);
	int _hmax = 0, _hmin = 0, _vmin = 0, _vmax = 0, _smin = 0, _smax = 0, flag = 0;
	while (flag != 'q')
	{
		_hmax = hmax, _hmin = hmin, _vmin = vmin, _vmax = vmax, _smin = smin, _smax = smax;
		//������Ĥ��
		cvInRangeS(hsv, cvScalar(MIN(_hmax, _hmin), MIN(_smax, _smin), MIN(_vmax, _vmin), 0),
			cvScalar(MAX(_hmax, _hmin), MAX(_smax, _smin), MAX(_vmax, _vmin), 0), mask);

		//��ʾͼ��
		cvShowImage("mask", mask);
		flag = cvWaitKey(40);
	}
	//*********************************************************


	/************************ϸ��*************************
	*
	*
	*
	*/

	//*********************************************************


	/************************Ѱ��·��*************************
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