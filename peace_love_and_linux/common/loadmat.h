#ifndef LOADMAT_H
#define LOADMAT_H

#include <unistd.h>
#include <QDateTime>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QTimer>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <opencv2/opencv.hpp>

class loadMat
{
public:
	loadMat();
	//data
	cv::Mat cam_matrix,distortion_coeff;
	QString root_j_s;
	//func
	bool load(QString path);
	void __parseMatrix(QString& str,QString matName,cv::Mat& srcMat);
	QString& printMat(const cv::Mat &srcMat,QString &str);
};

#endif // LOADMAT_H
