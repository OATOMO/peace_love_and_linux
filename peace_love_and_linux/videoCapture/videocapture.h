#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H

#include <QThread>
#include <QDebug>
#include <QSharedMemory>

#include <opencv2/opencv.hpp>

class videoCapture:public QThread
{
	Q_OBJECT
public:
	videoCapture(int videoIndex,cv::Size2i imageSize);
	~videoCapture();

	cv::Mat srcImage;
	cv::VideoCapture capture;
	int videoIndex;
	cv::Size2i imageSize;
	bool stopFlag;

protected:
	void run();
signals:
	void videoShow(cv::Mat &);

};

#endif // VIDEOCAPTURE_H
