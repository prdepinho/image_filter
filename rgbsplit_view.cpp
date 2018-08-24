
#include "rgbsplit_view.h"

void RGBSplitFilterView::ProcessArgs(int argc, char **argv){
	cv::Mat image = cv::imread(argv[2], cv::IMREAD_COLOR);
	if(!image.data){
		throw std::invalid_argument("Could not open the image file.");
	}
	filter->AddImage(image);
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
