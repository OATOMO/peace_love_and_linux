#include "lookoverimage.h"
#include "ui_lookoverimage.h"

#define NUMBER (currNumber+1)

lookoverImage::lookoverImage(std::vector<cv::Mat> * m_saveImageAll,QWidget *parent) :
	QDialog(parent),
	ui(new Ui::lookoverImage),
	m_saveImageAll(m_saveImageAll)
{
	ui->setupUi(this);
	currNumber = 0;
	initInterface();
	}

lookoverImage::~lookoverImage()
{
	delete ui;
}

void lookoverImage::initIcon(){
	this->ui->beforePushButton->setText(QString("") + QChar(0xf060));
	this->ui->afterPushButton->setText(QString("") + QChar(0xf061));
	this->ui->numberLabel->setText(QString::number(NUMBER,10) +
								   QString("/") +
								   QString::number(m_saveImageAll->size(),10)+
								   QString(" ")+QChar(0xf1c5));
}


void lookoverImage::updateImage(int number){
	cv::Mat tmpImage;
	(*m_saveImageAll)[number].copyTo(tmpImage);
	cv::resize(tmpImage,tmpImage,cv::Size(320,240),0,0,cv::INTER_LINEAR);
	QImage viewTemp(tmpImage.data,tmpImage.cols,tmpImage.rows,QImage::Format_RGB888);

	this->ui->imageLabel->setPixmap(QPixmap::fromImage(viewTemp));
	this->ui->numberLabel->setText(QString::number(NUMBER,10) +
								   QString("/") +
								   QString::number(m_saveImageAll->size(),10)+
								   QString(" ")+QChar(0xf1c5));

	(currNumber >= m_saveImageAll->size()-1)?(this->ui->afterPushButton->setDisabled(true)):(this->ui->afterPushButton->setEnabled(true));
	(currNumber <= 0)?(this->ui->beforePushButton->setDisabled(true)):(this->ui->beforePushButton->setEnabled(true));
}

void lookoverImage::initInterface(){
	initIcon();
	if(m_saveImageAll->size()){
		//
		updateImage(currNumber);
	}
//	for(int i = 0;i < m_saveImageAll.size();i++){
//		qDebug() << i;
//		cv::imshow(QString::number(i).toStdString(),m_saveImageAll[i]);
//	}

}

void lookoverImage::on_beforePushButton_clicked()
{
	currNumber--;
	updateImage(currNumber);
}

void lookoverImage::on_afterPushButton_clicked()
{
	currNumber++;
	updateImage(currNumber);
}

void lookoverImage::on_delPushButton_clicked()
{
	m_saveImageAll->erase(m_saveImageAll->begin()+currNumber);
	if((currNumber) == 0 && (m_saveImageAll->size()!=0)){
		updateImage(currNumber);
	}
	else if(currNumber > 0 && (m_saveImageAll->size()!=0)){
		updateImage(--currNumber);
	}
	else if((m_saveImageAll->size()==0)){
		qDebug() << "not image";
		this->close();
	}



	emit channgeImageN();
}

void lookoverImage::on_savePushButton_clicked()
{
	QString file_path = QFileDialog::getSaveFileName(this,tr("save image"),"",tr("(*.imgl)"));
	if(file_path.isNull()){
		return ;
	}
	if(QFile::exists(file_path)){
		qDebug() << "exists";
		return ;
	}
	QFile imglFile;
	QString imglName = file_path+".imgl";
	imglFile.setFileName(imglName);
	if(!imglFile.open(QIODevice::WriteOnly|QIODevice::Text)){
		qDebug()<<"打开失败";
	}
	imglFile.write((QString::number(m_saveImageAll->size(),10) + "\r\n").toStdString().c_str());
	imglFile.write(QString::number(m_saveImageAll->size(),10).toStdString().c_str());

	for(int i = 0;i < m_saveImageAll->size();i++){
		QString imageName = file_path+QString::number(i,10)+QString(".jpg");
		cv::imwrite(imageName.toStdString(),(*m_saveImageAll)[i]);
	}

		imglFile;close();
}
