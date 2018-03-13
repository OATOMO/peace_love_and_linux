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
