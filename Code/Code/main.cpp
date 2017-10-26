#include <cv.h>
#include <iostream>
#include <highgui.h>

using namespace std;

int main()
{
	IplImage* img = cvLoadImage("D:\3.png", 0); //以单通道方式打开图像，返回单通道灰度图
		cvNamedWindow("win1");
	CvMemStorage* storage = cvCreateMemStorage(); //创建一片内存区域存储线段数据
		CvSeq* lines = cvHoughLines2(img, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI / 180,
			30, 40, 200); //Hough变换找直线
	IplImage* img1 = cvCreateImage(cvGetSize(img), 8, 1); //新建一幅同样大的图像，用于画出找到的直线段
		cvSetZero(img1); //填充为黑色
	for (int i = 0; i < lines->total; i++)
	{
		CvPoint* line = (CvPoint*)cvGetSeqElem(lines, i); //读取第i条线段的两个端点
		cout << line[0].x << " " << line[0].y << endl;
		cout << line[1].x << " " << line[1].y << endl;
			cvLine(img1, line[0], line[1], cvScalar(255)); //用白色画出这条线段
	}
	cvShowImage("win1", img1);
	cvWaitKey();
	return 0;
}