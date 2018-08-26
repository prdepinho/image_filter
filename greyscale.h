#pragma once

#include "filter.h"
#include <opencv2/opencv.hpp>

class GreyscaleFilter : public Filter {
public:
	virtual bool IsApplicable() const override;
	virtual bool Apply() override;
	virtual void SetImage(cv::Mat image) override { this->image = image; }
	virtual void SetFileName(std::string name) override { this->name = name; }

	virtual std::string GetFlag() override { return "-grey"; }
	virtual std::string GetFilterName() const override { return "Greyscale"; }
	virtual std::vector<std::string> GetParameterNames() const { return {}; }
	virtual void SetParameters(std::vector<std::string> arguments) override {};
	virtual void Output() override;
private:
	std::string name;
	cv::Mat image;
	cv::Mat result;
};

