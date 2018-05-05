#ifndef LOOKOVERIMAGE_H
#define LOOKOVERIMAGE_H

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
#include <QDialog>
#include <vector>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QFileDialog>
//3rd
#include "cjson/cJSON.h"


//cJSON key
#define IMAGE_NUMBER "image_n"
#define IMAGE_PATH   "image_path"

namespace Ui {
	class lookoverImage;
}

class lookoverImage : public QDialog
{
	Q_OBJECT

public:
	explicit lookoverImage(std::vector<cv::Mat> * m_saveImageAll,QWidget *parent = 0);
	~lookoverImage();
	//fun
	void initIcon();
	void initInterface();
	void updateImage(int number);

	//data
	uint currNumber;
	std::vector<cv::Mat > * m_saveImageAll;


signals:
	void channgeImageN(void);

private slots:
	void on_beforePushButton_clicked();

	void on_afterPushButton_clicked();

	void on_delPushButton_clicked();

	void on_savePushButton_clicked();

private:
	Ui::lookoverImage *ui;
};

#endif // LOOKOVERIMAGE_H
