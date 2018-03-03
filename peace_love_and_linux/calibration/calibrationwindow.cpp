#include "calibrationwindow.h"
#include "ui_calibrationwindow.h"

calibrationWindow::calibrationWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::calibrationWindow)
{
	ui->setupUi(this);
	setSelfFont();
	qRegisterMetaType< cv::Mat >("cv::Mat"); 	//注册信号槽元类型
	qRegisterMetaType< cv::Mat >("cv::Mat&");	//注册信号槽元类型
	//get init info
	getInitInfo();
	//init interface
	initInterface();							//初始化界面
}

calibrationWindow::~calibrationWindow()
{
	delete ui;
}

void calibrationWindow::closeEvent(QCloseEvent * event){
	emit clickX();
}

#define TTF_FILE ":/FONT/FONT/fontawesome-webfont.ttf"
void calibrationWindow::setSelfFont(){
	int fontId = QFontDatabase::addApplicationFont(TTF_FILE);
	QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
	this->setFont(QFont(fontName));
}

void calibrationWindow::initData(){
	info_D.cJsonRoot = "";
	cJSON * root = cJSON_CreateObject();
	info_D.cJsonRoot = QString(cJSON_Print(root));
	cJSON_Delete(root);
}

u_int8_t calibrationWindow::getVideoNumber(){
	int videoNum = 0;
	QString path = "/dev";
	DIR * dp;
	struct dirent *entry;
	struct stat statbuf;

	if((dp = opendir(path.toStdString().c_str())) == NULL){
		qDebug() << "cannot open directory " << path;
		return -1;
	}
	chdir(path.toStdString().c_str());
	while((entry = readdir(dp)) != NULL){
		lstat(entry->d_name,&statbuf);
		if(S_ISCHR (statbuf.st_mode)){
//			qDebug() << entry->d_name;
			int i;
			if( QString(entry->d_name).contains("video")  ){
//				qDebug() << entry->d_name;
				//add json video*
				cJSON * root = cJSON_Parse(info_D.cJsonRoot.toStdString().c_str());
				cJSON_AddItemToObject(root,QString(entry->d_name).toStdString().c_str(),cJSON_CreateObject());
				info_D.cJsonRoot = QString(cJSON_Print(root));
				cJSON_Delete(root);
				//
				videoNum++;
			 }

		  }
	}

	info_D.videoNumber = videoNum;

return videoNum;
}

void calibrationWindow::__getVideoProperty(QString devName){
	int fb = ::open(devName.toStdString().c_str(),O_RDWR);
	if(fb < 0){
		qDebug() << "open " << devName << " failed T~T ..";
		exit(-1);
	}

	enum v4l2_buf_type m_type = V4L2_BUF_TYPE_VIDEO_CAPTURE;;
	struct v4l2_fmtdesc fmt;
	struct v4l2_frmsizeenum frmSize;

	memset(&fmt,0,sizeof(fmt));
	fmt.index = 0;
	fmt.type = m_type;
	while ((ioctl(fb, VIDIOC_ENUM_FMT, &fmt)) == 0){
		frmSize.pixel_format = fmt.pixelformat;
		frmSize.index = 0;

		QString typeFmt;
		typeFmt.sprintf("%c%c%c%c",(fmt.pixelformat & 0xFF),
				((fmt.pixelformat >> 8) & 0xFF),((fmt.pixelformat >> 16) & 0xFF),
				((fmt.pixelformat >> 24) & 0xFF));

		cJSON * root = cJSON_Parse(info_D.cJsonRoot.toStdString().c_str());
		cJSON * fmtNode = cJSON_CreateArray();

		while(ioctl(fb,VIDIOC_ENUM_FRAMESIZES,&frmSize) == 0){
			if(frmSize.type == V4L2_FRMSIZE_TYPE_DISCRETE){
//				qDebug() << "discrete " << frmSize.discrete.width << frmSize.discrete.height;
				QString tempFmtSize;
				tempFmtSize.sprintf("%dx%d",frmSize.discrete.width,frmSize.discrete.height);
				cJSON_AddItemToArray(fmtNode,cJSON_CreateString(tempFmtSize.toStdString().c_str()));
			}
			else if(frmSize.type == V4L2_FRMSIZE_TYPE_STEPWISE){
//				qDebug() << "stepwise " << frmSize.stepwise.max_width << frmSize.stepwise.max_height;
			}
			frmSize.index++;
		}
//		qDebug("{ pixelformat = '%c%c%c%c', description = '%s' }\n",fmt.pixelformat & 0xFF,
//			(fmt.pixelformat >> 8) & 0xFF,(fmt.pixelformat >> 16) & 0xFF,
//			(fmt.pixelformat >> 24) & 0xFF,fmt.description);
		cJSON_AddItemToObject(cJSON_GetObjectItem(root,devName.section('/',2,2).toStdString().c_str()),
							  typeFmt.toStdString().c_str(),fmtNode);
		info_D.cJsonRoot = QString(cJSON_Print(root));
		cJSON_Delete(root);
		fmt.index++;

	 }
}

