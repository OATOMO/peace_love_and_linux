#include "videocapture.h"

videoCapture::videoCapture(int videoIndex,cv::Size2i  imageSize):
	videoIndex(videoIndex),imageSize(imageSize)
{
	stopFlag = false;

}

videoCapture::~videoCapture()
{
	stopFlag = true;
//	cv::waitKey(100);
//	sleep(1);
	msleep(100);
	qDebug() << "~videoCapture()";
	capture.release();	
}

void videoCapture::run(){
	capture.open(videoIndex);
	capture.set(CV_CAP_PROP_FRAME_WIDTH,imageSize.width);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,imageSize.height);
	capture.set(CV_CAP_PROP_FPS,15);
	qDebug() << capture.get(CV_CAP_PROP_FPS);

//	qDebug() << videoIndex;
	while(!stopFlag){
	if(!capture.isOpened()){
		qDebug() << "open video" << videoIndex << " failed";
		exit(-1) ;
	}

	capture >> srcImage;


	emit videoShow(srcImage);
	srcImage.release();
	}
}
