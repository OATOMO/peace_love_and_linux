#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

#include <QDialog>
#include <QString>
#include <QMetaType>
#include <QSharedMemory>
#include <QMessageBox>

extern "C"{
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <sys/ioctl.h>
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
//self
#include "videoCapture/videocapture.h"
#include "calibration/lookoverimage.h"
#include "calibration/operationcalibration.h"

//map struct initInfo_D member vaildFlag
#define VAILD 	1;
#define INVAILD	0;

namespace Ui {
	class calibrationWindow;
}

struct initInfo_D{
	bool vaildFlag;
	u_int8_t videoNumber;
	QString cJsonRoot;
	QString currVideoX; //当前使用的video
	uint currWidth;     //当前width
	uint currHieght;    //当前height
};




class calibrationWindow : public QDialog
{
	Q_OBJECT

public:
	explicit calibrationWindow(QWidget *parent = 0);
	~calibrationWindow();
	void closeEvent(QCloseEvent * event);

	//fun
	void initData();
	u_int8_t getVideoNumber();
	void __getVideoProperty(QString devName);
	void getVideoProperty();
	void initInterface();
	void getInitInfo();

	void setSaveImageNumberLabel(int number);
	void setSelfFont();
	//data
	videoCapture * capThread;
	cv::Mat m_srcImage;
	std::vector<cv::Mat > m_saveImageAll;
	uint saveNumber = 0;
	operationCalibration * operationCal;
	lookoverImage * loWindow;
signals:
	void clickX();

private slots:
	void grapGetVideo(cv::Mat &);

	void on_startPushButton_clicked();

	void on_selectFMTComboBox_activated(const QString &arg1);

	void on_selectVideoComboBox_activated(const QString &arg1);

	void on_capturePushButton_clicked();

	void on_resetPushButton_clicked();

	void on_lookoverPushButton_clicked();

	void channgeImageN(void);

	void on_openImglPushButton_clicked();

	void on_calibrationPushButton_clicked();

private:
	Ui::calibrationWindow *ui;

	struct initInfo_D info_D;
};

#endif // CALIBRATIONWINDOW_H
