#include "sfmwindow.h"
#include "ui_sfmwindow.h"

SFMWindow::SFMWindow(QWidget *parent) :
	QDialog(parent),loadMat(),
	ui(new Ui::SFMWindow)
{
	ui->setupUi(this);
	initInterface();
}

SFMWindow::~SFMWindow()
{
	delete ui;
}

void SFMWindow::setSelectFeatureDetector(){
	ui->selectFeatureComboBox->addItem("SURF");
	ui->selectFeatureComboBox->addItem("SILT");
}

void SFMWindow::closeEvent(QCloseEvent * event){
	emit clickX();
}

void SFMWindow::initInterface(){
	setSaveImageNumberLabel(0);
	setSelectFeatureDetector();
}

void SFMWindow::on_openImglPushButton_clicked(){
	QString fileName = QFileDialog::getOpenFileName(this,tr("save image"),"",tr("(*.imgl)"));
	if(fileName == NULL){
		qDebug() << "click cancel";
		return ;
	}

	QFile imglFile;
	imglFile.setFileName(fileName);
	if(!imglFile.open(QIODevice::ReadOnly|QIODevice::Text)){
		qDebug()<<"打开失败";
		return ;
	}

	QString rootString = imglFile.readAll();

	cJSON * root_j = cJSON_Parse(rootString.toStdString().c_str());


	cJSON * image_n_j = cJSON_GetObjectItem(root_j,IMAGE_NUMBER);
	int image_n = image_n_j->valueint;

	cJSON * image_path_j = cJSON_GetObjectItem(root_j,IMAGE_PATH);
	if(image_n != cJSON_GetArraySize(image_path_j)){
		qDebug() << "format error";
		cJSON_Delete(root_j);
		imglFile.close();
		return ;
	}

	m_saveImageAll.clear();

	for(int i = 0;i < image_n;i++){
		cJSON * tmpPath_j = cJSON_GetArrayItem(image_path_j,i);
		QString tmpPath = tmpPath_j->valuestring;
		cv::Mat tmpImage = cv::imread(tmpPath.toStdString());
		m_saveImageAll.push_back(tmpImage);
	}

	saveNumber = image_n;
	setSaveImageNumberLabel(saveNumber);


	cJSON_Delete(root_j);
	imglFile.close();
}

void SFMWindow::on_loadCamMatPushButton_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("load camMat \"K\" "),"",tr("(*.m)"));
	load(fileName);

}

void SFMWindow::setSaveImageNumberLabel(int number){
	this->ui->saveImageNumberLabel->setText(QString("") + QChar(0xf03e) + QString(" ") + QString::number(number,10));
	if(number > 0){
		this->ui->startPushButton->setEnabled(true);
	}else if(number ==0 || number < 0){
		this->ui->startPushButton->setDisabled(true);
	}
}

void SFMWindow::selectFeatureDetector(){
	detectorType = ui->selectFeatureComboBox->currentText();
	qDebug() << detectorType;
}

void SFMWindow::on_startPushButton_clicked(){
	selectFeatureDetector();

	qDebug() << m_saveImageAll.size();
	cv::cvtColor(m_saveImageAll[0],m_saveImageAll[0],cv::COLOR_BGR2GRAY);
	cv::cvtColor(m_saveImageAll[1],m_saveImageAll[1],cv::COLOR_BGR2GRAY);

	if(!detectorType.compare("SURF")){
//		CPUSURFFeatureMatcher csfm(m_saveImageAll,imgpts);
//		qDebug() << "imgpts.size() -> " << imgpts.size();
//		std::vector<cv::DMatch> testMatch;
//		csfm.MatchFeatures(2,3,&testMatch);


	}//end if "SURF"

}

QString printMat(cv::Mat srcMat){
	QString matVal_s;

	matVal_s+=QString::number(srcMat.rows)+"x"+QString::number(srcMat.cols);
	matVal_s+="\n";
	matVal_s+="[";
	for(int i = 0;i < srcMat.rows;i++){
		for(int j = 0;j < srcMat.cols;j++){
			matVal_s+=QString::number(srcMat.at<double>(i,j));
			matVal_s+=",";
		}
			matVal_s+="\n";
	}
	matVal_s+="]";
	qDebug() << matVal_s;
}


