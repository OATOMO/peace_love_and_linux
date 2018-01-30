#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//qt
#include <QMainWindow>
#include <QDebug>
//self
#include "calibration/calibrationwindow.h"

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

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
