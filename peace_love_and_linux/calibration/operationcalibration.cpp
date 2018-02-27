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
	//初始化标定参数和界面
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
			m_cabOption.pattern = CHESSBOARD;				//棋盘格
		break;
		case 2:
			m_cabOption.pattern = CIRCLES_GRID;				//圆网格	
		break;
		case 3:
			m_cabOption.pattern = ASYMMETRIC_CIRCLES_GRID;	//非对称园网格
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

		//找角点
		cv::findChessboardCorners(proImage,cv::Size(m_cabOption.w,m_cabOption.h),tmpPoint,
								  cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE);
		qDebug("%d: Pix (%f,%f)",i,tmpPoint[0].x,tmpPoint[0].y);
//		cv::TermCriteria termCriteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS, 30, 0.1);
		//提取亚像素角点
		cv::cornerSubPix(proImage, tmpPoint, cvSize(11,11), cvSize(-1,-1), cv::TermCriteria(cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 30, 0.1 ));
		imagePoints.push_back(tmpPoint);
		qDebug("%d: SubPix (%f,%f)",i,tmpPoint[0].x,tmpPoint[0].y);
//		qDebug() << tmpPoint.size();

		//显示
		cv::drawChessboardCorners(proImage,cv::Size(m_cabOption.w,m_cabOption.h),tmpPoint,true);
		cv::resize(proImage,proImage,cv::Size(320,240),0,0,cv::INTER_LINEAR);
		QImage viewTemp(proImage.data,proImage.cols,proImage.rows,QImage::Format_Indexed8);
		this->ui->imageLabel->setPixmap(QPixmap::fromImage(viewTemp));

	}

	//固定fx/fy的比值，只将fy作为可变量，进行优化计算
	if(ui->aspectRatioCheckBox->isChecked()){
		flags |= cv::CALIB_FIX_ASPECT_RATIO;
	}
	//切向畸变系数（P1，P2）被设置为零并保持为零
	if(ui->zeroTangentCheckBox){
		flags |= cv::CALIB_ZERO_TANGENT_DIST;
	}
	//在进行优化时会固定光轴点，光轴点将保持为图像的中心点
	if(ui->principalPointCheckBox){
		flags |= cv::CALIB_FIX_PRINCIPAL_POINT;
	}


	cameraMatrix = cv::Mat::eye(3,3,CV_64F);
	if(flags & cv::CALIB_FIX_ASPECT_RATIO){
		cameraMatrix.at<double>(0,0) = m_cabOption.aspectRatio;
	}

	distCoeffs = cv::Mat::zeros(8,1,CV_64F);

	//找世界坐标中的点
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

		return:			重投影的总的均方根误差
	*/
	double rms = calibrateCamera(objectPoints, imagePoints, m_saveImageAll[0].size(),
			cameraMatrix,distCoeffs, rvecs, tvecs, flags|cv::CALIB_FIX_K4|cv::CALIB_FIX_K5);
						///*|CALIB_FIX_K3*/|CALIB_FIX_K4|CALIB_FIX_K5);
	qDebug("RMS error reported by calibrateCamera: %g\n", rms);

	bool ok = cv::checkRange(cameraMatrix) && cv::checkRange(distCoeffs);

	m_cabRet.totalAvgErr = computeReprojectionErrors(objectPoints,imagePoints,rvecs,tvecs,
											cameraMatrix,distCoeffs,m_cabRet.reprojErrs);
	saveCameraParams();

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

//计算重投影误差
double operationCalibration::computeReprojectionErrors(
		const std::vector<std::vector<cv::Point3f> >& objectPoints,
		const std::vector<std::vector<cv::Point2f> >& imagePoints,
		const std::vector<cv::Mat>& rvecs, const std::vector<cv::Mat>& tvecs,
		const cv::Mat& cameraMatrix, const cv::Mat& distCoeffs,
		std::vector<float>& perViewErrors )
{
	std::vector<cv::Point2f> imagePoints2;
	int i, totalPoints = 0;
	double totalErr = 0, err;
	perViewErrors.resize(objectPoints.size());

	for( i = 0; i < (int)objectPoints.size(); i++ )
	{
		cv::projectPoints(cv::Mat(objectPoints[i]), rvecs[i], tvecs[i],
					  cameraMatrix, distCoeffs, imagePoints2);
		err = cv::norm(cv::Mat(imagePoints[i]), cv::Mat(imagePoints2), cv::NORM_L2);
		int n = (int)objectPoints[i].size();
		perViewErrors[i] = (float)std::sqrt(err*err/n);
		totalErr += err*err;
		totalPoints += n;
	}

	return std::sqrt(totalErr/totalPoints);
}

void operationCalibration::saveCameraParams(){
	QDateTime time = QDateTime::currentDateTime();
	QString timeStr = time.toString("yyyy-MM-dd hh:mm:ss dddd");
	qDebug() << "current time" << timeStr;

	if(!rvecs.empty() || !tvecs.empty())
		qDebug() << "nframes" << (int)std::max(rvecs.size(), m_cabRet.reprojErrs.size());
	qDebug() << "image_width" << m_saveImageAll[0].cols;
	qDebug() << "image_height" << m_saveImageAll[0].rows;
	qDebug() << "board_width" << m_cabOption.w;
	qDebug() << "board_height" << m_cabOption.h;
	qDebug() << "square_size" << m_cabOption.squareSize;
	if( flags & cv::CALIB_FIX_ASPECT_RATIO )
			qDebug() << "aspectRatio" << m_cabOption.aspectRatio;

	if( flags != 0 ){
		qDebug( "flags: %s%s%s%s",
				flags & cv::CALIB_USE_INTRINSIC_GUESS ? "+use_intrinsic_guess" : "",
				flags & cv::CALIB_FIX_ASPECT_RATIO ? "+fix_aspectRatio" : "",
				flags & cv::CALIB_FIX_PRINCIPAL_POINT ? "+fix_principal_point" : "",
				flags & cv::CALIB_ZERO_TANGENT_DIST ? "+zero_tangent_dist" : "" );
				//cvWriteComment( *fs, buf, 0 );
		}
	qDebug() << "flags" << flags;
//	qDebug() << "camera_matrix" << cameraMatrix;
//	qDebug() << "distortion_coefficients" << distCoeffs;

//	qDebug() << "avg_reprojection_error" << m_cabRet.totalAvgErr;
//	if( !m_cabRet.reprojErrs.empty() )
//		qDebug() << "per_view_reprojection_errors" << cv::Mat(m_cabRet.reprojErrs);

}
