#pragma once

#include "rgbsplit.h"
#include "filter_view.h"
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "filter_exception.h"

class RGBSplitFilterView : public FilterView{
public:
	RGBSplitFilterView(RGBSplitFilter *filter = nullptr, std::string flag = "-rgb") 
		: FilterView(flag), filter(filter) {}
	virtual void ProcessArgs(int argc, char **argv);
	virtual int ProcessInput();
	virtual void Output();
private:
	RGBSplitFilter *filter;
};
