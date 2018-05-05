#include "loadmat.h"


loadMat::loadMat()
{

}

bool loadMat::load(QString path){

	root_j_s = "";
	cam_matrix = cv::Mat::eye(3,3,CV_64F);
	distortion_coeff   = cv::Mat::zeros(8,1,CV_64F);

	if(path == NULL){
		qDebug() << "click cancel";
		return false;
	}

	QFile file(path);
	if(!file.open(QIODevice::ReadOnly)){
		return false;
	}
	QTextStream in(&file);
	while(!in.atEnd()){
	root_j_s += in.readLine();
	}
//	qDebug() << root_j_s;
	__parseMatrix(root_j_s,"cameraMater",cam_matrix);
	__parseMatrix(root_j_s,"disCoeffs",distortion_coeff);


	file.close();
}

void loadMat::__parseMatrix(QString& str,QString matName,cv::Mat& srcMat){
	QJsonParseError jsonError;
	QJsonDocument root_j_d = QJsonDocument::fromJson(QByteArray(str.toStdString().c_str()), &jsonError);
	if(!root_j_d.isNull() && (jsonError.error == QJsonParseError::NoError ) ){
		if(root_j_d.isObject()){
			QJsonObject root_j = root_j_d.object();
			if(root_j.contains(matName) && root_j.value(matName).isObject()){
				QJsonObject matObj = root_j.value(matName).toObject();
				QJsonArray matMat = matObj.value("mat").toArray();
				QString MatInfo_s = matObj.value("matInfo").toString();
				int rows = MatInfo_s.section('*',0,0).toInt();
				int cols = MatInfo_s.section('*',1,1).toInt();


				if(matMat.size() != (rows*cols)){return;}
				for(int i = 0;i < rows;i++){
					for(int j = 0;j < cols;j++){
						srcMat.at<double>(cv::Point(j,i)) = matMat.at(i*cols+j).toDouble();
					}
				}
				QString tmp;
				qDebug() << printMat(srcMat,tmp);
			}
		}
	}
}

QString& loadMat::printMat(const cv::Mat &srcMat,QString &str){
	str = "";


	if(srcMat.type() == CV_64F || srcMat.type() == (CV_64F + CV_USRTYPE1)){

		str+="[";
		for(int i = 0;i < srcMat.rows;i++){
			for(int j = 0;j < srcMat.cols;j++){
				str+=QString::number(srcMat.at<double>(i,j));
				str+=",";
			}
			str+="\r\n";
		}
		str+="]";
	}//end if

	if(srcMat.type() == CV_32F){

		str+="[";
		for(int i = 0;i < srcMat.rows;i++){
			for(int j = 0;j < srcMat.cols;j++){
				str+=QString::number(srcMat.at<float>(i,j));
				str+=",";
			}
			str+="\r\n";
		}
		str+="]";
	}//end if

return str;
}
