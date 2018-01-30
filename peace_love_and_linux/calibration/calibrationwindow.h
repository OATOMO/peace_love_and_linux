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

private:
	Ui::calibrationWindow *ui;

	struct initInfo_D info_D;
};

#endif // CALIBRATIONWINDOW_H
