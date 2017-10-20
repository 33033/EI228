#include "cv.h"
#include "highgui.h"
#include<ctype.h>
#include <iostream>

template<class T> class Image
{
private:
	IplImage* imgp;
public:
	Image(IplImage* img = 0) { imgp = img; }
	~Image() { imgp = 0; }
	void operator=(IplImage* img) { imgp = img; }
	inline T* operator[](const int rowIndx) {
		return ((T *)(imgp->imageData + rowIndx*imgp->widthStep));
	}
};

void cvThin(IplImage *src, IplImage *dst, int iterations = 1)
{
	cvCopy(src, dst);
	Image<unsigned char> dstdat(dst);
	IplImage *t_image = cvCloneImage(src);
	Image<unsigned char> t_dat(t_image);
	for (int n = 0; n < iterations; ++n)
		for (int s = 0; s <= 1; ++s)
		{
			cvCopy(dst, t_image);
			for (int i = 0; i < src->height; ++i)
				for (int j = 0; j < src->width; ++j)
					if (t_dat[i][j])
					{
						int a = 0, b = 0;
						int d[8][2] = { { -1, 0 },{ -1,1 },{ 0,1 } ,{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 } };
						int p[8];
						p[0] = (i == 0) ? 0 : t_dat[i - 1][j];
						for (int k = 1; k <= 8; ++k)
						{
							if (i + d[k % 8][0] < 0 || i + d[k % 8][0] >= src->height ||
								j + d[k % 8][1] < 0 || j + d[k % 8][1] >= src->width)
								p[k % 8] = 0;
							else
								p[k % 8] = t_dat[i + d[k % 8][0]][j + d[k % 8][1]];
							if (p[k % 8])
							{
								++b;
								if (!p[k - 1])
									++a;
							}
						}
						if (b >= 2 && b <= 6 && a == 1)
							if (!s && !(p[2] && p[4] && (p[0] || p[6])))
								dstdat[i][j] = 0;
							else if (s && !(p[0] && p[6] && (p[2] || p[4])))
								dstdat[i][j] = 0;
					}
		}
	cvReleaseImage(&t_image);
}
IplImage* Thin(IplImage *input)
{
	IplImage *dst, *src;
	const int MAX_THINNING_TIMES = 18;

	src = cvCreateImage(cvSize(input->width, input->height), IPL_DEPTH_8U, 1);

	cvErode(input, src);

	dst = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 1);
	cvThin(src, dst, MAX_THINNING_TIMES);

	return dst;
}

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
	int i = 0;
	while (flag != 'q')
	{
		_hmax = hmax, _hmin = hmin, _vmin = vmin, _vmax = vmax, _smin = smin, _smax = smax;
		//������Ĥ��
		cvInRangeS(hsv, cvScalar(MIN(_hmax, _hmin), MIN(_smax, _smin), MIN(_vmax, _vmin), 0),
			cvScalar(MAX(_hmax, _hmin), MAX(_smax, _smin), MAX(_vmax, _vmin), 0), mask);

		//��ʾͼ��
		cvShowImage("mask", mask);
		flag = cvWaitKey(40);
		i++;
		if (i > 75) break;
	}
	//*********************************************************


	/************************ϸ��*************************
	*
	*
	*
	*/
	IplImage *thinimg;
	cvThin(mask, thinimg, 1);
	cvNamedWindow("thinimg", CV_WINDOW_AUTOSIZE);
	cvShowImage("thinimg", thinimg);

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