
#include "rgbsplit_view.h"

void RGBSplitFilterView::ProcessArgs(std::vector<std::string> arguments){
}

int RGBSplitFilterView::ProcessInput(){
	return 0;
}

void RGBSplitFilterView::Output(){
	std::vector<cv::Mat> results = filter->GetResults();
	cv::imwrite(("red_"   + filter->GetName()).c_str(), results[0]);
	cv::imwrite(("green_" + filter->GetName()).c_str(), results[1]);
	cv::imwrite(("blue_"  + filter->GetName()).c_str(), results[2]);
}
