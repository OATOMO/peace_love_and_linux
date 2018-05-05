/*			DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
					Version 2, December 2004

 Copyright (C) 2017 Romain Lespinasse <lzlzwan2481111@sina.com>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

			DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
*/
#ifndef OPERATIONAR_H
#define OPERATIONAR_H

#include <QDialog>
#include <QString>
#include <QMetaType>
#include <QSharedMemory>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
//c++ 3rd
#include <opencv2/opencv.hpp>
#include <common/loadmat.h>

namespace Ui {
	class operationAR;
}

class operationAR : public QDialog,public loadMat
{
	Q_OBJECT

public:
	explicit operationAR(QWidget *parent = 0);
	~operationAR();
	void closeEvent(QCloseEvent * event);
	//data
//	QString root_j_s;
//	cv::Mat cameraMatrix;								//内参矩阵
//	cv::Mat distCoeffs;								//畸变矩阵
	//fun
//	void __parseMatrix(QString& str,QString matName,cv::Mat& srcMat);
//	QString& printMat(const cv::Mat &srcMat,QString &str);

signals:
	void clickX();
private slots:
	void on_loadCamMatPushButton_clicked();

private:
	Ui::operationAR *ui;
};

#endif // OPERATIONAR_H
