#ifndef CPUSURFFEATUREMATCHER_H
#define CPUSURFFEATUREMATCHER_H

#include <SFM/featureMatcher/IFeatureMatcher.h>
#include <opencv2/opencv.hpp>
#include <nonfree.hpp>
#include <SFM/featureMatcher/sfm_config.h>
#include <SFM/featureMatcher/FindCameraMatrices.h>
#include <QDebug>
#include <vector>

using namespace cv::xfeatures2d;
using namespace cv;

class CPUSURFFeatureMatcher:public IFeatureMatcher
{
public:
	CPUSURFFeatureMatcher(std::vector<cv::Mat>& imgs,
						  std::vector<std::vector<cv::KeyPoint> >& imgpts);
	//func
	void MatchFeatures(int idx_i, int idx_j, std::vector<cv::DMatch>* matches = NULL);
	std::vector<cv::KeyPoint> GetImagePoints(int idx) { return imgpts[idx]; }

	//data
	int minHessian;
	std::vector<cv::Mat> descriptors;

	std::vector<cv::Mat>& imgs;
	std::vector<std::vector<cv::KeyPoint> >& imgpts;

	Ptr<SurfFeatureDetector> detector;

};

#endif // CPUSURFFEATUREMATCHER_H
