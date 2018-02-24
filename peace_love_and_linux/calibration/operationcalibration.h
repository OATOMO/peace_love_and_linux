#ifndef OPERATIONCALIBRATION_H
#define OPERATIONCALIBRATION_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include <vector>
#include <QDebug>
#include <QMap>
#include <unistd.h>

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

class operationCalibration : public QDialog
{
	Q_OBJECT

public:
	explicit operationCalibration(std::vector<cv::Mat>  m_saveImageAll,QWidget *parent = 0);
	~operationCalibration();
//fun
	void initOptionUi();
	void calcChessboardCorners(cv::Size boardSize, float squareSize, std::vector<cv::Point3f>& corners, Pattern patternType = CHESSBOARD);
//data
	std::vector<cv::Mat>  m_saveImageAll;				//需要标定的原始图片
	CabOption m_cabOption;								//标定参数集
	std::vector<std::vector<cv::Point3f> > objectPoints;	//世界坐标系中的点,由calcChessboardCorners求出
	std::vector<std::vector<cv::Point2f> > imagePoints;	//其对应的图像中的点
	cv::Mat cameraMatrix;								//内参矩阵
	cv::Mat distCoeffs;								//畸变矩阵
	std::vector<cv::Mat> rvecs;						//旋转向量
	std::vector<cv::Mat> tvecs;						//位移向量
	int flags;

private slots:
	void on_wSpinBox_valueChanged(int arg1);

	void on_hSpinBox_valueChanged(int arg1);

	void on_squareSizeSpinBox_valueChanged(double arg1);

	void on_aspectRatioSpinBox_valueChanged(double arg1);

	void on_patternComboBox_activated(const QString &arg1);

	void on_caliPushButton_clicked();




	void on_aspectRatioCheckBox_stateChanged(int arg1);

private:
	Ui::operationCalibration *ui;
};

#endif // OPERATIONCALIBRATION_H
