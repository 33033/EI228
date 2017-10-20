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
	cvNamedWindow("win1");
	cvShowImage("win1", img); //��ʾԭʼͼ��
	cvNamedWindow("win2");
	cvShowImage("win2", transimg); //��ʾ�任���ͼ��
	cvWaitKey();
	//************************************************************


	/************************��ֵ��*************************
	*
	*
	*
	*/

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
	return 0;
}