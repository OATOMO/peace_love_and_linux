#ifndef LOOKOVERIMAGE_H
#define LOOKOVERIMAGE_H

#include <QDialog>
#include <vector>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <QFileDialog>

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
