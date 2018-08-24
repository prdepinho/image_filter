#pragma once

#include <opencv2/opencv.hpp>

class Filter {
public:
	virtual bool IsApplicable() const = 0;
	virtual bool Apply() = 0;
	virtual void AddImage(cv::Mat image) = 0;
};