void calibrationWindow::getVideoProperty(){
	for(int i = 0; i < info_D.videoNumber;i++ ){
		__getVideoProperty(QString("/dev/video")+QString::number(i,10));
	}
}

void calibrationWindow::getInitInfo(){
	initData();
	getVideoNumber();
	getVideoProperty();

	qDebug() << info_D.cJsonRoot;
}

void calibrationWindow::initInterface(){
	//init video* dev
	for(int i = 0; i < info_D.videoNumber;i++ ){
		ui->selectVideoComboBox->addItem(
		QString("video")+QString::number(i,10));
	}
	//init FMT for video*
//    cJSON * root = cJSON_Parse(info_D.cJsonRoot.toStdString().c_str());
//    for(int i = 0; i < info_D.videoNumber;i++ ){
//        QString videoName_T = (QString("video")+QString::number(i,10));
//        cJSON * videoX = cJSON_GetObjectItem(root,videoName_T.toStdString().c_str());
//        cJSON * MJPG_FMT = cJSON_GetObjectItem(videoX,"MJPG");
//        int FMT_Number = cJSON_GetArraySize(MJPG_FMT);
//        for(int j = 0;j < FMT_Number;j++){

//        }
//    }
	if(info_D.videoNumber > 0){
		QString currentVideoX = ui->selectVideoComboBox->currentText();
		cJSON * root = cJSON_Parse(info_D.cJsonRoot.toStdString().c_str());
		cJSON * videoX = cJSON_GetObjectItem(root,currentVideoX.toStdString().c_str());
		cJSON * MJPG_FMT = cJSON_GetObjectItem(videoX,"MJPG");
		int FMT_Number = cJSON_GetArraySize(MJPG_FMT);
		for(int j = 0;j < FMT_Number;j++){
			cJSON * fmtItem = cJSON_GetArrayItem(MJPG_FMT,j);
			QString tempFMTSize = fmtItem->valuestring;
			ui->selectFMTComboBox->addItem(tempFMTSize);
		}
	}

	info_D.currVideoX = ui->selectVideoComboBox->currentText();
	info_D.currWidth = (ui->selectFMTComboBox->currentText()).section('x',0,0).toInt();
	info_D.currHieght = (ui->selectFMTComboBox->currentText()).section('x',1,1).toInt();

	this->ui->startPushButton->setText(QString("start ") + QChar(0xf0da));
	setSaveImageNumberLabel(0);
	this->ui->capturePushButton->setText(QString("capture ") + QChar(0xf1c5));
	this->ui->resetPushButton->setText(QString("reset ") + QChar(0xf2a3));
	this->ui->lookoverPushButton->setText(QString("") + QChar(0xf262) + QString(" ") + QChar(0xf03e));
	this->ui->capturePushButton->setDisabled(true);
}

void calibrationWindow::grapGetVideo(cv::Mat & srcImage){
	srcImage.copyTo(m_srcImage);
	cv::Mat tmpImage;
	cv::cvtColor(srcImage,tmpImage,CV_BGR2RGB);

	cv::resize(tmpImage,tmpImage,cv::Size(ui->imageLabel->width(),ui->imageLabel->height()),
			   0,0,cv::INTER_LINEAR);
	QImage viewTemp(tmpImage.data,tmpImage.cols,tmpImage.rows,QImage::Format_RGB888);

	ui->imageLabel->setPixmap(QPixmap::fromImage(viewTemp));


}

