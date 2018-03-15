#ifndef OPERATIONAR_H
#define OPERATIONAR_H

#include <QDialog>
#include <QString>
#include <QMetaType>
#include <QSharedMemory>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QTextStream>

namespace Ui {
	class operationAR;
}

class operationAR : public QDialog
{
	Q_OBJECT

public:
	explicit operationAR(QWidget *parent = 0);
	~operationAR();
	void closeEvent(QCloseEvent * event);
	//data
	QString root_j_s;
	//fun

signals:
	void clickX();
private slots:
	void on_loadCamMatPushButton_clicked();

private:
	Ui::operationAR *ui;
};

#endif // OPERATIONAR_H
