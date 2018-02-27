#ifndef OPERATIONCALIBRATION_H
#define OPERATIONCALIBRATION_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include <vector>
#include <QDebug>
#include <QMap>
#include <unistd.h>
#include <QDateTime>

namespace Ui {
	class operationCalibration;
}

enum Pattern { CHESSBOARD/*棋盘格*/, CIRCLES_GRID/*圆网格*/, ASYMMETRIC_CIRCLES_GRID/*非对称圆网格*/ };

struct CabOption{
	uint w;					//the number of inner corners per one of board dimension
	uint h;					//the number of inner corners per another board dimension
	Pattern pattern; 		//the type of pattern: chessboard or circles' grid
	float squareSize;     	//square size in some user-defined units (1 by default)
	cv::Mat outCameraParams;//the output filename for intrinsic [and extrinsic] parameters
	//						//write detected feature points
	//						//write extrinsic parameters
	//						//assume zero tangential distortion
	float aspectRatio;		//fix aspect ratio (fx/fy)
	//						//fix the principal point at the center
	//						//flip the captured images around the horizontal axis
};

struct CabReturn{
	std::vector<float > reprojErrs;
	double totalAvgErr;
};

class operationCalibration : public QDialog
{
	Q_OBJECT

public:
	explicit operationCalibration(std::vector<cv::Mat>  m_saveImageAll,QWidget *parent = 0);
	~operationCalibration();
//fun
	void initOptionUi();
	void calcChessboardCorners(cv::Size boardSize, float squareSize, std::vector<cv::Point3f>& corners, Pattern patternType = CHESSBOARD);
	void saveCameraParams();
	//计算重投影误差
	double computeReprojectionErrors(
		const std::vector<std::vector<cv::Point3f> >& objectPoints,
		const std::vector<std::vector<cv::Point2f> >& imagePoints,
		const std::vector<cv::Mat>& rvecs, const std::vector<cv::Mat>& tvecs,
		const cv::Mat& cameraMatrix, const cv::Mat& distCoeffs,
		std::vector<float>& perViewErrors);

//data
	std::vector<cv::Mat>  m_saveImageAll;				//需要标定的原始图片
	CabOption m_cabOption;								//标定参数集
	CabReturn m_cabRet;
	std::vector<std::vector<cv::Point3f> > objectPoints;	//世界坐标系中的点,由calcChessboardCorners求出
	std::vector<std::vector<cv::Point2f> > imagePoints;	//其对应的图像中的点
	cv::Mat cameraMatrix;								//内参矩阵
	cv::Mat distCoeffs;								//畸变矩阵
	std::vector<cv::Mat> rvecs;						//旋转向量
	std::vector<cv::Mat> tvecs;						//位移向量
	int flags;										//标定函数所采用的模型

private slots:
	void on_wSpinBox_valueChanged(int arg1);

	void on_hSpinBox_valueChanged(int arg1);

	void on_squareSizeSpinBox_valueChanged(double arg1);

	void on_aspectRatioSpinBox_valueChanged(double arg1);

	void on_patternComboBox_activated(const QString &arg1);

	void on_aspectRatioCheckBox_stateChanged(int arg1);

	void on_caliPushButton_clicked();





private:
	Ui::operationCalibration *ui;
};

#endif // OPERATIONCALIBRATION_H
