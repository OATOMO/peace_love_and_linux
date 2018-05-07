/*			DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
					Version 2, December 2004

 Copyright (C) 2017 Romain Lespinasse <lzlzwan2481111@sina.com>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

			DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.

need:
  @ SSBA (Sparse Levenberg-Marquardt based non-linear least squares optimizer and
		  bundle adjustment implementation)
  @ opencv_contrib_3.2
  @ openmp
*/
#ifndef SFMWINDOW_H
#define SFMWINDOW_H

#include <QDialog>
#include <QString>
#include <QMetaType>
#include <QSharedMemory>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
extern "C"{
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <linux/videodev2.h>
//3rd party
#include <cjson/cJSON.h>
}
//c++
#include <vector>
//3rd party
#include "FONT/iconhelper.h"
#include <opencv2/opencv.hpp>
#include <nonfree.hpp>
#include "featureMatcher/cpusurffeaturematcher.h"

//self
#include "common/loadmat.h"
//cJSON key
#define IMAGE_NUMBER "image_n"
#define IMAGE_PATH   "image_path"
using namespace cv::xfeatures2d;

namespace Ui {
	class SFMWindow;
}

class SFMWindow : public QDialog,public loadMat
{
	Q_OBJECT

public:
	explicit SFMWindow(QWidget *parent = 0);
	~SFMWindow();
	//main func

	//sub func
	void setSelectFeatureDetector();
	void closeEvent(QCloseEvent * event);
	void setSaveImageNumberLabel(int number);
	void initInterface();
	void selectFeatureDetector();
	//data
	std::vector<cv::Mat > m_saveImageAll;
	uint saveNumber = 0;
	QString detectorType;
	std::vector<std::vector<cv::KeyPoint> > imgpts;

//	cv::Mat cam_matrix,distortion_coeff;


private slots:
	void on_openImglPushButton_clicked();
	void on_startPushButton_clicked();

	void on_loadCamMatPushButton_clicked();

signals:
	void clickX();
private:
	Ui::SFMWindow *ui;
};

QString printMat(cv::Mat srcMat);
#endif // SFMWINDOW_H