#define M_SHAREDKEY "ATOM_shared_mem"
void calibrationWindow::on_startPushButton_clicked()
{
	if(info_D.currVideoX.isNull()){
		QMessageBox::about(this,tr("warning"),tr("No video"));
		return ;
	}

	if( (0 == this->ui->startPushButton->text().indexOf("start")) ){
		this->ui->startPushButton->setText(QString("stop ") + QChar(0xf0c8));
		//start video thread
		capThread = new videoCapture(info_D.currVideoX.remove("video").toInt(),
									 cv::Size2i(info_D.currWidth,info_D.currHieght));
		connect(capThread,SIGNAL(videoShow(cv::Mat &)),this,SLOT(grapGetVideo(cv::Mat &)));
		capThread->start();
		this->ui->capturePushButton->setEnabled(true);
		this->ui->resetPushButton->setDisabled(true);
		this->ui->selectVideoComboBox->setDisabled(true);
		this->ui->selectFMTComboBox->setDisabled(true);
		this->ui->lookoverPushButton->setDisabled(true);

	}else if((0 == this->ui->startPushButton->text().indexOf("stop"))){
		this->ui->startPushButton->setText(QString("start ") + QChar(0xf0da));
		//stop video thread
		capThread->quit();
		disconnect(capThread,0,0,0);
		delete capThread;
		this->ui->capturePushButton->setDisabled(true);
		this->ui->resetPushButton->setEnabled(true);
		this->ui->selectVideoComboBox->setEnabled(true);
		this->ui->selectFMTComboBox->setEnabled(true);
		this->ui->lookoverPushButton->setEnabled(true);
	}


}

void calibrationWindow::on_selectFMTComboBox_activated(const QString &arg1)
{
	info_D.currWidth = (ui->selectFMTComboBox->currentText()).section('x',0,0).toInt();
	info_D.currHieght = (ui->selectFMTComboBox->currentText()).section('x',1,1).toInt();

	qDebug("%dx%d\n",info_D.currWidth,info_D.currHieght);

}

void calibrationWindow::on_selectVideoComboBox_activated(const QString &arg1)
{
	info_D.currVideoX = arg1;
	qDebug("current video -> %s",info_D.currVideoX.toStdString().c_str());

	ui->selectFMTComboBox->clear();
	QString currentVideoX =	arg1;
	cJSON * root = cJSON_Parse(info_D.cJsonRoot.toStdString().c_str());
	cJSON * videoX = cJSON_GetObjectItem(root,currentVideoX.toStdString().c_str());
	cJSON * MJPG_FMT = cJSON_GetObjectItem(videoX,"MJPG");
	int FMT_Number = cJSON_GetArraySize(MJPG_FMT);
	for(int j = 0;j < FMT_Number;j++){
		cJSON * fmtItem = cJSON_GetArrayItem(MJPG_FMT,j);
		QString tempFMTSize = fmtItem->valuestring;
		ui->selectFMTComboBox->addItem(tempFMTSize);
	}

}

void calibrationWindow::on_capturePushButton_clicked(){
//	qDebug() << "capture";
	cv::Mat tmp;
	m_srcImage.copyTo(tmp);
	m_saveImageAll.push_back(tmp);
	saveNumber++;
	setSaveImageNumberLabel(saveNumber);
//	qDebug() << "m_saveImage size" << m_saveImageAll.size();
}



void calibrationWindow::setSaveImageNumberLabel(int number){
	this->ui->saveImageNumberLabel->setText(QString("") + QChar(0xf03e) + QString(" ") + QString::number(number,10));
}


void calibrationWindow::on_resetPushButton_clicked(){
	m_saveImageAll.clear();
	saveNumber = 0;
	setSaveImageNumberLabel(saveNumber);
	qDebug() << "m_saveImage size" << m_saveImageAll.size();
}

void calibrationWindow::channgeImageN(void){
	saveNumber = m_saveImageAll.size();
	setSaveImageNumberLabel(saveNumber);
	qDebug() << "m_saveImageAll.size()" << m_saveImageAll.size();
}

void calibrationWindow::on_lookoverPushButton_clicked(){
	if(m_saveImageAll.size() > 0){
		lookoverImage * loWindow = new lookoverImage(&m_saveImageAll,this);
		connect(loWindow,SIGNAL(channgeImageN()),this,SLOT(channgeImageN()));
		loWindow->show();
	}else{
		QMessageBox::about(this,tr("warning"),tr("No pictures"));
	}
}





void calibrationWindow::on_openImglPushButton_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("save image"),"",tr("(*.imgl)"));
	QFile imglFile;
	imglFile.setFileName(fileName);
	if(!imglFile.open(QIODevice::ReadOnly|QIODevice::Text)){
		qDebug()<<"打开失败";
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

void calibrationWindow::on_calibrationPushButton_clicked()
{
	if(m_saveImageAll.size() > 0){
		operationCalibration * operationCal = new operationCalibration(m_saveImageAll,this);
		operationCal->show();
	}else{
		QMessageBox::about(this,tr("warning"),tr("No pictures"));
	}


}
