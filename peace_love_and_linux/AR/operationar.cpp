#include "operationar.h"
#include "ui_operationar.h"

operationAR::operationAR(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::operationAR)
{
	ui->setupUi(this);
	root_j_s="";
}

operationAR::~operationAR()
{
	delete ui;
}

void operationAR::closeEvent(QCloseEvent * event){
	emit clickX();
}

void operationAR::on_loadCamMatPushButton_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("load camMat"),"","");
	if(fileName == NULL){
		qDebug() << "not select file";
		return ;
	}
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly)){
		return;
	}
	QTextStream in(&file);
	while(!in.atEnd()){
	root_j_s += in.readLine();
	}
	qDebug() << root_j_s;
	file.close();
}
