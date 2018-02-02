#ifndef OPERATIONCALIBRATION_H
#define OPERATIONCALIBRATION_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include <vector>

namespace Ui {
	class operationCalibration;
}

enum Pattern { CHESSBOARD/*棋盘格*/, CIRCLES_GRID/*圆网格*/, ASYMMETRIC_CIRCLES_GRID/*非对称圆网格*/ };

struct CabOption{
	uint w;					//the number of inner corners per one of board dimension
	uint h;					//the number of inner corners per another board dimension
	Pattern pattern; 		//the type of pattern: chessboard or circles' grid
	int squareSize;     	//square size in some user-defined units (1 by default)
	cv::Mat outCameraParams;//the output filename for intrinsic [and extrinsic] parameters
	//						//write detected feature points
	//						//write extrinsic parameters
	//						//assume zero tangential distortion
	//						//fix aspect ratio (fx/fy)
	//						//fix the principal point at the center
	//						//flip the captured images around the horizontal axis
};

class operationCalibration : public QDialog
{
	Q_OBJECT

public:
	explicit operationCalibration(std::vector<cv::Mat>  &m_saveImageAll,QWidget *parent = 0);
	~operationCalibration();
//fun

//data
	std::vector<cv::Mat >  m_saveImageAll;
	CabOption m_cabOption;

private slots:
	void on_wSpinBox_valueChanged(int arg1);

	void on_hSpinBox_valueChanged(int arg1);

private:
	Ui::operationCalibration *ui;
};

#endif // OPERATIONCALIBRATION_H
