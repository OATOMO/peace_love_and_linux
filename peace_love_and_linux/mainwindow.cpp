#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setWindowTitle(QString("peace love and linux  ") + QChar(0xf17c));
	this->ui->calibrationPushButton->setText(QString("calibraton ") + QChar(0xf2de));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_calibrationPushButton_clicked()
{
	calibrationWindow * calWin = new calibrationWindow(this);

	connect(calWin,SIGNAL(clickX()),this,SLOT(showMainWindow()));
	this->hide();
	calWin->show();
}

void MainWindow::showMainWindow(){
	this->show();
}
