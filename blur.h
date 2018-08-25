#pragma once

#include "filter.h"
#include <opencv2/opencv.hpp>

class BlurFilter : public Filter {
public:
	BlurFilter(int radius = 1, float weight = 1.0f) 
		: radius(radius), weight(weight) {}
	virtual std::string GetFilterName() const override { return std::string("Blur"); }
	virtual bool IsApplicable() const override;
	virtual bool Apply() override;
	virtual void SetImage(cv::Mat image) override { this->image = image; }
	virtual void SetFileName(std::string name) override { this->name = name; }
	void SetRadius(int radius) { this->radius = radius; }
	void SetWeight(float weight) { this->weight = weight; }
	std::string GetName() const{ return name; }
	cv::Mat GetResult() const{ return result; }
private:
	std::vector<uchar> GetNeighbors(cv::Mat &channel, int y, int x) const;
	std::string name;
	int radius;
	float weight;
	cv::Mat image;
	cv::Mat result;
};
