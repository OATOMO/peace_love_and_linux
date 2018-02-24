#include "operationcalibration.h"
#include "ui_operationcalibration.h"

operationCalibration::operationCalibration(std::vector<cv::Mat>  m_saveImageAll,QWidget *parent):
	m_saveImageAll(m_saveImageAll),
	QDialog(parent),
	ui(new Ui::operationCalibration)
{
	ui->setupUi(this);
	initOptionUi();
}

void operationCalibration::initOptionUi(){
	m_cabOption.w = ui->wSpinBox->value();
	m_cabOption.h = ui->hSpinBox->value();
	m_cabOption.squareSize = ui->squareSizeSpinBox->value();
	m_cabOption.aspectRatio = ui->aspectRatioSpinBox->value();
	on_patternComboBox_activated(ui->patternComboBox->currentText());
	flags = 0;

	//ui
//	ui->aspectRatioSpinBox->setDisabled(true);
	on_aspectRatioCheckBox_stateChanged(ui->aspectRatioCheckBox->isChecked());
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

void operationCalibration::on_squareSizeSpinBox_valueChanged(double arg1)
{
	m_cabOption.squareSize = arg1;
	qDebug() << m_cabOption.squareSize;
}

void operationCalibration::on_aspectRatioSpinBox_valueChanged(double arg1)
{
	m_cabOption.aspectRatio = arg1;
	qDebug() << m_cabOption.aspectRatio;
}

void operationCalibration::on_patternComboBox_activated(const QString &arg1)
{
	QMap<QString,int> m_map;
	m_map.insert("CHESSBOARD",1);
	m_map.insert("CIRCLES_GRID",2);
	m_map.insert("ASYMMETRIC_CIRCLES_GRID",3);

	switch((int)m_map.value(arg1)){
		case 1:
			m_cabOption.pattern = CHESSBOARD;
		break;
		case 2:
			m_cabOption.pattern = CIRCLES_GRID;
		break;
		case 3:
			m_cabOption.pattern = ASYMMETRIC_CIRCLES_GRID;
		break;
	}
	qDebug() << m_cabOption.pattern;
}

void operationCalibration::on_aspectRatioCheckBox_stateChanged(int arg1)
{
	if(arg1){
		ui->aspectRatioSpinBox->setEnabled(true);
	}
	else{
		ui->aspectRatioSpinBox->setDisabled(true);
	}
}


void operationCalibration::on_caliPushButton_clicked()
{
	for(int i = 0;i < m_saveImageAll.size();i++){
		cv::Mat proImage;
		std::vector<cv::Point2f> tmpPoint;
		cv::cvtColor(m_saveImageAll[i],proImage,cv::COLOR_BGR2GRAY);

		cv::findChessboardCorners(proImage,cv::Size(m_cabOption.w,m_cabOption.h),tmpPoint,
								  cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE);
		qDebug("%d: Pix (%f,%f)",i,tmpPoint[0].x,tmpPoint[0].y);
//		cv::drawChessboardCorners(proImage,cv::Size(m_cabOption.w,m_cabOption.h),tmpPoint,true);
//		cv::imshow(QString::number(i,10).toStdString(),proImage);
//		cv::TermCriteria termCriteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS, 30, 0.1);
		cv::cornerSubPix(proImage, tmpPoint, cvSize(11,11), cvSize(-1,-1), cv::TermCriteria(cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 30, 0.1 ));
		imagePoints.push_back(tmpPoint);
		qDebug("%d: SubPix (%f,%f)",i,tmpPoint[0].x,tmpPoint[0].y);
//		qDebug() << tmpPoint.size();


		cv::drawChessboardCorners(proImage,cv::Size(m_cabOption.w,m_cabOption.h),tmpPoint,true);
		cv::resize(proImage,proImage,cv::Size(320,240),0,0,cv::INTER_LINEAR);
		QImage viewTemp(proImage.data,proImage.cols,proImage.rows,QImage::Format_Indexed8);
		this->ui->imageLabel->setPixmap(QPixmap::fromImage(viewTemp));

	}

	if(ui->aspectRatioCheckBox->isChecked()){
		flags |= cv::CALIB_FIX_ASPECT_RATIO;
	}
	if(ui->zeroTangentCheckBox){
		flags |= cv::CALIB_ZERO_TANGENT_DIST;
	}
	if(ui->principalPointCheckBox){
		flags |= cv::CALIB_FIX_PRINCIPAL_POINT;
	}


	cameraMatrix = cv::Mat::eye(3,3,CV_64F);
	if(flags & cv::CALIB_FIX_ASPECT_RATIO){
		cameraMatrix.at<double>(0,0) = m_cabOption.aspectRatio;
	}

	distCoeffs = cv::Mat::zeros(8,1,CV_64F);

	objectPoints.resize(1);
	calcChessboardCorners(cv::Size(m_cabOption.w,m_cabOption.h),
						  m_cabOption.squareSize,
						  objectPoints[0],
						  m_cabOption.pattern);
	objectPoints.resize(imagePoints.size(),objectPoints[0]);

//	qDebug() << "objectPoints.size()" << objectPoints.size();

	/*
		@objectPoints:	世界坐标系中的点,由calcChessboardCorners求出	应该输入vector< vector< Point3f > >
		@imagePoings:	其对应的图像中的点,							应该输入vector< vector< Point3f > >
		@imageSize:		图像的大小，在计算相机的内参数和畸变矩阵需要用到
		@cameraMatrix:	内参数矩阵。输入一个Mat cameraMatrix即可
		@distCoeffs:	畸变矩阵。输入一个Mat distCoeffs即可
		rvecs:			旋转向量,应该输入一个Mat的vector,即vector<Mat> rvecs因为每个vector<Point3f>会得到一个rvecs
		tvecs:			位移向量,和rvecs一样，也应该为vector tvecs
	*/
	double rms = calibrateCamera(objectPoints, imagePoints, m_saveImageAll[0].size(),
			cameraMatrix,distCoeffs, rvecs, tvecs, flags|cv::CALIB_FIX_K4|cv::CALIB_FIX_K5);
						///*|CALIB_FIX_K3*/|CALIB_FIX_K4|CALIB_FIX_K5);
	qDebug("RMS error reported by calibrateCamera: %g\n", rms);
}


void operationCalibration::calcChessboardCorners(cv::Size boardSize, float squareSize,
				std::vector<cv::Point3f>& corners, Pattern patternType)
{
	corners.resize(0);

	switch (patternType) {
		case CHESSBOARD:
		case CIRCLES_GRID:
			for(int i = 0;i < boardSize.height;i++){
				for(int j = 0;j < boardSize.width;j++){
					corners.push_back(cv::Point3f(float(j*squareSize),
												  float(i*squareSize),0));
				}
			}
			break;

		case ASYMMETRIC_CIRCLES_GRID:
			for( int i = 0; i < boardSize.height; i++ ){
				for( int j = 0; j < boardSize.width; j++ ){
					corners.push_back(cv::Point3f(float((2*j + i % 2)*squareSize),
												  float(i*squareSize), 0));
				}
			}
			break;

		default:
			CV_Error(cv::Error::StsBadArg,"Unkown pattern type\n");
			break;
		}

}



