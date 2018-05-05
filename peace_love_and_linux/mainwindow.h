#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//qt
#include <QMainWindow>
#include <QDebug>
//self
#include "calibration/calibrationwindow.h"
#include "AR/operationar.h"
#include "SFM/sfmwindow.h"
//3rd

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_calibrationPushButton_clicked();
	void showMainWindow();

	void on_ARPushButton_clicked();

	void on_SFMPushButton_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
