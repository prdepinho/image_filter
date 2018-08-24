#pragma once

#include "blur.h"
#include "filter_view.h"
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "filter_exception.h"

class BlurFilterView : public FilterView{
public:
	BlurFilterView(BlurFilter *filter = nullptr, std::string flag = "-blur") 
		: FilterView(flag), filter(filter) {}
	virtual void ProcessArgs(std::vector<std::string> arguments);
	virtual int ProcessInput();
	virtual void Output();
private:
	BlurFilter *filter;
};
