
#include "rgbsplit_view.h"

void RGBSplitFilterView::ProcessArgs(std::vector<std::string> arguments){
}

int RGBSplitFilterView::ProcessInput(){
	return 0;
}

void RGBSplitFilterView::Output(){
	std::vector<cv::Mat> results = filter->GetResults();
	cv::imwrite("red_lena.png", results[0]);
	cv::imwrite("green_lena.png", results[1]);
	cv::imwrite("blue_lena.png", results[2]);
}
