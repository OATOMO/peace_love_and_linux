#include "cpusurffeaturematcher.h"


CPUSURFFeatureMatcher::CPUSURFFeatureMatcher(std::vector<cv::Mat> &imgs,
						std::vector<std::vector<cv::KeyPoint> > &imgpts):
imgpts(imgpts), imgs(imgs)
{
	minHessian = 100;
	Ptr<SurfFeatureDetector> detector = SurfFeatureDetector::create(minHessian);
	detector->detect(imgs,imgpts);
	detector->compute(imgs,imgpts,descriptors);
}


/*
 * DMatch :
 * 	@int queryIdx;  	query描述子的索引
 * 	@int trainIdx;  	train描述子的索引
 *  @int imgIdx;
 *  @float distance;	distance为两个描述子之间的距离
*/

void CPUSURFFeatureMatcher::MatchFeatures(int idx_i, int idx_j,
						std::vector<cv::DMatch>* matches)
{
#ifdef __SFM__DEBUG__
	const cv::Mat& img_1 = imgs[idx_i];
	const cv::Mat& img_2 = imgs[idx_j];
#endif
	const std::vector<cv::KeyPoint>& imgpts1 = imgpts[idx_i];
	const std::vector<cv::KeyPoint>& imgpts2 = imgpts[idx_j];
	const cv::Mat& descriptors_1 = descriptors[idx_i];
	const cv::Mat& descriptors_2 = descriptors[idx_j];

	std::vector<cv::DMatch> good_matches_,very_good_matches_;
	std::vector<cv::KeyPoint> keypoints_1,keypoints_2;

	qDebug()  << "imgpts1 has " << imgpts1.size() << " points (descriptors " << descriptors_1.rows << ")" ;
	qDebug() << "imgpts2 has " << imgpts2.size() << " points (descriptors " << descriptors_2.rows << ")" ;

	keypoints_1 = imgpts1;
	keypoints_2 = imgpts2;

	if(descriptors_1.empty()) {
			CV_Error(0,"descriptors_1 is empty");
	}
	if(descriptors_2.empty()) {
			CV_Error(0,"descriptors_2 is empty");
	}

	//matching descriptor vectors using Brute Force matcher
//	cv::BFMatcher matcher(cv::NORM_HAMMING);	//allow cross-check. use Hamming distance for binary descriptor (ORB)
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");//这里填写使用的匹配方式

	std::vector< cv::DMatch > matches_;
	if (matches == NULL) {
			matches = &matches_;
	}
	if (matches->size() == 0) {
			matcher->match(descriptors_1, descriptors_2, *matches);
//			matcher.match( descriptors_1, descriptors_2, *matches );
	}

	assert(matches->size() > 0);

	std::vector<KeyPoint> imgpts1_good,imgpts2_good;

	std::set<int> existing_trainIdx;
	for(unsigned int i = 0; i < matches->size(); i++ ){
		//"normalize" matching: somtimes imgIdx is the one holding the trainIdx
		if ((*matches)[i].trainIdx <= 0) {
			(*matches)[i].trainIdx = (*matches)[i].imgIdx;
		}

		if( existing_trainIdx.find((*matches)[i].trainIdx) == existing_trainIdx.end() &&
			(*matches)[i].trainIdx >= 0 && (*matches)[i].trainIdx < (int)(keypoints_2.size()) /*&&
			(*matches)[i].distance > 0.0 && (*matches)[i].distance < cutoff*/ ){
			good_matches_.push_back( (*matches)[i]);
			imgpts1_good.push_back(keypoints_1[(*matches)[i].queryIdx]);
			imgpts2_good.push_back(keypoints_2[(*matches)[i].trainIdx]);
			existing_trainIdx.insert((*matches)[i].trainIdx);
		}
	}

#ifdef __SFM__DEBUG__
	qDebug() << "keypoints_1.size() " << keypoints_1.size() << " imgpts1_good.size() " << imgpts1_good.size();
	qDebug() << "keypoints_2.size() " << keypoints_2.size() << " imgpts2_good.size() " << imgpts2_good.size();

	{
		//-- Draw only "good" matches
		Mat img_matches;
		drawMatches( img_1, keypoints_1, img_2, keypoints_2,
					good_matches_, img_matches, Scalar::all(-1), Scalar::all(-1),
					std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
		//-- Show detected matches
		std::stringstream ss;ss << "Feature Matches " << idx_i << "-" << idx_j;
		imshow(ss.str() , img_matches );
		waitKey(0);
		destroyWindow(ss.str());
	}
#endif

	std::vector<uchar> status;
	std::vector<KeyPoint> imgpts2_very_good,imgpts1_very_good;

	assert(imgpts1_good.size() > 0);
	assert(imgpts2_good.size() > 0);
	assert(good_matches_.size() > 0);
	assert(imgpts1_good.size() == imgpts2_good.size() && imgpts1_good.size() == good_matches_.size());

	//Select features that make epipolar sense
	GetFundamentalMat(keypoints_1,keypoints_2,imgpts1_very_good,imgpts2_very_good,good_matches_);

	//Draw matches
#ifdef __SFM__DEBUG__
	{
		//-- Draw only "good" matches
		Mat img_matches;
		drawMatches( img_1, keypoints_1, img_2, keypoints_2,
					good_matches_, img_matches, Scalar::all(-1), Scalar::all(-1),
					std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
		//-- Show detected matches
		imshow( "Good Matches", img_matches );
		waitKey(0);
		destroyWindow("Good Matches");
	}
#endif

}
