#include "operationcalibration.h"
#include "ui_operationcalibration.h"

operationCalibration::operationCalibration(std::vector<cv::Mat>  m_saveImageAll,QWidget *parent):
	m_saveImageAll(m_saveImageAll),
	QDialog(parent),
	ui(new Ui::operationCalibration)
{
	ui->setupUi(this);
	m_cabOption.w = ui->wSpinBox->value();
	m_cabOption.h = ui->hSpinBox->value();
}

operationCalibration::~operationCalibration()
{
	delete ui;
}

void operationCalibration::on_wSpinBox_valueChanged(int arg1)
{
	m_cabOption.w = arg1;
}

void operationCalibration::on_hSpinBox_valueChanged(int arg1)
{
	m_cabOption.h = arg1;
}

void operationCalibration::on_caliPushButton_clicked()
{
	for(int i = 0;i < m_saveImageAll.size();i++){
		cv::Mat proImage;
		std::vector<cv::Point2f> tmpPoint;
		cv::cvtColor(m_saveImageAll[i],proImage,cv::COLOR_BGR2GRAY);

		cv::findChessboardCorners(proImage,cv::Size(m_cabOption.w,m_cabOption.h),tmpPoint,
								  cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE);
		qDebug("Pix (%f,%f)",tmpPoint[0].x,tmpPoint[0].y);
//		cv::drawChessboardCorners(proImage,cv::Size(m_cabOption.w,m_cabOption.h),tmpPoint,true);
//		cv::imshow(QString::number(i,10).toStdString(),proImage);
		cv::TermCriteria termCriteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS, 30, 0.01);
		cv::cornerSubPix(proImage, tmpPoint, cvSize(5,5), cvSize(-1,-1), termCriteria);
		qDebug("SubPix (%f,%f)",tmpPoint[0].x,tmpPoint[0].y);
		qDebug() << tmpPoint.size();
	}
}
