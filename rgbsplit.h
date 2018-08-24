#pragma once

#include "filter.h"
#include <vector>
#include <opencv2/opencv.hpp>

class RGBSplitFilter : public Filter {
public:
	RGBSplitFilter() {}
	virtual bool IsApplicable() const override;
	virtual bool Apply() override;
	virtual void AddImage(cv::Mat image) override { this->image = image; }
	std::vector<cv::Mat> GetResults() const{ return results; }
private:
	cv::Mat image;
	std::vector<cv::Mat> results;
};
