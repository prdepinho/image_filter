
#include "rgbsplit.h"

// The image has to have at least three channels.
bool RGBSplitFilter::IsApplicable() const {
	switch(image.type()){
		case CV_8UC3: case CV_8UC4:
			return true;
	}
	return false;
}

bool RGBSplitFilter::Apply() {
	cv::Mat red = image.clone();
	cv::Mat green = image.clone();
	cv::Mat blue = image.clone();

	for(int i = 0; i < image.rows; i++){
		for(int j = 0; j < image.cols; j++){
			cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);

			red.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, pixel[2]);
			green.at<cv::Vec3b>(i, j) = cv::Vec3b(0, pixel[1], 0);
			blue.at<cv::Vec3b>(i, j) = cv::Vec3b(pixel[0], 0, 0);
		}
	}
	results = std::vector<cv::Mat>();
	results.push_back(red);
	results.push_back(green);
	results.push_back(blue);
	return true;
}

void RGBSplitFilter::Output(){
	cv::imwrite(("red_"   + name).c_str(), results[0]);
	cv::imwrite(("green_" + name).c_str(), results[1]);
	cv::imwrite(("blue_"  + name).c_str(), results[2]);
}
