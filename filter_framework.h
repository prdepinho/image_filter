#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "filter.h"

class FilterFramework {
public:
	int Execute(int argc, char **argv);
	void SetFilters(std::vector<Filter*> filters) { this->filters = filters; }
private:
	bool ProcessArgs(int argc, char **argv);
	void SetImageToFilters();
	void ProcessInteraction();
	void ExecuteFilter(Filter *filter);
	inline void ShowType(cv::Mat image);

	std::string filename;
	std::vector<std::string> arguments;
	std::vector<Filter*> filters;
	Filter *selected_filter = nullptr;
};

