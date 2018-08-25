#pragma once

#include "rgbsplit.h"
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

class RGBSplitFilterView : public FilterView{
public:
	RGBSplitFilterView(RGBSplitFilter *filter = nullptr, std::string flag = "-rgb") 
		: FilterView(flag), filter(filter) {}
	virtual void ProcessArgs(std::vector<std::string> arguments);
	virtual int ProcessInput();
	virtual void Output();
private:
	RGBSplitFilter *filter;
};
