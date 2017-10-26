#include <cv.h>
#include <iostream>
#include <highgui.h>

using namespace std;

int main()
{
	IplImage* img = cvLoadImage("D:\3.png", 0); //�Ե�ͨ����ʽ��ͼ�񣬷��ص�ͨ���Ҷ�ͼ
		cvNamedWindow("win1");
	CvMemStorage* storage = cvCreateMemStorage(); //����һƬ�ڴ�����洢�߶�����
		CvSeq* lines = cvHoughLines2(img, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI / 180,
			30, 40, 200); //Hough�任��ֱ��
	IplImage* img1 = cvCreateImage(cvGetSize(img), 8, 1); //�½�һ��ͬ�����ͼ�����ڻ����ҵ���ֱ�߶�
		cvSetZero(img1); //���Ϊ��ɫ
	for (int i = 0; i < lines->total; i++)
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines, i); //��ȡ��i���߶ε������˵�
		cout << line[0].x << " " << line[0].y << endl;
		cout << line[1].x << " " << line[1].y << endl;
			cvLine(img1, line[0], line[1], cvScalar(255)); //�ð�ɫ���������߶�
	}
	cvShowImage("win1", img1);
	cvWaitKey();
	return 0;
}