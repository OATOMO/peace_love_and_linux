#include "reprojectioncheck.h"
#include "ui_reprojectioncheck.h"

reProjectionCheck::reProjectionCheck(std::vector<cv::Mat>  m_saveImageAll,QWidget *parent) :
	m_saveImageAll(m_saveImageAll),
	QDialog(parent),
	ui(new Ui::reProjectionCheck)
{
	ui->setupUi(this);
	currNumber = 0;
	initUI();
}

reProjectionCheck::~reProjectionCheck()
{
	delete ui;
}

void reProjectionCheck::initUI(){
	updateImage(currNumber);
}

void reProjectionCheck::updateImage(int num){
	cv::Mat tempView;
	tempView = (cv::Mat)m_saveImageAll[num].clone();
	int w = ui->imageLabel->width();
	int h = ui->imageLabel->height();

	cv::resize(tempView,tempView,cv::Size(w,h),0,0,cv::INTER_LINEAR);
	QImage viewTemp(tempView.data,tempView.cols,tempView.rows,QImage::Format_RGB888);
	this->ui->imageLabel->setPixmap(QPixmap::fromImage(viewTemp));
	setNumberLabel(num);

	if(currNumber <= 0){
		ui->beforePushButton->setDisabled(true);
	}else{
		ui->beforePushButton->setEnabled(true);
	}

	if(currNumber >= m_saveImageAll.size()-1){
		ui->afterPushButton->setDisabled(true);
	}else{
		ui->afterPushButton->setEnabled(true);
	}
}

void reProjectionCheck::setNumberLabel(int num){
	int totalNum = m_saveImageAll.size();
	int currNum = num+1;
	ui->numberLabel->setText(QString::number(currNum) + "/" + QString::number(totalNum));

}

void reProjectionCheck::on_beforePushButton_clicked()
{
	currNumber--;
	updateImage(currNumber);
}

void reProjectionCheck::on_afterPushButton_clicked()
{
	currNumber++;
	updateImage(currNumber);
}
