#pragma once

#include "filter.h"
#include <opencv2/opencv.hpp>

class BlurFilter : public Filter {
public:
	BlurFilter(int radius = 1, float weight = 1.0f) 
		: radius(radius), weight(weight) {}
	virtual bool IsApplicable() const override;
	virtual bool Apply() override;
	virtual void AddImage(cv::Mat image) override { this->image = image; }
	void SetRadius(int radius) { this->radius = radius; }
	void SetWeight(float weight) { this->weight = weight; }
	cv::Mat GetResult() const{ return result; }
private:
	std::vector<cv::Vec3b> GetNeighbors(int y, int x) const;
	int radius;
	float weight;
	cv::Mat image;
	cv::Mat result;
};
