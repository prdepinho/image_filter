#pragma once

#include "filter.h"
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

class RGBSplitFilter : public Filter, public FilterView {
public:
	RGBSplitFilter(std::string flag = "-rgb") 
		: FilterView(flag) {}
	virtual std::string GetFilterName() const override { return std::string("RGB Split"); }
	virtual bool IsApplicable() const override;
	virtual bool Apply() override;
	virtual void SetImage(cv::Mat image) override { this->image = image; }
	virtual void SetFileName(std::string name) override { this->name = name; }

	virtual void ProcessArgs(std::vector<std::string> arguments);
	virtual int ProcessInput();
	virtual void Output();

	std::string GetName() const{ return name; }
	std::vector<cv::Mat> GetResults() const{ return results; }
private:
	std::string name;
	cv::Mat image;
	std::vector<cv::Mat> results;
};

