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
#ifndef REPROJECTIONCHECK_H
#define REPROJECTIONCHECK_H

#include <QDialog>
#include <opencv2/opencv.hpp>

namespace Ui {
	class reProjectionCheck;
}

class reProjectionCheck : public QDialog
{
	Q_OBJECT

public:
	explicit reProjectionCheck(std::vector<cv::Mat>  m_saveImageAll,QWidget *parent = 0);
	~reProjectionCheck();
	//data
	std::vector<cv::Mat>  m_saveImageAll;
	int currNumber;
	//fun
	void initUI();
	void updateImage(int number);
	void setNumberLabel(int num);

private slots:
	void on_beforePushButton_clicked();

	void on_afterPushButton_clicked();

private:
	Ui::reProjectionCheck *ui;
};

#endif // REPROJECTIONCHECK_H
